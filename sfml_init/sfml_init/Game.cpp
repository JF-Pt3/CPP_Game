#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr; // o window é do tipo apontador( ver as variáveis do Game.h)
}

void Game::initWindow()
{
	this->videoMode.height = 600;// mais fácil fazer o ajuste das dimensões do ecrã assim...
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode; para ir buscar a resolução do ecrã do pc directamente...
	this->window = new sf::RenderWindow(this->videoMode, "Game One", sf::Style::Titlebar | sf::Style::Close);
}

Game::Game() {//Definição do construtor
	// Vai permitir chamar as funções que vão fazer as "coisas" aparecer no ecrã!...
	/// é necessário ter esta ordem, porque não vamos pretender inicializar o ecrã e só depois inicializar variáveis....
	this->initializeVariables();
	this->initWindow();
}

Game::~Game() {//Definição do destructor
	delete this->window;// para evitar um grande memory leak...
}

const bool Game::running() const
{
	return this->window->isOpen();
}


//Functions
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


void Game::update()
{
	this->pollEvents();// aqui dentro vamos chamar o pollEvents( é a tal função que faz a mecânica de tratamento de eventos no nosso jogo)
	

}

void Game::render()
{
	/*
		- clear the old frame;
		- render the objects;
		- display frame in our window;
		Renders the game objects
	*/
	this->window->clear(sf::Color(255,0,0,255));// 1º limpa-se a janela, pintado-a de vermelho...

	//Pintam-se os objectos na janelinha...
	this->window->display(); // 2º Faz-se o display
}




