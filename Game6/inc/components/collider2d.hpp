#pragma once
#include "../../component.hpp"
class Collider2D {
	float x, y;
	float leftBound, rightBound, topBound, bottomBound;
public:
	Collider2D();
	virtual void reset();
};