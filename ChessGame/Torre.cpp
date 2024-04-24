#include "Torre.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.hpp"

#define NEGRO 0
#define BLANCO 1

Torre::Torre(int color) : Pieza() {
	if (color == BLANCO)
		this->texture.loadFromFile(blanca);
	else if (color == NEGRO)
		this->texture.loadFromFile(negra);
	else
		cout << "ERROR: color selecionado no es ni blanco ni negro" << endl;

	this->sprite.setTexture(this->texture);
	this->color = color;
}

bool Torre::movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, Board* board) {
	if (color == BLANCO) {
		return comprobarHorizontal(origenx, origeny, nuevax, nuevay, board, NEGRO);
	}
	else if (color == NEGRO) {
		return comprobarHorizontal(origenx, origeny, nuevax, nuevay, board, BLANCO);
	}
	return false;
}
