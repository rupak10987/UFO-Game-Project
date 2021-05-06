#pragma once
#include"loot.h"
class loot_life :public loot
{
public:
	loot_life(class Game* game, Vector2 pos);
	void functionality()override;
private:
	int gain_life = 5;
};