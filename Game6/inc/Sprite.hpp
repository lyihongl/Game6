#pragma once
#include "SpriteSheet.hpp"
#include <memory>
#include <glm/glm.hpp>

class Sprite
{
public:
	//glm::vec2 gpu_tr, gpu_tl, gpu_br, gpu_bl;
	std::weak_ptr<SpriteSheet> sheet;
	int x, y, w, h;
	Sprite();
	Sprite(std::shared_ptr<SpriteSheet>& sheet, int x, int y, int w, int h);
	const Sprite& operator=(const Sprite&);
};

