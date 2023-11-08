#pragma once
#include "SpriteSheet.hpp"
#include <memory>

class Sprite
{
	const std::weak_ptr<SpriteSheet> sheet;
	int x, y, w, h;
public:
	Sprite();
	Sprite(std::shared_ptr<SpriteSheet>& sheet, int x, int y, int w, int h);
	Sprite& operator=(const Sprite&);
};

