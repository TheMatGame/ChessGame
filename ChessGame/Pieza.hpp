#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class Pieza {

public:
	Pieza();

	sf::Texture texture;
	sf::Sprite sprite;
	int color = 0;

	void dibujarPieza(sf::RenderWindow* window, float x, float y);

	virtual bool movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, class Board* board);

protected: 
	bool comprobarDiagonal(int origenx, int origeny, int nuevax, int nuevay, class Board* board, int colorEnemigo);
	bool comprobarHorizontal(int origenx, int origeny, int nuevax, int nuevay, class Board* board, int colorEnemigo);
};