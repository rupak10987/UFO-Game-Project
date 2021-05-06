#pragma once
#include"Component.h"
class Spritecomponent :public Component
{
public:
	Spritecomponent(class Object* owner, int c_order, int draworder);
	~Spritecomponent()override;
	virtual void settextue(SDL_Texture* mtx);
	void update(float deltatime)override;
	virtual void draw();
	int getdraworder()const { return mdraworder; }
	void set_should_rotate(bool arg) { should_rotate = arg; }
protected:
	int mdraworder;
	//this should be updated by query texture....
	int mytexwidth;
	int mytexheight;
	SDL_Texture* mtexture;
	SDL_Rect mrect;
	bool should_rotate;
};
