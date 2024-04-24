#include "Reina.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#define NEGRO 0
#define BLANCO 1

Reina::Reina(int color) : Pieza() {
	if (color == BLANCO)
		this->texture.loadFromFile(blanca);
	else if (color == NEGRO)
		this->texture.loadFromFile(negra);
	else
		cout << "ERROR: color selecionado no es ni blanco ni negro" << endl;

	this->sprite.setTexture(this->texture);
	this->color = color;
}

bool Reina::movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, Board* board) {
	if (color == BLANCO) {
		bool diagonal = comprobarDiagonal(origenx, origeny, nuevax, nuevay, board, NEGRO);
		bool horizontal = comprobarHorizontal(origenx, origeny, nuevax, nuevay, board, NEGRO);
		return diagonal || horizontal;
	}
	else if (color == NEGRO) {
		bool diagonal = comprobarDiagonal(origenx, origeny, nuevax, nuevay, board, BLANCO);
		bool horizontal = comprobarHorizontal(origenx, origeny, nuevax, nuevay, board, BLANCO);
		return diagonal || horizontal;
	}
	return false;
}