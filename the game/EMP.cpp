#include"EMP.h"
#include"stones.h"
#include"loot_shotgun_ammo.h"
#include"loot_sniper_ammo.h"
#include"loot_emp.h"
#include"Damage_counter_Sprite.h"
#include"loot_life.h"
EMP::EMP(class Game* game, Vector2 pos) :
	Object(game)
{
	setposition(pos);
	setscale(0);
	material = new Animation_sprite(this, 5, 3, 150);
	mcircle = new Circlecomponent(this, 1, 0);
	emp_effect_sfx = getgame()->get_sfx("ship_assets/sfx_wav/mozambique.wav");
	std::vector<SDL_Texture*>animation;
	stringstream filename_inital1;
	stringstream filename_inital2;
	string filename;
	filename_inital1 << "ship_assets/emp_trial/000";
	filename_inital2 << "ship_assets/emp_trial/00";
	for (int j = 1; j <= 20; j++)
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
}

void EMP::updateObject(float deltatime)
{
	float rad_scale = mcircle->getradius();
	rad_scale += 150 * deltatime;
	mcircle->setradius(rad_scale);
	setscale(rad_scale*2 / 300);//300 is the side of the texture

	if (mcircle->getradius() >= emp_max_radius)
	{
		setstate(dead);
		return;
	}	
	for (auto st : getgame()->getstones())
	{
		if (st->get_emp_renew_timer() >= 1.6)
		{
			if (mcircle->intersect(mcircle, st->getcircle()))
			{
				st->set_emp_renew_timer();
				if (st->getlife_sprite()->getlife_stat() <= dph)
				{
					int rand_num = rand() % 11;
					if (rand_num >= 0 && rand_num <= 7)
						class loot_sniper_ammo* lut1 = new loot_sniper_ammo(getgame(), st->getposition());
					else if (rand_num >= 8 && rand_num <= 15)
						class loot_shotgun_ammo* lut2 = new loot_shotgun_ammo(getgame(), st->getposition());
					else if (rand_num >= 16 && rand_num <= 18)
						class loot_emp* lut0 = new loot_emp(getgame(), st->getposition());
					else if (rand_num >= 19 && rand_num <= 20)
						class loot_life* lut3 = new loot_life(getgame(), st->getposition());

					st->setstate(dead);
					st->play_broke_impact_sfx();
					getgame()->remove_stone(st);
					st->get_damage_sprite()->stack_damage(dph);
				}
				else
				{
					st->getlife_sprite()->settimer(1);
					st->get_damage_sprite()->stack_damage(dph);
					float newlife = st->getlife_sprite()->getlife_stat();
					newlife -= dph;
					st->getlife_sprite()->setlife(newlife);
				}
			}
		}
	}
}
