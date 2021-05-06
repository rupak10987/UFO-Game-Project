#include"Hud.h"
#include"Spritecomponent_offset_position.h"
#include"Ship.h"
Hud::Hud(class Game* game):
	Object(game)
{
	Vector2 postn;
	postn.x = -400;//1067 / 2
	postn.y = 600/2;//600 / 2
	setposition(postn);
	Hud_life_sprite=new Spritecomponent_offset_position(this, 1, 1000, 415 - 10, 183-10);//ofset x y for r8 side=415-10, 183-10

	smg_hud = new Spritecomponent_offset_position(this, 1, 1001, 488 - 10, 212-10);//ofset x y for r8 side=488-10, 212-10
	smg_hud->settextue(game->gettexture("ship_assets/HUD/smg_hud.png"));

	special_bullet_hud=new Spritecomponent_offset_position(this, 1, 1002, 450 - 10, 253-10);//ofset x y for r8 side=450-10, 253-10
	number_of_bullet_tex = new Spritecomponent_offset_position(this, 1, 1003, 466 - 10, 277-10);//ofset x y for r8 side=466-10, 277-10

	special_bullet_hud->settextue(Shotgun_hud);

	EMP_hud = game->gettexture("ship_assets/HUD/emp_hud.png");
	Sniper_hud = game->gettexture("ship_assets/HUD/sniper_hud.png");
	Shotgun_hud = game->gettexture("ship_assets/HUD/shotgun_hud.png");

	stringstream filename_inital1;
	stringstream filename_inital2;
	string filename;
	filename_inital1 << "ship_assets/hud_life_circle/000";
	filename_inital2 << "ship_assets/hud_life_circle/00";
	for (int j = 0; j <= 50; j++)
	{
		stringstream num;;
		num << j;
		if (j < 10)
			filename = filename_inital1.str() + num.str() + ".png";
		else
			filename = filename_inital2.str() + num.str() + ".png";
		hud_life_tex.emplace_back(game->gettexture(filename.c_str()));
	}
	Hud_life_sprite->settextue(hud_life_tex.at(0));

}




void Hud::updateObject(float deltatime)
{
	stringstream n;
	SDL_Color col = { 255,255,255,255 };
	bullet_num = getgame()->getship()->get_mag_size();
	n << bullet_num;
	string filename = n.str();


	if (getgame()->getship()->get_magazinetype() == Ship::emp)
		special_bullet_hud->settextue(EMP_hud);
	else if(getgame()->getship()->get_magazinetype() == Ship::shotgun)
		special_bullet_hud->settextue(Shotgun_hud);
	else if (getgame()->getship()->get_magazinetype() == Ship::sniper)
		special_bullet_hud->settextue(Sniper_hud);

	if (bullet_num != previous_frame_bulletnumber)
	{
		number_of_bullet_tex->settextue(getgame()->get_text_as_texture(filename.c_str(), col, 14));
	}
	previous_frame_bulletnumber = bullet_num;


	now_life = getgame()->getship()->getlife()->getlife_stat();
	if (now_life != previous_frame_life)
	{
		Hud_life_sprite->settextue(hud_life_tex.at(50-now_life));
	}
	previous_frame_life = now_life;
}