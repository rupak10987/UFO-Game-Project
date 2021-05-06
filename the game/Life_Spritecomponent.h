#pragma once
#include"Spritecomponent.h"
#include"stones.h"
class Life_Spritecomponent : public Spritecomponent
{
public:
	Life_Spritecomponent( class Object* owner, int c_order, int draworder, float mlife);
	void settextue(SDL_Texture* mtx)override;
	void update(float deltatime)override;
	void draw()override;
	//main part of the component......................
	void setlife(float li) { life = li; }
	float getlife_stat()const { return life; }
	void settimer(float time) { lifetimer = time; }
private:
	float life;
	float lifetimer;
	float max_life;
};