#pragma once
#include"Component.h"
class Circlecomponent :public Component
{
public:
	Circlecomponent(class Object* owner, int c_order, float rad);
	float getradius()const { return mradius; }
	void setradius(float rad) { mradius = rad; }
	bool intersect(Circlecomponent* a, Circlecomponent* b)
	{
		Vector2 distance = (a->mowner->getposition())- (b->mowner->getposition());
		float distance_squared = distance.LengthSq();
		float radsq = a->getradius() + b->getradius();
		radsq *= radsq;
		if (distance_squared <= radsq)
		{
			if (a->mowner->id == 0 || b->mowner->id ==0 || a->mowner->id == 1 || b->mowner->id == 1)
			{
				if (b->mowner->id == 0)
				{
					float d = distance.Length();
					distance.Normalize();
					float r = a->getradius() + b->getradius();
					float offset = (r - d);//whole actually
					offset = -offset;
					a->mowner->setposition(a->mowner->getposition() - distance * offset);
					//b->mowner->setposition(b->mowner->getposition() + distance * offset);
					return true;
				}
				return true;
			}
			float d = distance.Length();
			distance.Normalize();
			float r= a->getradius() + b->getradius();
			float offset = (r - d) /2;//not 2 actually
			offset = -offset;
			a->mowner->setposition(a->mowner->getposition() -  distance*offset);
			b->mowner->setposition(b->mowner->getposition() + distance*offset);
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	float mradius;
};
