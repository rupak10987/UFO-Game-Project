#include"Game.h"
#include"iostream"
#include"Object.h"
#include"Ship.h"
#include"Spritecomponent.h"
#include"Component.h"
#include"background.h"
#include"stones.h"
#include"bullet.h"
#include"SDL_ttf.h"
#include"Hud.h"
using namespace std;
bool Game::initialize()
{
	cout << "Initializing Game.." << endl;
	if (!SDL_Init(SDL_INIT_EVERYTHING))
	{
		IMG_Init(NULL);
		TTF_Init();
		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048);
		mwindow = SDL_CreateWindow("the game engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1066, 600, NULL);
		cout << "window created successfully" << endl;
		mrenderer = SDL_CreateRenderer(mwindow, 1, NULL);
		cout << "renderer created successfully" << endl;
		loaddata();
		return true;
	}
	else
	{
		cout << "failed to init" << endl;
		return false;
	}
	
}
void Game::Cache(const char* fname)
{
	int mytexwidth;
	int mytexheight;
	SDL_Rect temprect;
	temprect.x = 100;
	temprect.y = 100;
	SDL_Texture* tx = gettexture(fname);
	SDL_QueryTexture(tx, nullptr, nullptr, &mytexwidth, &mytexheight);
	temprect.w = mytexwidth;
	temprect.h = mytexheight;
	SDL_SetRenderDrawColor(mrenderer, 200, 200, 100, 255);
	SDL_RenderClear(mrenderer);
	SDL_RenderCopy(mrenderer, tx, NULL, &temprect);
	SDL_RenderCopy(mrenderer, loading, NULL, NULL);
	SDL_RenderPresent(mrenderer);	
}
void Game::loaddata()
{
	b = new background(this);
	p = new Ship(this);
	hud = new Hud(this);
	for (int i = 1; i < 14; i++)
	{
		class stones* s = new stones(this);
		s->id = 10+i;
	}
	loading = gettexture("ship_assets/LOADING.png");
	load_all_possible_tex_at_start();
	load_all_possible_sfx_at_start();
	//deltatime init segment
	mticks = SDL_GetTicks();
}
void Game::runloop()
{
	//handleinput();
	update();
	draw();
}

void Game::update()
{
	float deltatime = ((SDL_GetTicks() - mticks) / 1000.0); 
	fps++;
	/*if (SDL_GetTicks() % 1000 == 0)
	{
		cout << "FPS = " << fps<< endl;
		fps = 0;
	}*/
	mticks = SDL_GetTicks();
	if (deltatime >= 0.009)
	{
		deltatime = 0.009;
	}
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			running = false;
			break;
		}
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (auto ob : mobjects)
	{
    	ob->keyboard(state);
		ob->update(deltatime);
	}
	//strat
	for (auto ob : mpending_objects)
	{
		mobjects.emplace_back(ob);
	}
	mpending_objects.clear();
	//end
	std::vector<class Object*> deadobjects;
	for (auto ob : mobjects)
	{
		if (ob->getstate() == Object::dead)
		{
			deadobjects.emplace_back(ob);
		}
	}
	for (auto ob : deadobjects)
	{
		delete ob;
	}
}
void Game::draw()
{
	SDL_SetRenderDrawColor(mrenderer, 100, 100, 100, 255);
	SDL_RenderClear(mrenderer);
	for(auto sp:msprites)
	{
		sp->draw();
	}
	SDL_RenderPresent(mrenderer);
}
void Game::shutdown()
{
	SDL_DestroyRenderer(mrenderer);
	SDL_DestroyWindow(mwindow);
	delete this;
	SDL_Quit();
}
Game::~Game()
{
	for (auto ob : mobjects)
	{
		removeobject(ob);
	}
}
void Game::addobject(class Object* ob)
{

	//mobjects.emplace_back(ob);
	//start
	mpending_objects.emplace_back(ob);
	
}
void Game::removeobject(class Object* ob)
{
	auto iter = find(mobjects.begin(), mobjects.end(), ob);
	if (iter != mobjects.end())
	{
		iter_swap(iter, mobjects.end() - 1);
		mobjects.pop_back();
	}
	else
	{
		mobjects.pop_back();
	}
}
void Game::add_stone(class stones* stone)
{
	mstones.emplace_back(stone);
}
void Game::remove_stone(class stones* stone)
{
	auto iter = std::find(mstones.begin(), mstones.end(), stone);
	if (iter != mstones.end())
	{
	std:iter_swap(iter, mstones.end() - 1);
		mstones.pop_back();
	}
	else
	{
		mstones.pop_back();
	}
}
SDL_Texture* Game::gettexture(const char* filename)
{
	SDL_Texture* mtex=nullptr;
	auto iter = mtextures.find(filename);
	if (iter != mtextures.end())
	{
		mtex = iter->second;
		return mtex;
	}
	else
	{
		SDL_Surface* temp = IMG_Load(filename);
		mtex = SDL_CreateTextureFromSurface(mrenderer, temp);
		SDL_FreeSurface(temp);
		mtextures.emplace(filename, mtex);
		return mtex;
	}
}
Mix_Chunk* Game::get_sfx(const char* filename)
{
	Mix_Chunk* sfx = nullptr;
	auto iter = m_sfx.find(filename);
	if (iter != m_sfx.end())
	{
		sfx = iter->second;
		return sfx;
	}
	else
	{
		sfx = Mix_LoadWAV(filename);
		m_sfx.emplace(filename, sfx);
		return sfx;
	}
}
SDL_Texture* Game::get_text_as_texture(const char* filename, SDL_Color col, int size)
{
	SDL_Texture* mtex = nullptr;
	auto iter = mtextures.find(filename);
	if (iter != mtextures.end())
	{
		mtex = iter->second;
		return mtex;
	}
	else
	{
		TTF_Font* font = TTF_OpenFont("ship_assets/fonts/OCRAEXT.TTF", size);
		SDL_Surface* temp = TTF_RenderText_Solid(font, filename, col);
		mtex = SDL_CreateTextureFromSurface(mrenderer, temp);
		SDL_FreeSurface(temp);
		return mtex;
	}
}
void Game::addsprite(class Spritecomponent* msprt)
{
	int draworder;
	draworder = msprt->getdraworder();
	auto iteration = msprites.begin();
	while (iteration != msprites.end())
{
		if ((*iteration)->getdraworder() >= draworder)
		break;
		else
		iteration++;	
}
	msprites.insert(iteration, msprt);
}
void Game::removesprite(class Spritecomponent* msprt)
{
	auto iter = std::find(msprites.begin(), msprites.end(), msprt);
	msprites.erase(iter);
}








void Game:: load_all_possible_tex_at_start()
{
	//bullets............................
	gettexture("ship_assets/bullet3.png");
	Cache("ship_assets/bullet3.png");
	gettexture("ship_assets/bullet1.png");
	Cache("ship_assets/bullet1.png");
	gettexture("ship_assets/bullet2.png");
	Cache("ship_assets/bullet2.png");
	//loots................................
	stringstream filename_inital1;
	stringstream filename_inital2;
	string filename;
	filename_inital1 << "ship_assets/loot_shotgun_ammo/000";
	filename_inital2 << "ship_assets/loot_shotgun_ammo/00";
	for (int j = 1; j <= 59; j++)
	{
		stringstream num;;
		num << j;
		if (j < 10)
			filename = filename_inital1.str() + num.str() + ".png";
		else
			filename = filename_inital2.str() + num.str() + ".png";
		gettexture(filename.c_str());
		Cache(filename.c_str());
	}
	stringstream filename_inital3;
	stringstream filename_inital4;
	string filename1;
	filename_inital3 << "ship_assets/loot_sniper_amo/000";
	filename_inital4 << "ship_assets/loot_sniper_amo/00";
	for (int j = 1; j <= 59; j++)
	{
		stringstream num;;
		num << j;
		if (j < 10)
			filename1 = filename_inital3.str() + num.str() + ".png";
		else
			filename1 = filename_inital4.str() + num.str() + ".png";
		gettexture(filename1.c_str());
		Cache(filename1.c_str());
	}
	stringstream filename_inital5;
	stringstream filename_inital6;
	string filename2;
	filename_inital5 << "ship_assets/loot_emp/000";
	filename_inital6 << "ship_assets/loot_emp/00";
	for (int j = 1; j <= 59; j++)
	{
		stringstream num;;
		num << j;
		if (j < 10)
			filename2 = filename_inital5.str() + num.str() + ".png";
		else
			filename2 = filename_inital6.str() + num.str() + ".png";
		gettexture(filename2.c_str());
		Cache(filename2.c_str());
	}
	//............................emp effect
	stringstream filename_inital7;
	stringstream filename_inital8;
	string filename3;
	filename_inital7 << "ship_assets/emp_trial/000";
	filename_inital8 << "ship_assets/emp_trial/00";
	for (int j = 1; j <= 20; j++)
	{
		stringstream num;;
		num << j;
		if (j < 10)
			filename3 = filename_inital7.str() + num.str() + ".png";
		else if (j >= 10 && j < 100)
			filename = filename_inital8.str() + num.str() + ".png";
		gettexture(filename3.c_str());
		Cache(filename3.c_str());
	}
	//lifes.....
	gettexture("ship_assets/life3.png");
	gettexture("ship_assets/life2.png");
	//numbers.............
	stringstream number;
	string show;
	for (int i = 1; i <= 50; i++)
	{
		number << i;
		show = "-" + number.str();
		SDL_Color col = { 10,10,10,255 };
		get_text_as_texture(show.c_str(),col,12);
	}
	stringstream filename_inital9;
	stringstream filename_inital10;
	string filename4;
	filename_inital9 << "ship_assets/hud_life_circle/000";
	filename_inital10 << "ship_assets/hud_life_circle/00";
	for (int j = 0; j <= 50; j++)
	{
		stringstream num;;
		num << j;
		if (j < 10)
			filename4 = filename_inital9.str() + num.str() + ".png";
		else
			filename4 = filename_inital10.str() + num.str() + ".png";
		gettexture(filename4.c_str());
		Cache(filename4.c_str());
	}
}
void Game::load_all_possible_sfx_at_start()
{
	get_sfx("ship_assets/sfx_wav/alternator.wav");
	get_sfx("ship_assets/sfx_wav/g7_as_bolt_action.wav");
	get_sfx("ship_assets/sfx_wav/mastif.wav");
	get_sfx("ship_assets/sfx_wav/mozambique.wav");
	get_sfx("ship_assets/sfx_wav/break.mp3");
	get_sfx("ship_assets/sfx_wav/equip.wav");
	get_sfx("ship_assets/sfx_wav/ship_taking_damage.mp3");
}
