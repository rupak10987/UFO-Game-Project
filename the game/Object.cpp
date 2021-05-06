#include"Object.h"
Object::Object(class Game* game) :
	mstate(Active),
	mgame(game),
	mrotation(0.0),
	mscale(1)
{
	game->addobject(this);
	id = SDL_GetTicks();
}
Object::~Object()
{

	mgame->removeobject(this);
	while (!mcomponents.empty())
	{
		delete mcomponents.back();
	}
}

void Object::update(float deltatime)
{
	updatecomponents(deltatime);
	updateObject(deltatime);
}
void Object::addcomponents(class Component* comp)
{
	auto iter = mcomponents.begin();
	for (; iter != mcomponents.end(); iter++)
	{
		if (comp->get_cdraworder() <= (*iter)->get_cdraworder())
		{
			break;
		}
	}
	mcomponents.insert(iter, comp);
}
void Object::keyboard(const Uint8* key)
{
	for (auto iter : mcomponents)
	{
		iter->processinput(key);
	}
}
void Object::updatecomponents(float deltatime)
{
	
	for (auto comp : mcomponents)
	{
		comp->update(deltatime);
	}
}
//this has to delete
void Object::remove_all_components()
{
	for (auto comp : mcomponents)
	{
		delete comp;
	}
}
void Object::removecomponent(class Component* comp)
{
	auto iter = std::find(mcomponents.begin(), mcomponents.end(), comp);
	mcomponents.erase(iter);
}
Vector2 Object::getforward() const
{
	Vector2 vec;
	vec.x = (Math::Cos(mrotation));
	vec.y = -(Math::Sin(mrotation));
	return vec;
}
