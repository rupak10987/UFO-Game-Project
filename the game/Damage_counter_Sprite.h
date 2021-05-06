#pragma once
#include"Spritecomponent_offset_position.h"
class Damage_counter_Sprite :public Spritecomponent_offset_position
{
public:
	Damage_counter_Sprite(class Object* owner, int c_order, int draworder, int offset_x, int offset_y);
	void update(float deltatime)override;
	void draw()override;
	void stack_damage(float dmg)
	{ 
	damage_taken = dmg;
	timer = 0.5;
	}
private:
	float total_damage=0;
	float timer=0;
	float damage_taken = 0;
};