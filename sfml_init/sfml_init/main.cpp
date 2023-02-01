#include <iostream>
#include "Game.h"


using namespace std;
using namespace sf; // unlock functions from SFML

int main() {

	//Init srand

	srand(static_cast<unsigned>(time(NULL)));

	//Init Game Engine:

	Game game;

	while (game.running() and game.getEndGame() == false) {

		//update

		game.update();
		
		//Render
		game.render();

	}

	//End app




	return 0;
}