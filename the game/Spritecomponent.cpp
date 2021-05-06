#include"Spritecomponent.h"
Spritecomponent::Spritecomponent(class Object* owner, int c_order, int draworder) :
	Component(owner, c_order),
	mdraworder(draworder),
	should_rotate(true)
{
	mowner->getgame()->addsprite(this);
}
Spritecomponent::~Spritecomponent()
{
	mowner->getgame()->removesprite(this);
	
	
}
void Spritecomponent::settextue(SDL_Texture* mtx)
{
	mtexture = mtx;
	SDL_QueryTexture(mtexture, nullptr, nullptr, &mytexwidth, &mytexheight);
}
void Spritecomponent::update(float deltatime)
{
	int x = static_cast<int>(mowner->getposition().x);
	int y = static_cast<int>(mowner->getposition().y);
	mrect.x = x-((mytexwidth/2)*mowner->getscale());
	mrect.y = y-((mytexheight/2)*mowner->getscale());
	mrect.h = mowner->getscale()*mytexheight;
	mrect.w = mowner->getscale()* mytexwidth;
}
void Spritecomponent::draw()
{
	if (should_rotate)
	{
		SDL_RenderCopyEx(mowner->getgame()->getrenderer(), mtexture, NULL, &mrect, -Math::ToDegrees(mowner->getrotation()), NULL, SDL_FLIP_NONE);
	}
	else
	SDL_RenderCopy((mowner->getgame()->getrenderer()), mtexture, NULL, &mrect);
	
}