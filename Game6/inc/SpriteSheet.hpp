#pragma once

#include <string>
#include <stb_image.h>

class SpriteSheet {
    void PrepareData(unsigned char *data);

    public:
    unsigned int textureId;
    int width, height, nrChannels;

    SpriteSheet(const std::string &path);
    SpriteSheet(const std::string &&path);

    SpriteSheet(SpriteSheet &) = delete;
    SpriteSheet(SpriteSheet &&) = delete;
    SpriteSheet operator=(SpriteSheet &) = delete;
    ~SpriteSheet();
};
