#pragma once
#include"Object.h"
#include"Circlecomponent.h"
class loot :public Object
{
public:
	loot(class Game* game,Vector2 pos);
	class Circlecomponent* getcircle()const { return mcircle; }
	void updateObject(float deltatime)override;
	virtual void functionality();
protected:
	float timer = 5;
	Mix_Chunk* loot_equiped;
	class Circlecomponent* mcircle;
};