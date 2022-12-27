#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr; // o window é do tipo apontador( ver as variáveis do Game.h)

	//Variables related to game logic

	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;	
	this->maxEnemies = 5;
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
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
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
		//See the manual: setPosition requires x and y to be float, we need a cast...
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

	//Move the enemies:

	for (auto& e : this->enemies)
		e.move(0.f, 1.f); // A cada enemy gerado, procede-se à translação de 5 unidades para baixo (eixo y),
	//coloquei 1.f para ir andando só uma unidade para baixo, sendo mais lentinho...vê-se melhor :-)


}


void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();
	

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




