#pragma once
#include"Object.h"
#include"Circlecomponent.h"
#include"Life_Spritecomponent.h"
#include"movecomponent.h"

class stones :public Object
{
public:
	stones(class Game* game);
	class Movecomponent* get_movecomponent()const { return move; }
	class Circlecomponent* getcircle()const { return mcircle; }
	class Life_Spritecomponent* getlife_sprite()const { return mlifesprite; }
	class Damage_counter_Sprite* get_damage_sprite()const { return damage_sprite; }
	void play_broke_impact_sfx() { Mix_PlayChannel(3, broke_impact, 0); }
	//int get_id()const { return mid; }
	//void set_id(int id) { mid = id; }
	void updateObject(float deltatime)override;
	void manage_collision_stone_vs_ship();
	float get_emp_renew_timer() { return emp_renew_timer; }
	void set_emp_renew_timer() { emp_renew_timer -= 0.1; }
	
private:
	Mix_Chunk* ship_taking_damag;//channel
	Mix_Chunk* broke_impact;
	class Circlecomponent* mcircle;
	class Life_Spritecomponent* mlifesprite;
	class Damage_counter_Sprite* damage_sprite;
	class Movecomponent* move;
	//int mid;//my id
	//this pert is for damaging the ship...
	float ship_damage_timer;
	float emp_renew_timer=1.6;
};