#include "inc/empire.hpp"
#include "inc/render.hpp"
#include "inc/grid.hpp"
#include "inc/EntityManager.hpp"

#include <cstdio>
#include <cstdlib>
#include <shaders.hpp>
#include <vector>
#include <queue>
#include <windows.h>
#include <cmath>

#define GLM_FORCE_RADIANS 1
#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

const int SCREEN_FULLSCREEN = 0;
const uint32_t SCREEN_WIDTH = 1280;
const uint32_t SCREEN_HEIGHT = 720;
const float VP_RATIO = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
SDL_Window *window = NULL;
SDL_GLContext maincontext;

// uint32_t frame_count = 0;

static void sdl_die(const char *message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

void init_screen(const char *caption) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) sdl_die("Couldn't initialize SDL");
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // Create the window
    if (SCREEN_FULLSCREEN) {
        window = SDL_CreateWindow(
            caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
            SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        window = SDL_CreateWindow(caption, SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    }
    if (window == NULL) sdl_die("Couldn't set video mode");

    maincontext = SDL_GL_CreateContext(window);
    if (maincontext == NULL) sdl_die("Failed to create OpenGL context");

    // Check OpenGL properties
    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Use v-sync
    // SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    // glShadeModel(GL_FLAT)
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_GL_SetSwapInterval(0);
    glViewport(0, 0, w, h);
    glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
}


int main(int argc, char **argv) {
    // std::cout<<Constants::getResource(Constants::ResourceIndex::WOOD).getName()<<std::endl;

    init_screen("OpenGL 4.3");

    SDL_Event event;
    bool quit = false;
    bool be_nice_and_dont_burn_the_cpu = true;
    Uint32 minimum_fps_delta_time = (1000 / 60);
    Uint32 last_game_step = SDL_GetTicks(); // initial value
    Uint32 wait_time = 0;

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f,
        100.0f);

    float angle = 0.0f;
    float rotationSpeed = 0.1f;

    glm::vec2 start = glm::vec2(10, 10);
    glm::vec2 end = glm::vec2(10, 40);
    unsigned long long ticks = 0;

    Empire rome{};
    Render render{SCREEN_WIDTH, SCREEN_HEIGHT};
    std::vector<Quad> quads;
    quads.push_back(Quad{50, 50, 100, 100, 0});
    Shader s{"./shaders/triagShader.vert", "./shaders/triagShader.frag"};
    Shader field{"./shaders/triagShader.vert", "./shaders/fieldLines.frag"};

    std::vector<std::vector<int>> grid1(36, std::vector<int>(64, 0));

    std::vector<std::vector<unsigned int>> blocked(
        36, std::vector<unsigned int>(64, 0));
    blocked[0][20] = 1;
    blocked[1][20] = 1;
    blocked[2][20] = 1;
    blocked[3][20] = 1;
    blocked[4][20] = 1;
    blocked[0][21] = 1;
    blocked[1][21] = 1;
    blocked[2][21] = 1;
    blocked[3][21] = 1;
    blocked[4][21] = 1;
    std::vector<Quad> quads2;
    for (int i = 0; i < blocked.size(); i++) {
        for (int j = 0; j < blocked[0].size(); j++) {
            if (blocked[i][j]) {
                quads2.push_back(Quad{20, 20, static_cast<float>(j * 20 + 10),
                                      static_cast<float>(i * 20 + 10), 0});
            }
        }
    }
    std::vector<Quad> quads3;
    for (int i = 0; i < blocked.size(); i++) {
        for (int j = 0; j < blocked[0].size(); j++) {
            if (!blocked[i][j]) {
                quads3.push_back(Quad{18, 2, static_cast<float>(j * 20 + 10),
                                      static_cast<float>(i * 20 + 9), 0});
            }
        }
    }

    std::vector<std::vector<std::pair<float, float>>> grid2(
        36, std::vector<std::pair<float, float>>(64, {0.0f, 0.0f}));

    int mX = 0, mY = 0;
    EntityManager em{};
    Entity e = em.addEntity("A");
    Physics2D p{};
    e.setComponent<Physics2D>(p);

    while (!quit) {
        uint32_t now = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                // if (rng_gen) delete rng_gen;
                quit = true;
                break;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                    break;
                }
            }
            }
        }

        if (last_game_step + minimum_fps_delta_time < now) {
            SDL_GL_SwapWindow(window);

            Uint32 delta_time = now - last_game_step;
            // wait_time = std::min(0, minimum_fps_delta_time - delta_time);

            if (delta_time > minimum_fps_delta_time) {
                delta_time = minimum_fps_delta_time; // slow down if the
                                                     // computer is too slow
            }
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // std::cout << "fps: " << (1000.f / delta_time) << "\n";
            ticks++;
            SDL_GetMouseState(&mX, &mY);
            unsigned int gridX = mX / 20;
            unsigned int gridY = mY / 20;
            if (ticks % 5) {
                // std::cout<<gridX<<": "<<gridY<<std::endl;
                //GridUtil::bfs(grid1, blocked, gridX, gridY);
                //GridUtil::compute_gradient_mtx(grid1, grid2);
                // for (const auto &row : grid1) {
                //     for (const unsigned int &i : row) {
                //         std::cout << i << " ";
                //         // i = 0;
                //     }
                //     std::cout << "\n";
                // }
                // std::cout << std::endl;
            }
            // rome.simulate(ticks);
            //for (Quad &q : quads) {
            //    // q.rad += 0.005;
            //    uint32_t quad_grid_x = q.x / 20;
            //    uint32_t quad_grid_y = q.y / 20;

            //    const auto &[ax, ay] = grid2[quad_grid_y][quad_grid_x];
            //    q.x += ax * 0.3;
            //    q.y += ay * 0.3;
            //}
            //for (Quad &q : quads3) {
            //    // q.rad += 0.005;
            //    uint32_t quad_grid_x = q.x / 20;
            //    uint32_t quad_grid_y = q.y / 20;

            //    const auto &[ax, ay] = grid2[quad_grid_y][quad_grid_x];
            //    q.rad = std::atan2(ay, ax);
            //}
            //render.renderQuad(quads, s);
            //render.renderQuad(quads2, s);
            //render.renderQuad(quads3, field);

            // RenderGame();

            last_game_step = now;
        } else {
            // we're too fast, wait a bit.
            if (be_nice_and_dont_burn_the_cpu) {
                SDL_Delay(1);
            }
        }
    }
    return 0;
}