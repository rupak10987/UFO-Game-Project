#pragma once
#include"Spritecomponent.h"

class Spritecomponent_offset_position :public Spritecomponent
{
public:
	Spritecomponent_offset_position(class Object* owner, int c_order, int draworder, int offset_x, int offset_y):
		Spritecomponent(owner, c_order, draworder),
		moffset_x(offset_x),
		mofffset_y(offset_y)
	{
	}
	void update(float deltatime)override
	{
		int x = static_cast<int>(mowner->getposition().x);
		int y = static_cast<int>(mowner->getposition().y);
		mrect.x = x + moffset_x;
		mrect.y = y + mofffset_y;
		mrect.h = mowner->getscale() * mytexheight;
		mrect.w = mowner->getscale() * mytexwidth;
	}

protected:
	//6.66 pixel per charecter of size 12 text
	int moffset_x;
	int mofffset_y;
};