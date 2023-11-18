#include "inc/EntityManager.hpp"
#include "inc/PhysicsProcess.hpp"
#include "inc/SpriteSheet.hpp"
#include "inc/empire.hpp"
#include "inc/grid.hpp"
#include "inc/render.hpp"
#include "inc/Particle.hpp"

#include <windows.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <queue>
#include <shaders.hpp>
#include <vector>

#define GLM_FORCE_RADIANS 1
#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const int SCREEN_FULLSCREEN = 0;
float SCREEN_WIDTH = 1368;
float SCREEN_HEIGHT = 768;
float VP_RATIO = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
SDL_Window* window = NULL;
SDL_GLContext maincontext;

// uint32_t frame_count = 0;

static void sdl_die(const char* message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

void init_screen(const char* caption) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_die("Couldn't initialize SDL");
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL);  // Default OpenGL is fine.

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
        int SW, SH;
        window = SDL_CreateWindow(
            caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
            SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
        SDL_GetWindowSize(window, &SW, &SH);
        SCREEN_WIDTH = static_cast<float>(SW);
        SCREEN_HEIGHT = static_cast<float>(SH);
        VP_RATIO = SCREEN_WIDTH / SCREEN_HEIGHT;
    } else {
        window = SDL_CreateWindow(
            caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            static_cast<uint32_t>(SCREEN_WIDTH),
            static_cast<uint32_t>(SCREEN_HEIGHT), SDL_WINDOW_OPENGL);
    }
    if (window == NULL)
        sdl_die("Couldn't set video mode");

    maincontext = SDL_GL_CreateContext(window);
    if (maincontext == NULL)
        sdl_die("Failed to create OpenGL context");

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

int main(int argc, char** argv) {
    // std::cout<<Constants::getResource(Constants::ResourceIndex::WOOD).getName()<<std::endl;

    init_screen("OpenGL 4.3");

    SDL_Event event;
    bool quit = false;
    bool be_nice_and_dont_burn_the_cpu = true;
    float minimum_fps_delta_time = (1000000.f / 60.f);
    Uint32 last_game_step = SDL_GetTicks();  // initial value
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
    quads.push_back(Quad{100, 100});
    Shader s{"./shaders/triagShader.vert", "./shaders/triagShader.frag"};
    Shader field{"./shaders/triagShader.vert", "./shaders/fieldLines.frag"};
    Shader spriteShader{"./shaders/spriteTest.vert",
                        "./shaders/spriteTest.frag"};

    // std::vector<std::vector<int>> grid1(36, std::vector<int>(64, 0));

    // std::vector<std::vector<unsigned int>> blocked(
    //     36, std::vector<unsigned int>(64, 0));
    // blocked[0][20] = 1;
    // blocked[1][20] = 1;
    // blocked[2][20] = 1;
    // blocked[3][20] = 1;
    // blocked[4][20] = 1;
    // blocked[0][21] = 1;
    // blocked[1][21] = 1;
    // blocked[2][21] = 1;
    // blocked[3][21] = 1;
    // blocked[4][21] = 1;
    // std::vector<Quad> quads2;
    // for (int i = 0; i < blocked.size(); i++) {
    //     for (int j = 0; j < blocked[0].size(); j++) {
    //         if (blocked[i][j]) {
    //             quads2.push_back(Quad{20, 20, static_cast<float>(j * 20 +
    //             10),
    //                                   static_cast<float>(i * 20 + 10), 0});
    //         }
    //     }
    // }
    // std::vector<Quad> quads3;
    // for (int i = 0; i < blocked.size(); i++) {
    //     for (int j = 0; j < blocked[0].size(); j++) {
    //         if (!blocked[i][j]) {
    //             quads3.push_back(Quad{18, 2, static_cast<float>(j * 20 + 10),
    //                                   static_cast<float>(i * 20 + 9), 0});
    //         }
    //     }
    // }

    std::vector<std::vector<std::pair<float, float>>> grid2(
        36, std::vector<std::pair<float, float>>(64, {0.0f, 0.0f}));

    int mX = 0, mY = 0;
    EntityManager em{};
    Entity e = em.addEntity("A");
    Entity mainShipEntity = em.addEntity("B");

    std::shared_ptr<SpriteSheet> sheet =
        std::make_shared<SpriteSheet>("./res/shipsall.gif");
    Sprite sprite{sheet, 0.f, 0.f, static_cast<float>(64),
                  static_cast<float>(64)};
    Sprite sprite2{sheet, 0.f, 0.f, static_cast<float>(64),
                   static_cast<float>(64)};

    Sprite sprite3{sheet, 128.f, 64.f, static_cast<float>(28),
                   static_cast<float>(56)};
    Sprite retical{sheet, 196.f, 4.f, 24.f, 24.f};

    Particle reticalParticle(retical);

    Entity r = em.addEntity("");
    r.setComponent<Quad>({12, 12});
    r.setComponent<Sprite>(retical);
    r.setComponent<Position2D>({0, 0, 0});

    std::cout << "sheet width: " << sheet->width << std::endl;

    Physics2D p{};
    e.setComponent<Position2D>({0, 0, 0});
    e.setComponent<Physics2D>(p);
    e.setComponent<Quad>({100, 100});
    e.setComponent<Sprite>(sprite);

    mainShipEntity.setComponent<Position2D>({600, 600, -2});
    mainShipEntity.setComponent<Physics2D>(p);
    mainShipEntity.setComponent<Quad>({32, 32});
    mainShipEntity.setComponent<Sprite>(sprite2);

    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    glm::dvec2 state = {0, 0};
    glm::dvec2 derivative = {0, 0};

    glm::dvec2 vstate = {0, 0};
    glm::dvec2 vderivative = {0, 0};

    glm::dvec2 cameraOffset = {100.0, 100.0};

    double time = 0;
    float target = 0;
    float zoomw = SCREEN_WIDTH;
    float zoomh = SCREEN_HEIGHT;
    // glm::ivec2 mousePos;
    int viewZoom = 1;
    glm::dvec2 cameraZoomState = {zoomh, 0};
    glm::dvec2 dcameraZoomState = {0, 0};
    float targetH = zoomh;
    unsigned long long lastZoom = 0;

    while (!quit) {
        // uint32_t now = SDL_GetTicks();
        auto delta_time = end_time - start_time;
        end_time = std::chrono::high_resolution_clock::now();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    // if (rng_gen) delete rng_gen;
                    quit = true;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        SDL_GetMouseState(&mX, &mY);
                        if (!r.hasComponent<Position2D>()) {
                            r.setComponent<Position2D>(
                                {static_cast<float>(mX) +
                                     static_cast<float>(cameraOffset.x) * zoomw / SCREEN_WIDTH,
                                 static_cast<float>(mY) +
                                     static_cast<float>(cameraOffset.y) * zoomh / SCREEN_HEIGHT,
                                 0.f});
                            // r.setComponent<Position2D>({
                            //     static_cast<float>(mX) / 2 * screenw /
                            //     SCREEN_WIDTH, static_cast<float>(mX) / 2 *
                            //     screenw / SCREEN_WIDTH,
                            //     });
                        } else {
                            r.getComponent<Position2D>().x =
                                static_cast<float>(mX) * zoomw / SCREEN_WIDTH +
                                cameraOffset.x;
                            r.getComponent<Position2D>().y =
                                static_cast<float>(mY) * zoomh / SCREEN_HEIGHT +
                                cameraOffset.y;
                        }
                    }
                    break;
                }
                case SDL_MOUSEWHEEL: {
                    //lastZoom
                    if (event.wheel.y > 0) {
                        // zoomw -= 30 * VP_RATIO;
                        // zoomh -= 30;
                        // cameraOffset += glm::vec2{15 * VP_RATIO, 15};

                        //targetH = std::fmax(targetH-100, 0.5*SCREEN_HEIGHT);
                        if (viewZoom == 1) {
                            viewZoom = 0;
                            targetH = 0.5f * SCREEN_HEIGHT;
                        } else if (viewZoom == 2) {
                            viewZoom = 1;
                            targetH = SCREEN_HEIGHT;
                        } else if (viewZoom == 0) {
                            targetH = 0.5f * SCREEN_HEIGHT;
                        }
                    } else if (event.wheel.y < 0) {
                        //targetH += 100;
                        if (viewZoom == 1) {
                            viewZoom = 2;
                            targetH = 2 * SCREEN_HEIGHT;
                        } else if (viewZoom == 0) {
                            viewZoom = 1;
                            targetH = SCREEN_HEIGHT;
                        } else if (viewZoom == 2) {
                            targetH = 2 * SCREEN_HEIGHT;
                        }
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_q) {
                        quit = true;
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_SPACE &&
                        event.key.repeat == 0) {

                        Entity c = em.addEntity("");
                        c.setComponent<Position2D>(
                            mainShipEntity.getComponent<Position2D>());
                        p.vx =
                            std::sin(
                                mainShipEntity.getComponent<Position2D>().rad) *
                            6;
                        p.vy =
                            -std::cos(
                                mainShipEntity.getComponent<Position2D>().rad) *
                            6;
                        c.setComponent<Physics2D>(p);
                        c.setComponent<Quad>({14, 29});
                        c.setComponent<Sprite>(sprite3);
                    }
                }
            }
        }
        long long delta_time_us =
            std::chrono::duration_cast<std::chrono::microseconds>(delta_time)
                .count();

        if (delta_time_us > minimum_fps_delta_time) {
            SDL_GL_SwapWindow(window);

            if (std::fabs(zoomh - targetH) > 0.01) {
                cameraZoomState.x = static_cast<double>(zoomh);
                //dcameraZoomState = Physics::RK4(
                //    targetH, cameraZoomState, dcameraZoomState, time,
                //    static_cast<double>(delta_time_us) / 10000000);

                //cameraZoomState += dcameraZoomState;
                //glm::dvec2 oldZoomState = cameraZoomState;
                //std::cout << "[before] target: " << targetH << " "
                //          << glm::to_string(cameraZoomState) << std::endl;
                cameraZoomState = Physics::implicitEuler(
                    targetH, cameraZoomState, time,
                    static_cast<double>(delta_time_us) / 10000000);
                //std::cout << "[after] target: " << targetH << " "
                //          << glm::to_string(cameraZoomState) << std::endl;
                zoomh = static_cast<float>(cameraZoomState.x);
                zoomw = static_cast<float>(cameraZoomState.x) * VP_RATIO;
                cameraOffset -= glm::vec2{static_cast<float>(cameraZoomState.y) * VP_RATIO * 0.5,
                                          static_cast<float>(cameraZoomState.y) * 0.5};
            }
            // if (viewZoom == 2 && std::fabs(SCREEN_HEIGHT * 2 - zoomh) >
            // 0.001) { zoomw += 30 * VP_RATIO; zoomh += 30; cameraOffset -=
            // glm::vec2{15 * VP_RATIO, 15};
            //} else if (viewZoom == 1 && std::fabs(SCREEN_HEIGHT - zoomh) >
            // 0.001)
            // SDL_GetMouseState(&mousePos.x, &mousePos.y);
            // if (mousePos.x < 40) {
            //     cameraOffset.x -= 10;
            // } else if (mousePos.x >= SCREEN_WIDTH - 40) {
            //     cameraOffset.x += 10;
            // }
            // if (mousePos.y < 40) {
            //     cameraOffset.y -= 10;
            // } else if (mousePos.y >= SCREEN_HEIGHT - 40) {
            //     cameraOffset.y += 10;
            // }

            // Uint32 delta_time = now - last_game_step;
            //  wait_time = std::min(0, minimum_fps_delta_time - delta_time);

            if (delta_time_us > minimum_fps_delta_time) {
                delta_time_us =
                    floor(minimum_fps_delta_time);  // slow down if the
                                                    // computer is too slow
            }
            cameraOffset.x =
                mainShipEntity.getComponent<Position2D>().x - zoomw / 2;
            cameraOffset.y =
                mainShipEntity.getComponent<Position2D>().y - zoomh / 2;
            // cameraOffset.x += 1;
            //  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClearColor(156 / 255.f, 166 / 255.f, 158 / 255.f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            float shipAngle = mainShipEntity.getComponent<Position2D>().rad;
            glm::vec2 a{mainShipEntity.getComponent<Position2D>().x,
                        mainShipEntity.getComponent<Position2D>().y};
            glm::vec2 b = a + glm::vec2{10 * std::sin(shipAngle),
                                        -10 * std::cos(shipAngle)};
            glm::vec2 c{r.getComponent<Position2D>().x,
                        r.getComponent<Position2D>().y};
            int relativeDir = Physics::relativeDir(a, b, c);
            float angle = 0;
            if (relativeDir == 1) {
                glm::vec2 l1{a - b};
                glm::vec2 l2{c - b};
                angle =
                    std::abs(std::atan2(std::fabs(l1.y * l2.x - l1.x * l2.y),
                                        std::fabs(l1.x * l2.x + l1.y * l2.y)));
            } else if (relativeDir == -1) {
                glm::vec2 l1{a - b};
                glm::vec2 l2{c - b};
                angle =
                    -std::abs(std::atan2(std::fabs(l1.y * l2.x - l1.x * l2.y),
                                         std::fabs(l1.x * l2.x + l1.y * l2.y)));
            }
            target = shipAngle + angle;
            // zoomw += 1.f*VP_RATIO;
            // zoomh += 1.f;
            render.updateRes(zoomw, zoomh);
            // std::cout << "relativeDir: " << relativeDir << " angle: " <<
            // angle
            //           << "\n";
            // std::cout << glm::to_string(a - b) << " " << glm::to_string(c -
            // b)
            //           << "\n";

            // state = {shipAngle,
            // mainShipEntity.getComponent<Physics2D>().vrad};
            if (r.hasComponent<Position2D>()) {
                vstate.x = glm::length(c - a);
                vderivative =
                    Physics::RK4(0, vstate, vderivative, time,
                                 static_cast<double>(delta_time_us) / 10000000);
                vderivative[0] = vderivative[0] / std::fabs(vderivative[0]) *
                                 std::fmin(std::fabs(vderivative[0]), 5.f);
                // std::cout << "vdervative: " << glm::to_string(vderivative)
                //           << "\n";
                vstate + vderivative;
                mainShipEntity.getComponent<Physics2D>().vx =
                    -glm::sin(shipAngle) * vderivative[0];
                mainShipEntity.getComponent<Physics2D>().vy =
                    glm::cos(shipAngle) * vderivative[0];
            }
            state.x = shipAngle;
            derivative =
                Physics::RK4(target, state, derivative, time,
                             static_cast<double>(delta_time_us) / 10000000);
            state += derivative;

            mainShipEntity.getComponent<Physics2D>().vrad = derivative[0];
            // mainShipEntity.getComponent<Physics2D>().vx =
            //     glm::sin(state[0]) * 2;
            // mainShipEntity.getComponent<Physics2D>().vy =
            //     -glm::cos(state[0]) * 2;
            for (auto& f : em.entities) {
                if (f.hasComponent<Physics2D>()) {
                    f.getComponent<Position2D>() += f.getComponent<Physics2D>();
                }
            }
            // std::cout << "state: " << glm::to_string(state)
            //           << " derivative:" << glm::to_string(derivative) <<
            //           "\n";
            // std::cout << "ship rad: "
            //           << mainShipEntity.getComponent<Position2D>().rad <<
            //           "\n";

            // std::cout << "derivative: " << glm::to_string(derivative) <<
            // std::endl;
            //  rome.simulate(ticks);
            //  for (Quad &q : quads) {
            //     // q.rad += 0.005;
            //     uint32_t quad_grid_x = q.x / 20;
            //     uint32_t quad_grid_y = q.y / 20;

            //    const auto &[ax, ay] = grid2[quad_grid_y][quad_grid_x];
            //    q.x += ax * 0.3;
            //    q.y += ay * 0.3;
            //}
            // for (Quad &q : quads3) {
            //    // q.rad += 0.005;
            //    uint32_t quad_grid_x = q.x / 20;
            //    uint32_t quad_grid_y = q.y / 20;

            //    const auto &[ax, ay] = grid2[quad_grid_y][quad_grid_x];
            //    q.rad = std::atan2(ay, ax);
            //}
            // render.renderQuad(quads, s);
            // render.renderQuad(quads2, s);
            // render.renderQuad(quads3, field);

            // RenderGame();

            // last_game_step = now;
            render.renderEntity(em.entities, spriteShader, cameraOffset);
            start_time = std::chrono::high_resolution_clock::now();
        } else {
            // we're too fast, wait a bit.
            if (be_nice_and_dont_burn_the_cpu) {
                SDL_Delay(1);
            }
        }
    }
    return 0;
}