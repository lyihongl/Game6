#include "inc/Sprite.hpp"

Sprite::Sprite() : sheet(), x(0), y(0), w(0), h(0) {
}

Sprite::Sprite(std::shared_ptr<SpriteSheet> &sheet, float x, float y, float w, float h)
    : sheet(sheet), x(x), y(y), w(w), h(h)
// gpu_tr(static_cast<float>(x) / sheet->width, static_cast<float>(y) /
// sheet->height), gpu_tl((static_cast<float>(x) + w) / sheet->width,
// static_cast<float>(y) / sheet->height), gpu_br(static_cast<float>(x) /
// sheet->width, (static_cast<float>(y) + h) / sheet->height),
// gpu_bl((static_cast<float>(x) + w) / sheet->width, (static_cast<float>(y) +
// h) / sheet->height)
{
}

const Sprite &Sprite::operator=(const Sprite &s) {
    sheet = s.sheet;
    x = s.x;
    y = s.y;
    w = s.w;
    h = s.h;
    // gpu_tr = glm::vec2(static_cast<float>(x) / sheet.lock()->width,
    // static_cast<float>(y) / sheet.lock()->height); gpu_tl =
    // glm::vec2((static_cast<float>(x) + w) / sheet.lock()->width,
    // static_cast<float>(y) / sheet.lock()->height); gpu_br =
    // glm::vec2(static_cast<float>(x) / sheet.lock()->width,
    // (static_cast<float>(y) + h) / sheet.lock()->height); gpu_bl =
    // glm::vec2((static_cast<float>(x) + w) / sheet.lock()->width,
    // (static_cast<float>(y) + h) / sheet.lock()->height);
    return *this;
}
