#include "inc/quad.hpp"

Quad::Quad() : w(0), h(0) {
}

Quad::Quad(float w, float h) : w(w), h(h) {
}

// std::pair<float, float> Quad::topLeft() const {
//     return {x - w / 2, y - h / 2};
// }
// std::pair<float, float> Quad::topRight() const {
//     return {x + w / 2, y - h / 2};
// }
// std::pair<float, float> Quad::bottomRight() const {
//     return {x + w / 2, y + h / 2};
// }
// std::pair<float, float> Quad::bottomLeft() const {
//     return {x - w / 2, y + h / 2};
// }