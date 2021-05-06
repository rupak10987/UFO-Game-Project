#pragma once
#include"Object.h"
#include"Spritecomponent.h"
class bullet :public Object
{
public:
	bullet(class Game* game, Vector2 pos, float rot);
	void updateObject(float deltatime)override;
	virtual void load_bullet();
	class Circlecomponent* getcircle()const { return mcircle; }
	void set_dph(float dp) { dph = dp; }
	float get_bullet_per_sec()const { return bullet_per_sec; }
	void play_gunshot_sfx(int chanel) { Mix_PlayChannel(chanel, gunshot, 0); }
	virtual Vector2 recoil(Vector2 target);
protected:
	Mix_Chunk* gunshot;
	class Spritecomponent* sp;
	class Circlecomponent* mcircle;
	class Movecomponent* move;
	float dph = 4;
	float bullet_per_sec=10;
	float lifetime;
};