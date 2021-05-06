#include"Animation_sprite.h"
#include"Spritecomponent.h"

Animation_sprite::Animation_sprite(class Object* owner, int c_order, int draworder,float fps) :
Spritecomponent(owner, c_order, draworder),
myfps(fps)
{
}
void Animation_sprite::update(float deltatime)
{
	Spritecomponent::update(deltatime);
	if (manimtextures.size() > 0)
	{
		mycurrentframe += (myfps * deltatime);
		if (mycurrentframe >= manimtextures.size())
		{
			mycurrentframe -= manimtextures.size();
		}
	}
	settextue(manimtextures[static_cast<int>(mycurrentframe)]);
}
void Animation_sprite::setanimatontextures(std::vector<SDL_Texture*>animtexts)
{
	manimtextures = animtexts;
	settextue(manimtextures[0]);
	mycurrentframe = rand()%manimtextures.size();
}