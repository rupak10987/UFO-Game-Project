#include"Game.h"
#include"time.h"
using namespace std;
int main(int argc, char** argv)
{
	srand(time(NULL));
	cout << "hello" << endl;
	Game* game = new Game;
	if (game->initialize())
	{
		while (game->running)
		{
			game->runloop();
		}
		game->shutdown();
	}
	return 0;
}