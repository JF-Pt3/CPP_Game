#include "Game.h"

/*
	@return void
	Initialize all variables related to game logic

*/

void Game::initializeVariables()
{
	this->window = nullptr; // Windows is a pointer( check variables from Game.h)

	//
	this->endGame = false;
	this->points = 0;//Points earned when we kill the enemy
	this->enemySpawnTimerMax = 20.f;// Rate of enemy generation/spawning
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false; // Starts in "false" since in begining we are not holding the mouse...
	this->health = 10;
}
/*
	@return void
	Initialize our Game window

*/
void Game::initWindow()
{
	this->videoMode.height = 600;// manually adjust dimensions of screen
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode; directly finds the dimensions of your deafault screen
	this->window = new sf::RenderWindow(this->videoMode, "Game One", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);// we are limiting to 60 fps (not pushing to much :-) )
}
/*
	@return void
	Load our fonts
	// we should indicade the path to the .ttf file...
*/
void Game::initFonts()
{
	if (this->font.loadFromFile("C:/Users/JF/3D Objects/SFML_Project/sfml_init/sfml_init/Fonts/Dosis-Light.ttf")) {

		std::cout << "ERROR::GAME::INITFONTS::FAILED TO LOAD THE DESIRED FONT" << "\n";
	}

}
/*
	@return void
	Text settings...

*/
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("none");

}

/*
	@return void
	Create the enemy default settings
	-Set position,size and color

*/

void Game::initEnemies()
{

	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan); // fill enemy with cyan color...
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

/*
	@return Game
	Constructor definition
	- Allows to call all functions related to the game
	  - window functions;
	  - Fonts,
	  - Text,
	  - Enemies;
	*The order is important!

*/

Game::Game() {
	
	
	this->initializeVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

/*
	@return Game
	Destructor definition
*/

Game::~Game() {
	delete this->window;// avoid memory leak...
}

/*

	Self Explanatory :-)


*/
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}



//Functions

	/*
		@return void
		Spawns enemies and sets their types,colors.Spawn them random positions.
		-Sets a random type (diff).
		-Sets a random position
		-Sets a random color ( for random we use ctime lib
		-Adds enemy to the vector
	*/

void Game::spawnEnemy()
{


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
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)) // o enemy aqui já vai com avanço, com 0.f o enemy começa lá em cima!

	);

	//We will have different types of enemies. To do so, we will randomize enemy type:
	int type = rand() % 5; // Generate 0 to 4 random enemies

	switch (type)
	{

	case 0:// The hardest enemy!!! ahahaha :-)
		
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));// The smaller enemies are the hardest to deal, that's why we set smaller scales
		this->enemy.setFillColor(sf::Color::Magenta);
		break;

	case 1:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;

	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;

	case 3:
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;

	case 4:
		this->enemy.setSize(sf::Vector2f(90.f, 90.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;

	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	}


	//Spawn the enemy:
	this->enemies.push_back(this->enemy);
}

/*
	@return void
	Function to mediate actions to be taken following events:
	-Key is pressed;
	-Window is closed;
*/

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {

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

/*@return void
  updates the mouse positions
	- Mouse position relative to window (Vector2i)
*/
void Game::updateMousePositions()
{


	this->mousePosWindow = sf::Mouse::getPosition(*this->window);// Window is a pointer, we need to reference it... (that's why we use *this)
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);//We take our mouse positions in window,secondly this positions are mapped to floats. Finally this floats are mapped to our View
}

/*@return void
	Function to display in real time the points
*/
void Game::updateText()
{
	std::stringstream ss; //StreamString alows you to mix integers,chars,doubles,floats and other data types among a string

	ss << "Points" << this->points << "\n" << "Health: " << this->health;

	this->uiText.setString(ss.str());

}

/*
	@return void
	Updates the enemy spawn timer and spawns enemies
	when the total amount of enemies is smaller than the maximum

	Moves the enemies downwards

	Removes enemies at the edge of the screen. 

*/
void Game::updateEnemies()
{


	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {

		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {

			//Spawn the enemy and reset the timer

			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f; 

	}


	for (int i = 0; i < this->enemies.size(); i++) {
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

		if (this->mouseHeld == false) {
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
				//Once we raise the enemy, it is good practice to cancel this loop, because if i continue to click on my mouse it can be observed sudently crashes.
				// We should avoid the "break", since it can ruin something in our code.
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {



					//Collect or Gain Points :-)
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;
					std::cout << "Points: " << this->points << std::endl;

					//Delete the enemy:
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

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

/*
	@return void
	Function to update mouse positions, text and enemies state

*/

void Game::update()
{
	this->pollEvents();

	//If the game finishes, then we cannot update nothing more.

	if (this->endGame == false) {

		this->updateMousePositions();
		this->updateText();

		this->updateEnemies();

	}
	//End game condition
	if (this->health <= 0) {
		this->endGame = true;// In main loop endGame becomes true and "Game Over" :-)
	}

}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText); // I am not bounding to draw on screen
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
		target.draw(e);

}

/*  @return void
	- clear the old frame;
	- render the objects;
	- display frame in our window;
	Renders the game objects
*/
void Game::render()
{

	this->window->clear();// O clear força o update à janela com côr preta. É o deafault!

	/// Draw game objects:
	this->renderEnemies(*this->window); // vamos fazer o render dos enemies. *this: we don't want the pointer, so we dereference the pointer, since window is a pointer of type RenderWindow

	this->renderText(*this->window);

	//Pintam-se os objectos na janelinha...
	this->window->display(); // 2º Faz-se o display
}




