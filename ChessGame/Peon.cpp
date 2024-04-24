#include "Peon.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.hpp"

#define NEGRO 0
#define BLANCO 1

Peon::Peon(int color) : Pieza() {
	if (color == BLANCO)
		this->texture.loadFromFile(blanca);
	else if (color == NEGRO)
		this->texture.loadFromFile(negra);
	else 
		cout << "ERROR: color selecionado no es ni blanco ni negro" << endl;

	this->sprite.setTexture(this->texture);
	this->color = color;
	primerMovimiento = true;
}

bool Peon::movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, Board* board) {
	//Movimiento Peon Blanco
	if (color == BLANCO) {
		if (origenx - 2 == nuevax && primerMovimiento &&
			!board->hayPiezaEnPos(nuevax, nuevay) &&
			!board->hayPiezaEnPos(origenx-1, nuevay)) {
			primerMovimiento = false;
			return true;
		}
		else if (origenx - 1 == nuevax)	{
			if (origeny == nuevay && !board->hayPiezaEnPos(nuevax, nuevay)) {
				primerMovimiento = false;
				return true;
			}
			else if (origeny + 1 == nuevay && board->hayPiezaEnPos(nuevax, nuevay, NEGRO)) {
				
				primerMovimiento = false;
				return true;
			}
			else if (origeny - 1 == nuevay && board->hayPiezaEnPos(nuevax, nuevay, NEGRO)) {
				
				primerMovimiento = false;
				return true;
			}
		}
	}

	//Movimiento Peon Negro
	if (color == NEGRO) {
		if (origenx + 2 == nuevax && primerMovimiento && 
			!board->hayPiezaEnPos(nuevax, nuevay) &&
			!board->hayPiezaEnPos(origenx+1, nuevay)) {
			primerMovimiento = false;
			return true;
		}
		else if (origenx + 1 == nuevax) {
			if (origeny == nuevay && !board->hayPiezaEnPos(nuevax, nuevay)) {
				primerMovimiento = false;
				return true;
			}
			else if (origeny + 1 == nuevay && board->hayPiezaEnPos(nuevax, nuevay, BLANCO)) {
				
				primerMovimiento = false;
				return true;
			}
			else if (origeny - 1 == nuevay && board->hayPiezaEnPos(nuevax, nuevay, BLANCO)) {
				
				primerMovimiento = false;
				return true;
			}
		}
	}

	return false;
}

void Peon::transformar() {
	//Falta que el peon pueda transformarse
}