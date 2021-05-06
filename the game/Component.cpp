#include"Component.h"
Component::Component(class Object* owner, int c_order):
	mcomp_order(c_order),
	mowner(owner)
{
	mowner->addcomponents(this);
}
Component::~Component()
{
	mowner->removecomponent(this);
}