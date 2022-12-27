#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Estes includes estavam inicialmente declarados no main.cpp, foram movidos para estes Game.h,
//porque estes códigos Graphis.hpp,...,Network.hpp têm muito código e se os estivermos a incluir no main.cpp, ao longo do tempo aumenta o tempo de compilação
// Se estivermos a criar um grande jogo, complexo, existem os chamados pre-compiled headers

/*
	Class that acts as the game engine
	Basically is a class where we define all functions,functionalities of game	
*/




class Game
{
private:
	//Variáveis:

	//Window:
	sf::RenderWindow* window; //é um apontador para a janela
	sf::VideoMode videoMode;
	sf::Event ev;// o ev tem uma inicialização deafault...

	//Game Objects
	sf::RectangleShape enemy;//


	//Criação de algumas funções que não pretendemos dar acesso...
	void initializeVariables();
	void initWindow();
	void initEnemies();

public:
	//Contructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;// enquanto a janela está aberta.. é porque a janela está em "running"

	//Our Functions:
	void pollEvents();
	void update();
	void render();
};

