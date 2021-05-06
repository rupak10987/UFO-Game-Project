#pragma once
#include"Object.h"
#include"Circlecomponent.h"
#include"Life_Spritecomponent.h"
class Ship : public Object
{
public:
	enum  special_magazine
	{
	smg,
    sniper,
	shotgun,
	emp,
	lazer
	};
	Ship(class Game* game);
	void updateObject(float deltatime)override;	
	float gettimer()const { return timer; }
	void settimer(float time) { timer = time; }
	void keyboard(const Uint8* kstate)override;

	void set_current_bullet_sec(float bps) { current_bull_sec = bps; }

	int get_mag_size()const { return magazine_size; }
	special_magazine get_magazinetype()const { return magazine_type; }
	void set_mag_size(int x) { magazine_size = x;}
	void set_mag_type(special_magazine stat) { magazine_type = stat; }

	class Circlecomponent* getcircle()const { return mcircle; }
	class Life_Spritecomponent* getlife(){ return mlife; }

	float getcurrent_speed()const { return mcurrent_speed; }
	void setcurrent_speed(float s) { mcurrent_speed = s; }
private:
	float mcurrent_speed;
	class Animation_sprite* material;
	std::vector<SDL_Texture*>animation_normal;
	std::vector<SDL_Texture*>animation_boosted;
	class Circlecomponent* mcircle;
	class Life_Spritecomponent* mlife;
	special_magazine magazine_type=shotgun;
	bool boosted = false;
	int magazine_size = 3;
	int sfx_channel = 0;
	float timer=1.5;//its complicated.. this is mainly bullets delay
	float current_bull_sec;
};