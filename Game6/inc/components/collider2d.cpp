#include "collider2d.hpp"

Collider2D::Collider2D() : x(0), y(0), leftBound(0), rightBound(0), topBound(0), bottomBound(0) 
{

}

void Collider2D::reset() {
	x = 0;
	y = 0;
	leftBound = 0;
	rightBound = 0;
	topBound = 0;
	bottomBound = 0;
}
