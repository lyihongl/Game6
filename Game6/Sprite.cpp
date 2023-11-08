#include "inc/Sprite.hpp"

Sprite::Sprite() : sheet(), x(0), y(0), w(0), h(0)
{
}

Sprite::Sprite(std::shared_ptr<SpriteSheet>& sheet, int x, int y, int w, int h) :
	sheet(sheet), x(x), y(y), w(w), h(h)
{
}

Sprite& Sprite::operator=(const Sprite& s)
{
	return const_cast<Sprite&>(s);
}
