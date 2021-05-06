#pragma once
#include"Spritecomponent.h"
class Animation_sprite : public Spritecomponent
{
public:
Animation_sprite(class Object* owner, int c_order, int draworder, float fps);
void update(float deltatime)override;
void setanimatontextures(std::vector<SDL_Texture*>animtexts);
void set_current_frame(int frm) { mycurrentframe = frm; }// to be used after setting animation textures
void set_fps(float fps) { myfps=fps; }
protected:
	std::vector<SDL_Texture*>manimtextures;
	float myfps;
	float mycurrentframe;
};