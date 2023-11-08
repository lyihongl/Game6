#include "inc/components/physics2d.hpp"

Physics2D::Physics2D(): x(0), y(0), vx(0), vy(0), ax(0), ay(0), rad(0), vrad(0), arad(0) {
}

void Physics2D::reset()
{
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	ax = 0;
	ay = 0;
	rad = 0;
	vrad = 0;
	arad = 0;
}
