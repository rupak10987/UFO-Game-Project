#pragma once
#include"Object.h"
class Component
{
public:
	Component(class Object* owner, int c_order);
	virtual ~Component();
	virtual void update(float deltatime){}
	virtual void processinput(const Uint8* kstate){}
	int get_cdraworder()const { return mcomp_order; }
protected:
	int mcomp_order;
	class Object* mowner;
};