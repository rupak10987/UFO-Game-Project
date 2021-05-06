#pragma once
#include"bullet.h"
class bullet2 :public bullet
{
public:
	bullet2(class Game* game, Vector2 pos, float rot);
	void load_bullet()override;
};