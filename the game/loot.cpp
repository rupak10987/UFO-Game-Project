#include"loot.h"
#include"Circlecomponent.h"
#include"Ship.h"
loot::loot(class Game* game, Vector2 pos) :
	Object(game)
{
	setposition(pos);
	setrotation(0.0);
	loot_equiped = getgame()->get_sfx("ship_assets/sfx_wav/equip.wav");
	mcircle = new Circlecomponent(this, 2, 16);
}

void loot::functionality()
{
}

void loot::updateObject(float deltatime)
{
	timer -= deltatime;
	if (timer <= 0)
	{
		setstate(dead);
		return;
	}
	if (mcircle->intersect(mcircle, getgame()->getship()->getcircle()))
	{
		Mix_PlayChannel(5, loot_equiped, 0);
		functionality();
		setstate(dead);
	}
}