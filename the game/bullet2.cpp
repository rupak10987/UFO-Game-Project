#include"bullet2.h"
#include"Spritecomponent.h"
#include"Circlecomponent.h"
#include"movecomponent.h"
bullet2::bullet2(class Game* game, Vector2 pos, float rot) :
	bullet(game, pos, rot)
{
	dph = 15;
	bullet_per_sec = 0.65;
	lifetime = 1500;
	load_bullet();
}
void bullet2::load_bullet()
{
	gunshot = nullptr;
	gunshot = getgame()->get_sfx("ship_assets/sfx_wav/g7_as_bolt_action.wav");
	delete sp;
	sp = new Spritecomponent(this, 5, 3);
	sp->settextue(getgame()->gettexture("ship_assets/bullet2.png"));
	move->setforwardspeed(1500);
}