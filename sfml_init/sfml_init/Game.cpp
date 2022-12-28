#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr; // o window é do tipo apontador( ver as variáveis do Game.h)

	//Variables related to game logic
	this->endGame = false;
	this->points = 0;//Points earned when we kill the enemy
	this->enemySpawnTimerMax = 10.f;// Rate of enemy generation/spawning
	this->enemySpawnTimer = this->enemySpawnTimerMax;	
	this->maxEnemies = 5;
	this->mouseHeld = false; // Starts in "false" since in begining we are not holding the mouse...
	this->health = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;// mais fácil fazer o ajuste das dimensões do ecrã assim...
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode; para ir buscar a resolução do ecrã do pc directamente...
	this->window = new sf::RenderWindow(this->videoMode, "Game One", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);// ao invés de 144 fps é melhor baixar para 60, garante-se que em pc's rascas isto funciona
}



void Game::initEnemies()
{

	this->enemy.setPosition(300.f, 400.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, .5f));	//Diminuímos o enemy para metade
	this->enemy.setFillColor(sf::Color::Cyan); // fill enemy with cyan color...
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

Game::Game() {//Definição do construtor
	// Vai permitir chamar as funções que vão fazer as "coisas" aparecer no ecrã!...
	/// é necessário ter esta ordem, porque não vamos pretender inicializar o ecrã e só depois inicializar variáveis....
	this->initializeVariables();
	this->initWindow();	
	this->initEnemies();
}

Game::~Game() {//Definição do destructor
	delete this->window;// para evitar um grande memory leak...
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}



//Functions


void Game::spawnEnemy()
{
	/*
		@return void
		Spawns enemies and sets their colors and positions
		-Sets a random position
		-Sets a random color ( for random we use ctime lib
		-Adds enemy to the vector 
	*/

	/*
		rand() % this->window->getSize().x:
	    I am generating a random number between 0 and the window size in X Axis...
	    rand() % (this->window->getSize().x - this->enemy.getSize().x)
		The enemy, that is a square has it's left upper corner in upper left corner...
	      As the rand() function returns a number between 0 and right limit of our window,
		  because originaly i wrote "rand() % this->window->getSize().x", in limit the function can generate a number in X axis that force our enemy (rectangle) going outside our RenderWindow Window!!!

		  And because of that, we need to subtract that max distance in X axis, with the maximum size of rectangle in relation to X axis:

				-> rand() % (this->window->getSize().x - this->enemy.getSize().x)
	*/
	this->enemy.setPosition(
		//Generate a X coordinate between 0 and 500, since our height is 600 and lenght of rectangle is 100, we should't insert a rectangle beyond 500,since the rectangle can exceed our height window  

		// Note: rand() % 100 ->> means that we will generate a random number between 0 and 99, so in fact the 99 line is generating an integer between 0 and 499
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),0.f
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)) // o enemy aqui já vai com avanço, com 0.f o enemy começa lá em cima!
	
	);// esta função como parametros de entrada tem o float x e float y
	this->enemy.setFillColor(sf::Color::Green);

	//Spawn the enemy:
	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {// quando se invoca o "this" estamos a ir buscar variáveis,funções etc que pertencem à classe do objecto Game, que está definida no Game.h
		
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();			
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		}

	}
}

void Game::updateMousePositions()
{
	/*@return void
	  updates the mouse positions
	    - Mouse position relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);// não esquece que o window é um pointer logo o this temos de referenciar
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);//We take our mouse positions in window,secondly this positions are mapped to floats. Finally this floats are mapped to our View
}

void Game::updateEnemies()
{
	/*
		@return void
		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the maximum

		Moves the enemies downwards

		Removes enemies at the edge of the screen. //TODO

	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {

		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {

			//Spawn the enemy and reset the timer
			
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f; // como é um float é melhor não fazer "this->enemySpawnTimer++"

	}


	for (int i = 0; i < this->enemies.size(); i++){
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f); // In each iteration of main loop, this for-loop force each of enemy rectangle to move this offset, x=0 and y = 5, thats why enemy are moving downwards

		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1; // if the enemy reaches the bottom screen limit we subtract one point to the player
			std::cout << "Health: " << this->health << std::endl;
		}
	}
	//Check if clicked upon
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (this->mouseHeld == false){
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
				//Once we raise the enemy, it is good practice to cancel this loop, because if i continue to click on my mouse it can be observed sudently crashes.
				// We should avoid the "break", since it can ruin something in our code.
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					
					//Collect or Gain Points :-)

					this->points += 1;
					std::cout << "Points: " << this->points << std::endl;
				}

			}
		}

	}
	else {// If we are not clicking in left mouse botton, change this variable to false.
		this->mouseHeld = false;
	}
	//The mouseHeld avoids the player to kill enemies with left mouse botton allways pressed
	// So we are able to kill again enemy, only when we release the left key botton of mouse.



}


void Game::update()
{
	this->pollEvents();

	//If the game finishes, then we cannot update nothing more.

	if (this->endGame == false) {

		this->updateMousePositions();

		this->updateEnemies();

	}
	//End game condition
	if (this->health <= 0) {
		this->endGame = true;// In main loop endGame becomes true and "Game Over" :-)
	}

}

void Game::renderEnemies()
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
		this->window->draw(e);

}

void Game::render()
{
	/*
		- clear the old frame;
		- render the objects;
		- display frame in our window;
		Renders the game objects
	*/
	this->window->clear();// O clear força o update à janela com côr preta. É o deafault!

	/// Draw game objects:
	this->renderEnemies(); // vamos fazer o render dos enemies.

	//Pintam-se os objectos na janelinha...
	this->window->display(); // 2º Faz-se o display
}




