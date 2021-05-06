#include"Life_Spritecomponent.h"
Life_Spritecomponent::Life_Spritecomponent( class Object* owner, int c_order, int draworder, float mlife) :
	Spritecomponent(owner, c_order, draworder),
	max_life(mlife)
{
	life = max_life;
	lifetimer = 0;
}
void Life_Spritecomponent::update(float deltatime)
{  
	if (life > max_life)
	{
		life = max_life;
	}
	if(lifetimer>0)
	lifetimer -= deltatime;
	mytexwidth = life;
	Spritecomponent::update(deltatime);
	mrect.y = mowner->getposition().y - 32;
}
void Life_Spritecomponent::draw()
{
	if(lifetimer>0)
	SDL_RenderCopy((mowner->getgame()->getrenderer()), mtexture, NULL, &mrect);
}
void Life_Spritecomponent::settextue(SDL_Texture* mtx)
{
	mtexture = mtx;
	mytexwidth = life;
	mytexheight = 3;
}