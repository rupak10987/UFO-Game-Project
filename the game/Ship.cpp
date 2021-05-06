#include"Ship.h"
#include"Spritecomponent.h"
#include"Animation_sprite.h"
#include"Inputcomponent.h"
#include"vector"
#include"bullet2.h"
#include"bullet.h"
#include"bullet_shotgun.h"
#include"EMP.h"
#include"Object.h"
Ship::Ship(class Game* game) :
	Object(game)
{
	id = 0;
	Vector2 pposi;
	pposi.x = 32;
	pposi.y = 32;
	setposition(pposi);
	//std::cout << "initializing ship" << std::endl;
	mcircle = new Circlecomponent(this, 5, 20);
	class Inputcomponent* inputs = new Inputcomponent(this, 0);
	inputs->setkeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D,SDL_SCANCODE_SPACE);
	material = new Animation_sprite(this, 1, 2, 50);
	stringstream filename_inital1;
	stringstream filename_inital2;
	string filename;
	filename_inital1 << "ship_assets/new_ship3/00";
	filename_inital2 << "ship_assets/new_ship3/0";
	for (int j = 60; j <= 120; j++)
	{
		stringstream num;;
		num << j;
		if (j <= 99)
		{
			filename = filename_inital1.str() + num.str() + ".png";
		}
		else
		{
			filename = filename_inital2.str() + num.str() + ".png";
		}
		animation_normal.emplace_back(game->gettexture(filename.c_str()));
	}
	
	material->setanimatontextures(animation_normal);
	mlife = new Life_Spritecomponent(this, 3, 200, 50);
	SDL_Texture* li = game->gettexture("ship_assets/life2.png");
	mlife->settextue(li);
}


void Ship::updateObject(float deltatime)
{
	if (timer <= 1)
	{
		timer -= deltatime * current_bull_sec;
		if (timer <= 0)
		{
			timer = 1.5;
		}
	}
}

void Ship::keyboard(const Uint8* key)
{
	Object::keyboard(key);
	
	if (key[SDL_SCANCODE_SPACE])
	{
		if (gettimer() == 1.5)
		{
			sfx_channel++;
			sfx_channel %= 3;
			Vector2 temppos = getposition();
			bullet* bul = new bullet(getgame(), temppos, getrotation());
			temppos += bul->recoil(getforward()) * 32;
			bul->setposition(temppos);
			set_current_bullet_sec(bul->get_bullet_per_sec());
			settimer(1);
			bul->play_gunshot_sfx(sfx_channel);
		}
	}

	if (key[SDL_SCANCODE_Q])
	{
		if (gettimer() == 1.5 && magazine_size>0 && magazine_type == sniper)
		{
			magazine_size--;
			Vector2 temppos = getposition();
			temppos += getforward() * 32;
			bullet2* bul = new bullet2(getgame(), temppos, getrotation());
			set_current_bullet_sec(bul->get_bullet_per_sec());
			settimer(1);
			bul->play_gunshot_sfx(0);
		}
	}
	if (key[SDL_SCANCODE_Q])
	{
		if (gettimer() == 1.5 && magazine_size > 0 && magazine_type==shotgun)
		{
			magazine_size--;
			Vector2 temppos = getposition();
			temppos += getforward() * 32;
			bullet_shotgun* bul = new bullet_shotgun(getgame(), temppos, getrotation()+Math::ToRadians(5.0));
			bullet_shotgun* bul1 = new bullet_shotgun(getgame(), temppos, getrotation());
			bullet_shotgun* bul2 = new bullet_shotgun(getgame(), temppos, getrotation()-Math::ToRadians(5.0));
			set_current_bullet_sec(bul->get_bullet_per_sec());
			settimer(1);
			bul->play_gunshot_sfx(0);
		}

	}
	if (key[SDL_SCANCODE_Q])
	{
		if (gettimer() == 1.5 && magazine_size > 0 && magazine_type == emp)
		{
			magazine_size--;
			Vector2 temppos = getposition()+(32*getforward());
			EMP* boma = new EMP(getgame(), temppos);
			set_current_bullet_sec(boma->get_bullet_per_sec());
			settimer(1);
			boma->mix_play_emp_effect();
		}
	}
	if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S])
	{
		this->material->set_fps(70);
		if(key[SDL_SCANCODE_LSHIFT])
		{
			this->material->set_fps(100);
		}
	}
	else
		this->material->set_fps(50);

}

