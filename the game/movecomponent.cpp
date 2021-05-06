#include"movecomponent.h"
#include"Object.h"
#include"stones.h"
Movecomponent::Movecomponent(class Object* owner, class Circlecomponent* c, int c_order) :
	Component(owner, c_order),
	forwardspeed(0.0),
	angularspeed(0.0)
{
	mcir = c;
}
void Movecomponent::update(float deltatime)
{
	float rotation_temp = mowner->getrotation();
	rotation_temp += deltatime * angularspeed;
	mowner->setrotation(rotation_temp);
	//cout << rotation_temp << endl;
	f = mowner->getposition();
	f += deltatime * forwardspeed * mowner->getforward();
	//screen rapping.......................
	
	if (f.x >= 1066-(mowner->getcircle()->getradius()))
	{
	
		//f.x = 0;
		if (mowner->id != 1)
		{
			if (mowner->id == 0)
			{
				f.x -= (mowner->getcircle()->getradius()) - (1066 - (mowner->getposition().x));
			}
			else
			{
				mowner->setrotation(-mowner->getrotation() + 3.1415);
				//f += deltatime * forwardspeed * mowner->getforward();
				f.x -= (mowner->getcircle()->getradius()) - (1066 - (mowner->getposition().x));
			}
		}
	}
	else if(f.x<=0+ (mowner->getcircle()->getradius()))
	{
		
		//f.x = 1066;
		if (mowner->id != 1)
		{
			if (mowner->id == 0)
			{
				f.x += (mowner->getcircle()->getradius()) - mowner->getposition().x;
			}
			else
			{
				mowner->setrotation(-mowner->getrotation() + 3.1415);
				//f += deltatime * forwardspeed * mowner->getforward();
				f.x += (mowner->getcircle()->getradius()) - mowner->getposition().x;
			}
		
		}
	}
	if (f.y <= 0+ (mowner->getcircle()->getradius()))
	{
		
		//f.y = 600;
		if (mowner->id != 1)
		{
			if (mowner->id == 0)
			{
				f.y += (mowner->getcircle()->getradius()) - mowner->getposition().y;
			}
			else
			{
				mowner->setrotation(-mowner->getrotation() + 2 * 3.1415);
				//f += deltatime * forwardspeed * mowner->getforward();
				f.y += (mowner->getcircle()->getradius()) - mowner->getposition().y;
			}
			
		}
	}
	else if (f.y >= 600- (mowner->getcircle()->getradius()))
	{
	
		//f.y = 0;
		if (mowner->id != 1)
		{
			if (mowner->id == 0)
			{
				f.y -= (mowner->getcircle()->getradius()) - (600 - (mowner->getposition().y));
			}
			else 
			{
				mowner->setrotation(-mowner->getrotation() + 2 * 3.1415);
				//f += deltatime * forwardspeed * mowner->getforward();
				f.y -= (mowner->getcircle()->getradius()) - (600 - (mowner->getposition().y));
			}
		
		}

	}
	mowner->setposition(f);
	
}
void Movecomponent::svs(float deltatime)
{
	vector<class stones*>sts = mowner->getgame()->getstones();
	for (auto sex : sts)
	{
		if (mowner->id != sex->id)
		{
			if (mcir->intersect(mcir, sex->getcircle()))
			{
				//this portion should be in ccomp
				//end of the portion
					Vector2 a = (this->mowner->getforward()) * forwardspeed;
					Vector2 b = (sex->getforward()) * forwardspeed;
					Vector2 norm = (this->mowner->getposition()) - (sex->getposition());
					norm.Normalize();
					Vector2 tangv;
					tangv.x = -norm.y;
					tangv.y = norm.x;
					float a_initial_ncomp = Vector2::Dot(a, norm);
					float a_initial_tcomp = Vector2::Dot(a, tangv);
					float b_initial_ncomp = Vector2::Dot(b, norm);
					float b_initial_tcomp = Vector2::Dot(b, tangv);


					float a_fnv = b_initial_ncomp;
					float b_fnv = a_initial_ncomp;



					Vector2 afvn = a_fnv * norm;
					Vector2 bfvn = b_fnv * norm;
					Vector2 afvt = a_initial_tcomp * tangv;
					Vector2 bfvt = b_initial_tcomp * tangv;


					Vector2 a_final_vector = afvn + afvt;
					Vector2 b_final_vector = bfvn + bfvt;

					float ang_a = Math::Atan2(-a_final_vector.y, a_final_vector.x);
					float ang_b = Math::Atan2(-b_final_vector.y, b_final_vector.x);

					this->mowner->setrotation(ang_a);
					sex->setrotation(ang_b);		
			}
			
		}
	}

}