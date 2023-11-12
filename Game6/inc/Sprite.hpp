#pragma once
#include "SpriteSheet.hpp"
#include "components/ComponentBase.hpp"
#include <memory>
#include <glm/glm.hpp>

class Sprite : Component2D{
    public:
    // glm::vec2 gpu_tr, gpu_tl, gpu_br, gpu_bl;
    std::weak_ptr<SpriteSheet> sheet;
    float x, y, w, h;
    Sprite();
    Sprite(std::shared_ptr<SpriteSheet> &sheet, float x, float y, float w, float h);
    const Sprite &operator=(const Sprite &);
    virtual void reset();
};
