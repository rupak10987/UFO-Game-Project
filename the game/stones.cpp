#include"stones.h"
#include"movecomponent.h"
#include"Spritecomponent.h"
#include"Animation_sprite.h"
#include"Ship.h"
#include"sstream"
#include"Damage_counter_Sprite.h"
stones::stones(class Game* game):
	Object(game)
{
	game->add_stone(this);
	float rot = Math::ToRadians(rand() % 361);
	Vector2 p;
	p.x = 50+ (rand() % 1017);
	p.y = 50+ (rand() % 550);
	setposition(p);
	setrotation((rot));
	// animation textures..................................................................
	class Animation_sprite* sp = new Animation_sprite(this, 1, 1, 50);
	sp->set_should_rotate(false);
	vector<SDL_Texture*> material;
	string filename1;
	string filename2;
	int random = rand() % 11;
	if (random <5)
	{
		filename1 = "ship_assets/stone_animated/000";
		filename2 = "ship_assets/stone_animated/00";
	}
	else
	{
		filename1 = "ship_assets/stone_animated3/000";
		filename2 = "ship_assets/stone_animated3/00";
	}
	string file;
	for (int j = 1; j < 60; j++)
	{
		stringstream num;
		num << j;
		if (j < 10)
		{
			file = filename1 + num.str() + ".png";
		}
		else
		{
			file = filename2 + num.str() + ".png";
		}
		material.emplace_back(getgame()->gettexture(file.c_str()));
	}
	sp->setanimatontextures(material);


	// life texture.................................
	mlifesprite = new Life_Spritecomponent(this, 3, 4, 50);
	SDL_Texture* li = game->gettexture("ship_assets/life3.png");
	mlifesprite->settextue(li);


	//circle.......................................
	mcircle = new Circlecomponent(this, 5, 25);


	//movement.....................................
	move = new Movecomponent(this,mcircle, 0);
	move->setangularspeed(0.2);//0.2
	move->setforwardspeed(200);


	// damage stack
	damage_sprite = new Damage_counter_Sprite(this, 5, 6, -12, -45);

	broke_impact = getgame()->get_sfx("ship_assets/sfx_wav/break.mp3");
	ship_taking_damag = getgame()->get_sfx("ship_assets/sfx_wav/ship_taking_damage.mp3");
}

void stones::manage_collision_stone_vs_ship()
{
	if (getgame()->getship()->getlife()->getlife_stat()<2)
	{
		getgame()->running = false;
		return;
	}
	else
	{
		getgame()->getship()->getlife()->settimer(1);
		float newlife = (getgame()->getship()->getlife()->getlife_stat());
		newlife -= 2;
		getgame()->getship()->getlife()->setlife(newlife);
		Mix_PlayChannel(4, ship_taking_damag, 0);
	}
	//just tryin out bro.....
	Vector2 a = (this->getforward())*get_movecomponent()->getforwardsped();
	Vector2 b = this->getgame()->getship()->getforward() * this->getgame()->getship()->getcurrent_speed();
	Vector2 norm = (this->getposition()) - (this->getgame()->getship()->getposition());
	norm.Normalize();
	Vector2 tangv;
	tangv.x = -norm.y;
	tangv.y = norm.x;
	float a_initial_ncomp = Vector2::Dot(a, norm);
	float a_initial_tcomp = Vector2::Dot(a, tangv);
	float b_initial_ncomp = Vector2::Dot(b, norm);
	float b_initial_tcomp = Vector2::Dot(b, tangv);


	float a_fnv = b_initial_ncomp;
	float b_fnv = a_initial_ncomp;



	Vector2 afvn = a_fnv * norm;
	Vector2 bfvn = b_fnv * norm;
	Vector2 afvt = a_initial_tcomp * tangv;
	Vector2 bfvt = b_initial_tcomp * tangv;


	Vector2 a_final_vector = afvn + afvt;
	Vector2 b_final_vector = bfvn + bfvt;

	float ang_a = Math::Atan2(-a_final_vector.y, a_final_vector.x);
	float ang_b = Math::Atan2(-b_final_vector.y, b_final_vector.x);

	this->setrotation(ang_a);
	//end of trying
}

void stones::updateObject(float deltatime)
{

	if (ship_damage_timer< 1)
	{
		ship_damage_timer -= deltatime;
		if (ship_damage_timer <0)
		{
			ship_damage_timer = 1;
		}
		
	}
	if (mcircle->intersect(mcircle, getgame()->getship()->getcircle()) && getgame()->getship()->getstate()==Object::Active)
	{
		if (ship_damage_timer >= 1)
		{
			ship_damage_timer -= deltatime;
			manage_collision_stone_vs_ship();
		}
	}
	if (emp_renew_timer < 1.6)
	{
	emp_renew_timer -= deltatime;
		if (emp_renew_timer <= 0)
		emp_renew_timer = 1.6;
	}
	//trying....
	move->svs(deltatime);
}
