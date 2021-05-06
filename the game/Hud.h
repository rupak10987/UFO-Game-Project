#pragma once
#include"Object.h"
class Hud :public Object
{
public:
	Hud(class Game* game);
	void updateObject(float deltatime)override;
protected:
	SDL_Texture* Shotgun_hud;
	SDL_Texture* Sniper_hud;
	SDL_Texture* EMP_hud;
	std::vector<SDL_Texture*>hud_life_tex;
	
	class Spritecomponent_offset_position* smg_hud;
	class Spritecomponent_offset_position* special_bullet_hud;
	class Spritecomponent_offset_position* number_of_bullet_tex;
	class Spritecomponent_offset_position* Hud_life_sprite;

	int previous_frame_bulletnumber = 0;//this just for optimization
	int bullet_num;
	int previous_frame_life;
	int now_life;
};
