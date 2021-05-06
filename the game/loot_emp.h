#pragma once
#include"loot.h"
class loot_emp :public loot
{
public:
	loot_emp(class Game* game, Vector2 pos);
	void functionality()override;
private:
	int mag_size = 1;
};