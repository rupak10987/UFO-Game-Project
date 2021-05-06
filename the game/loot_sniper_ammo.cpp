#include"loot_sniper_ammo.h"
#include"Ship.h"
#include"Animation_sprite.h"
#include"Spritecomponent_offset_position.h"
loot_sniper_ammo::loot_sniper_ammo(class Game* game, Vector2 pos) :
	loot(game, pos)
{
	class Animation_sprite* material = new Animation_sprite(this, 1, 3, 24);
	std::vector<SDL_Texture*>animation;
	stringstream filename_inital1;
	stringstream filename_inital2;
	string filename;
	filename_inital1 << "ship_assets/loot_sniper_amo/000";
	filename_inital2 << "ship_assets/loot_sniper_amo/00";
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
	class Spritecomponent_offset_position* mytext = new Spritecomponent_offset_position(this, 1, 4, -20, -16-12);
	SDL_Color col = { 0,0,0,255 };
	mytext->settextue(game->get_text_as_texture("sniper", col, 12));//6.66 pixel per charecter of size 12 text
}

void loot_sniper_ammo::functionality()
{
	getgame()->getship()->set_mag_type(Ship::sniper);
	getgame()->getship()->set_mag_size(mag_size);
}