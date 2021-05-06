#pragma once
#include"loot.h"
class loot_shotgun_ammo :public loot
{
public:
	loot_shotgun_ammo(class Game* game, Vector2 pos);
	void functionality()override;
private:
	int mag_size = 3;
};