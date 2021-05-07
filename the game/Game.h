#pragma once
#include"iostream"
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
#include"vector"
#include"Math.h"
#include"Object.h"
#include"string"
#include"sstream"
#include<map>
using namespace std;
class Game
{
public:
	Game()
	{
		cout << "log0:game object created" << endl;
		running = true;
	}
	~Game();
	bool initialize();
	void runloop();
	void shutdown();
	SDL_Renderer* getrenderer()const { return mrenderer; }
	vector<class stones*> getstones()const{ return mstones; }

	class Ship* getship()const { return p; }
	void load_all_possible_tex_at_start();
	void load_all_possible_sfx_at_start();
	bool running;
	void addobject(class Object* ob);
	void removeobject(class Object* ob);
	void addsprite(class Spritecomponent* msprt);
	void removesprite(class Spritecomponent* msprt);
	void add_stone(class stones* stone);
	void remove_stone(class stones* stone);
	SDL_Texture* gettexture(const char* filename);
	SDL_Texture* get_text_as_texture(const char* filename, SDL_Color col, int size);
	Mix_Chunk* get_sfx(const char* filename);
private:
	//functions.......
	void Cache(const char* fname);
	void loaddata();
	void handleinput();
	void update();
	void draw();
	void updateObjects();
	//elements........
	int fps;
	std::map<std::string, SDL_Texture*>mtextures;
	std::map<std::string, Mix_Chunk*>m_sfx;
	Uint32 mticks;
	SDL_Window* mwindow;
	SDL_Renderer* mrenderer;
	int test = 0;
	std::vector<class Object*>mobjects;
	std::vector<class Object*>mpending_objects;
	std::vector<class Spritecomponent*>msprites;
	std::vector<class stones*> mstones;
	class Ship* p;
	class background* b;
	class Hud* hud;
	SDL_Texture* loading;
};
