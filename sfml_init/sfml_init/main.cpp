#include <iostream>
#include "Game.h"


using namespace std;
using namespace sf; // para desbloquer as rotinas do SFML

int main() {

	//Init srand

	srand(static_cast<unsigned>(time(NULL)));

	//Init Game Engine:

	Game game;

	while (game.running()) {

		//update

		game.update();
		
		//Render
		game.render();

	}

	//End app




	return 0;
}