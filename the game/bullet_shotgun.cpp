#include"bullet_shotgun.h"
#include"Spritecomponent.h"
#include"Circlecomponent.h"
#include"movecomponent.h"
bullet_shotgun::bullet_shotgun(class Game* game, Vector2 pos, float rot) :
	bullet(game, pos, rot)
{
	dph = 5;
	bullet_per_sec = 0.9;
	lifetime = 400;
	load_bullet();
}
void bullet_shotgun::load_bullet()
{
	gunshot = nullptr;
	gunshot = getgame()->get_sfx("ship_assets/sfx_wav/mastif.wav");
	delete sp;
	sp = new Spritecomponent(this, 5, 3);
	sp->settextue(getgame()->gettexture("ship_assets/bullet1.png"));
	move->setforwardspeed(1100);
}