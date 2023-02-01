#include <iostream>
#include <vector> 
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
	Class that acts as the game engine
	Basically is a class where we define all functions,functionalities of game	
*/




class Game
{
private:
	//Variáveis:

	//Window:
	sf::RenderWindow* window; //it's a pointer to window
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse Positions:
	sf::Vector2i mousePosWindow;//Most of operations in SFML are done with float, so we will start to use Vector2f (two floats for mouse positions...)
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	
	bool endGame;
	unsigned points; // only positive points :-)
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game Objects
	std::vector<sf::RectangleShape> enemies; // Vector to store "sf::RectangleShape" objects. Vector to store enemies.
	sf::RectangleShape enemy;//


	
	void initializeVariables();
	void initWindow();	
	void initFonts();
	void initText();
	void initEnemies();

public:
	//Contructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Our Functions:
	void spawnEnemy(); 
	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();
	void renderText(sf::RenderTarget& target);//Often we don't need to render to main window, sometimes we can render to a view...
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

