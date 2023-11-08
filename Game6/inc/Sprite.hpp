#pragma once
#include "SpriteSheet.hpp"

class Sprite
{
	const SpriteSheet& sheet;
	int x, y, w, h;
public:
	Sprite(SpriteSheet& sheet, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
};

