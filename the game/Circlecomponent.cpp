#include"Circlecomponent.h"
Circlecomponent::Circlecomponent(class Object* owner, int c_order, float rad) :
	Component(owner, c_order)
{
	setradius(rad);
	mowner->setcollision_stat(true);
}