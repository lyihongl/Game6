#include "inc/Sprite.hpp"

Sprite::Sprite(SpriteSheet& sheet, unsigned int x, unsigned int y, unsigned int w, unsigned int h) :
	sheet(sheet), x(x), y(y), w(w), h(h)
{
}
