#pragma once
#include"loot.h"
class loot_sniper_ammo :public loot
{
public:
	loot_sniper_ammo(class Game* game, Vector2 pos);
	void functionality()override;
private:
	int mag_size = 3;
};