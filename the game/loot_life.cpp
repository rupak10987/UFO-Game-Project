#include"loot_life.h"
#include"Ship.h"
#include"Animation_sprite.h"
#include"Spritecomponent_offset_position.h"
loot_life::loot_life(class Game* game, Vector2 pos) :
	loot(game, pos)
{
	class Animation_sprite* material = new Animation_sprite(this, 1, 3, 24);
	std::vector<SDL_Texture*>animation;
	stringstream filename_inital1;
	stringstream filename_inital2;
	string filename;
	filename_inital1 << "ship_assets/loot_shield/000";
	filename_inital2 << "ship_assets/loot_shield/00";
	for (int j = 1; j <= 59; j++)
	{
		stringstream num;;
		num << j;
		if (j < 10)
			filename = filename_inital1.str() + num.str() + ".png";
		else
			filename = filename_inital2.str() + num.str() + ".png";
		animation.emplace_back(game->gettexture(filename.c_str()));
	}
	material->setanimatontextures(animation);
	/*class Spritecomponent_offset_position* mte = new Spritecomponent_offset_position(this, 1, 4, -24, -14 - 0);
	SDL_Color col = { 0,0,0,255 };
	mte->settextue(game->get_text_as_texture("life", col, 12));*/
}

void loot_life::functionality()
{
	getgame()->getship()->getlife()->setlife((getgame()->getship()->getlife()->getlife_stat()) + gain_life);
	getgame()->getship()->getlife()->settimer(1);
}