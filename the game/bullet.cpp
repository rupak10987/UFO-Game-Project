#include"bullet.h"
#include"Circlecomponent.h"
#include"Spritecomponent.h"
#include"movecomponent.h"
#include"stones.h"
#include"loot_shotgun_ammo.h"
#include"loot_sniper_ammo.h"
#include"loot_emp.h"
#include"Damage_counter_Sprite.h"
#include"loot_life.h"
bullet::bullet(class Game* game, Vector2 pos, float rot):
	Object(game),
	lifetime(500.0)
{
	id = 1;
	setposition(pos);
	setrotation(rot);
	load_bullet();
}
void bullet::load_bullet()
{
	gunshot = getgame()->get_sfx("ship_assets/sfx_wav/alternator.wav");
	mcircle = new Circlecomponent(this, 3, 8);
	sp = new Spritecomponent(this, 5, 3);
	sp->settextue(getgame()->gettexture("ship_assets/bullet3.png"));
	move = new Movecomponent(this, mcircle,0);
	move->setangularspeed(0);
	move->setforwardspeed(1000);
}
void bullet::updateObject(float deltatime)
{
	if (lifetime != 0)
	{
		lifetime--;
		if (lifetime == 1)
		{
			setstate(dead);
		}
    }

	for (auto st : getgame()->getstones())
	{
			// collision with stone vs bullet
			if (mcircle->intersect((mcircle), st->getcircle()))
			{
				if(st->getlife_sprite()->getlife_stat()<=dph)
				{
					int rand_num = rand() % 21;

				         if (rand_num >= 0 && rand_num <= 7)
					    class loot_sniper_ammo* lut1 = new loot_sniper_ammo(getgame(), st->getposition());
					else if (rand_num >= 8 && rand_num <= 15)
						class loot_shotgun_ammo* lut2 = new loot_shotgun_ammo(getgame(), st->getposition());
					else if (rand_num >= 16 && rand_num <= 18)
					    class loot_emp* lut0 = new loot_emp(getgame(), st->getposition());
					else if (rand_num >=19 && rand_num<=20)
						class loot_life* lut3 = new loot_life(getgame(), st->getposition());

				st->get_damage_sprite()->stack_damage(dph);
				st->setstate(dead);
				st->play_broke_impact_sfx();
				getgame()->remove_stone(st); 
				}
				else
				{
					st->getlife_sprite()->settimer(1);
					st->get_damage_sprite()->stack_damage(dph);
					float newlife= st->getlife_sprite()->getlife_stat();
					newlife-=dph;
					st->getlife_sprite()->setlife(newlife);
				}
				lifetime = 2;//this is for over surity
				setstate(dead);
				break;
			}
	}
	if(getposition().x>=1066 || getposition().x <= 0 || getposition().y >= 600 || getposition().y <= 0)
	setstate(dead);
}


Vector2 bullet::recoil(Vector2 target)
{
	Vector2 normal;
	normal.x = -target.y;
	normal.y = target.x;
	float number = (rand() % 7)-3;
	number /= 10;
	Vector2 result = (number * normal) + target;
	return result;
}