#pragma once
#include"Object.h"
#include"Game.h"
#include"Animation_sprite.h"
class background :public Object
{
public:
	background(class Game* game) :
		Object(game)
	{
		Vector2 pos;
		pos.x = 1066/2;
		pos.y = 300;
		setposition(pos);
		cout << "bg set..." << endl;
		class Spritecomponent* sp = new Spritecomponent(this, 1, 0);
		sp->settextue(getgame()->gettexture("ship_assets/normal_bg.png"));
		/*class Animation_sprite* material = new Animation_sprite(this, 1, 0, 24);
		std::vector<SDL_Texture*>animation;
		// from this section of this constructor its loading files
		stringstream filename_inital1;
		stringstream filename_inital2;
		string filename;

		filename_inital1 << "ship_assets/bg/00";
		filename_inital2 << "ship_assets/bg/0";
		for (int j = 36; j <= 200; j++)
		{
			stringstream num;;
			num << j;
			if (j < 100)
				filename = filename_inital1.str() + num.str() + ".png";
			else
				filename = filename_inital2.str() + num.str() + ".png";
			animation.emplace_back(game->gettexture(filename.c_str()));
		}
		material->setanimatontextures(animation);*/
	}
};