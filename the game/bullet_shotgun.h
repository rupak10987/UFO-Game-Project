#pragma once
#include"bullet.h"
class bullet_shotgun :public bullet
{
public:
	bullet_shotgun(class Game* game, Vector2 pos, float rot);
	void load_bullet()override;
};