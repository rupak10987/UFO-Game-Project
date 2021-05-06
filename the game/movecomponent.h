#pragma once
#include"Component.h"
#include"Circlecomponent.h"
class Movecomponent :public Component
{
public:
	Movecomponent(class Object* owner,class Circlecomponent* c, int c_order);
	void setforwardspeed(float speed) { forwardspeed = speed; }
	void setangularspeed(float speed) { angularspeed = speed; }
	float getforwardsped()const { return forwardspeed; }
	float getangularspeed()const { return angularspeed; }
	void update(float deltatime)override;
	Vector2 getcurrentvector() { return f; }
	void svs(float deltatime);

private:
	Vector2 f;
	float forwardspeed;
	float angularspeed;
	class Circlecomponent* mcir;
};