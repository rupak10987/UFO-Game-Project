#pragma once
#include"Object.h"
#include"Circlecomponent.h"
#include"Animation_sprite.h"
#include"Spritecomponent.h"
class EMP :public Object
{
public:
	EMP(class Game* game, Vector2 pos);
	void updateObject(float deltatime)override;
	float get_bullet_per_sec() { return bullet_persec; }
	void mix_play_emp_effect() { Mix_PlayChannel(0, emp_effect_sfx, 0); }
private:
	Mix_Chunk* emp_effect_sfx;
	class Circlecomponent* mcircle;
	class Animation_sprite* material;
	float bullet_persec=0.5;
	int dph = 10;
	float emp_max_radius=150;
};