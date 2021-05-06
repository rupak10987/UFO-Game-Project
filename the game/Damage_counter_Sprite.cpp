#include"Damage_counter_Sprite.h"
#include"sstream"
Damage_counter_Sprite::Damage_counter_Sprite(class Object* owner, int c_order, int draworder, int offset_x, int offset_y) :
	Spritecomponent_offset_position(owner, c_order, draworder, offset_x, offset_y)
{

}
void Damage_counter_Sprite::update(float deltatime)
{
	if (timer > 0)
	{
		timer -= deltatime;
		if (timer <= 0)
		{
			total_damage = 0;
			damage_taken = 0;
		}
		total_damage += damage_taken;
		damage_taken = 0;
	}
	Spritecomponent_offset_position::update(deltatime);
}

void Damage_counter_Sprite::draw()
{
	if (timer > 0)
	{
		stringstream number;
		string show;
		number << total_damage;
		show = "-"+number.str();
		SDL_Color col = { 10,10,10,255 };
		settextue(mowner->getgame()->get_text_as_texture(show.c_str(), col, 12));

		SDL_RenderCopy((mowner->getgame()->getrenderer()), mtexture, NULL, &mrect);
	}
	
}
