#pragma once
#include"Game.h"
#include"Component.h"

using namespace std;
class Object
{
public:
	enum state
	{
		Active,
		updating,
		dead
	};
	Object(class Game* game);
	virtual ~Object();
	//for collision
	float id;
	bool incollison = false;
	state getstate() const
	{
		return mstate;
	}
	void setstate(state comingstate)
	{
		mstate = comingstate;
	}
	//getters and setters all needs to be impolemented in the subclasses
	virtual class Circlecomponent* getcircle()const { return nullptr; }
	float getscale() const { return mscale; }

	float getrotation() const { return mrotation; }

	Vector2 getposition() const { return mposition; }

	Vector2 getforward()const;

	void setscale(float scale) { mscale = scale; }

	void setrotation(float rotation) { mrotation = rotation; }

	void setposition(Vector2 postion) { mposition = postion; }

	bool getcollision_stat()const { return collision; }

	void setcollision_stat(bool val) { collision = val; }
// update not to be overridden
void update(float deltatime);

virtual void updateObject(float deltatime) {}

virtual void keyboard(const Uint8* kstate);

void updatecomponents(float deltatime);

void addcomponents(class Component* comp);

class Game* getgame() { return mgame; }

void remove_all_components();

void removecomponent(class Component* comp);
private:
	state mstate;
	Game* mgame;
	float mscale;
	Vector2 mposition;
	float mrotation;
	vector<class Component*>mcomponents;
	bool collision = false;
};
