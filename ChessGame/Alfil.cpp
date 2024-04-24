#include "Alfil.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#define NEGRO 0
#define BLANCO 1

Alfil::Alfil(int color) : Pieza() {
	if (color == BLANCO)
		this->texture.loadFromFile(blanca);
	else if (color == NEGRO)
		this->texture.loadFromFile(negra);
	else
		cout << "ERROR: color selecionado no es ni blanco ni negro" << endl;

	this->sprite.setTexture(this->texture);
	this->color = color;
}

bool Alfil::movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, Board* board) {
	if (color == BLANCO) {
		return comprobarDiagonal(origenx, origeny, nuevax, nuevay, board, NEGRO);
	}
	else if (color == NEGRO) {
		return comprobarDiagonal(origenx, origeny, nuevax, nuevay, board, BLANCO);
	}
	return false;
}
