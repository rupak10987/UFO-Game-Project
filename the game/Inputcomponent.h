#pragma once
#include"movecomponent.h"
class Inputcomponent :public Movecomponent
{
public:
	Inputcomponent(class Object* owner, int c_order);
	void processinput(const Uint8* kstate) override;
	void setkeys(int w, int s,int a,int d, int space);
private:
	int forward_key;
	int backword_key;
	int anticlockwise_key;
	int clockwise_key;
	int fire_key;
	
};