#include "Caballo.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#define NEGRO 0
#define BLANCO 1

Caballo::Caballo(int color) : Pieza() {
	if (color == BLANCO)
		this->texture.loadFromFile(blanca);
	else if (color == NEGRO)
		this->texture.loadFromFile(negra);
	else
		cout << "ERROR: color selecionado no es ni blanco ni negro" << endl;

	this->sprite.setTexture(this->texture);
	this->color = color;
}

bool Caballo::movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, Board* board) {
	if (color == BLANCO) {
		for (int i = 0; i < 8; ++i) {
			if (origenx + movimientox[i] == nuevax && origeny + movimientoy[i] == nuevay) {
				if (board->hayPiezaEnPos(nuevax, nuevay, NEGRO)) {
					

					return true;
				}
				else if (!board->hayPiezaEnPos(nuevax, nuevay)) {
					return true;
				}
			}
		}
	}
	else if (color == NEGRO) {
		for (int i = 0; i < 8; ++i) {
			if (origenx + movimientox[i] == nuevax && origeny + movimientoy[i] == nuevay) {
				if (board->hayPiezaEnPos(nuevax, nuevay, BLANCO)) {
					return true;
				}
				else if (!board->hayPiezaEnPos(nuevax, nuevay)) {
					return true;
				}
			}
		}
	}
	return false;
}