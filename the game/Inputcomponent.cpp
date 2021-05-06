#include"Inputcomponent.h"
#include"bullet.h"
#include"Ship.h"
Inputcomponent::Inputcomponent(class Object* owner, int c_order):
	Movecomponent(owner,nullptr,c_order)
{

}
void Inputcomponent::processinput(const Uint8* kstate)
{
	float fspeed = 0.0;
	mowner->getgame()->getship()->setcurrent_speed(fspeed);
	if (kstate[forward_key])
	{
		fspeed = 200.0;	
		mowner->getgame()->getship()->setcurrent_speed(fspeed);
		if (kstate[SDL_SCANCODE_LSHIFT])
		{
			fspeed = 300.0;
			mowner->getgame()->getship()->setcurrent_speed(fspeed);
			
		}
	}
	if (kstate[backword_key])
	{
		fspeed = -200.0;
		mowner->getgame()->getship()->setcurrent_speed(fspeed);
		if (kstate[SDL_SCANCODE_LSHIFT])
		{
			fspeed = -300.0;
			mowner->getgame()->getship()->setcurrent_speed(fspeed);
		}
	}
	setforwardspeed(fspeed);
	float rspeed = 0.0;
	mowner->getgame()->getship()->setcurrent_speed(fspeed);
	if (kstate[anticlockwise_key])
	{
		
		rspeed = 6;
	}
	if (kstate[clockwise_key])
	{
		
		rspeed = -6;
	}
	setangularspeed(rspeed);
	
}
void Inputcomponent::setkeys(int w, int s, int a, int d, int space)
{
	forward_key = w;
	backword_key = s;
	anticlockwise_key = a;
	clockwise_key = d;
	fire_key = space;
}
