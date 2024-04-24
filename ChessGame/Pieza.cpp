#include "Pieza.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

Pieza::Pieza() {}

void Pieza::dibujarPieza(sf::RenderWindow* window, float x, float y) {
	sprite.setPosition(x,y);
	window->draw(sprite);
}

bool Pieza::movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, Board* board) { return false; }

bool Pieza::comprobarDiagonal(int origenx, int origeny, int nuevax, int nuevay, Board* board, int colorEnemigo) {
	//Recorrer diagonal \ 
	if (origenx - nuevax == origeny - nuevay) {
		int j = min(origeny, nuevay) + 1, y = max(origeny, nuevay) - 1;
		int i = min(origenx, nuevax) + 1, x = max(origenx, nuevax) - 1;

		bool posible = true;
		//Mirar si el camino entre las dos piezas esta vacio
		while (i <= x && j <= y && posible) {
			posible = !board->hayPiezaEnPos(i, j);
			++i; ++j;
		}
		if (!posible) return false;

		//Que pieza hay en la posicion a la que quiero ir?
		if (!board->hayPiezaEnPos(nuevax, nuevay)) return true;

		if (board->hayPiezaEnPos(nuevax, nuevay, colorEnemigo)) return true;
	}
	//Recorrer diagonal /
	else if (nuevax - origenx == origeny - nuevay) {
		int y = min(origeny, nuevay) + 1, j = max(origeny, nuevay) - 1;
		int i = min(origenx, nuevax) + 1, x = max(origenx, nuevax) - 1;

		bool posible = true;
		//Mirar si el camino entre las dos piezas esta vacio
		while (i <= x && j >= y && posible) {
			posible = !board->hayPiezaEnPos(i, j);

			++i; --j;
		}
		if (!posible) return false;

		//Que pieza hay en la posicion a la que quiero ir?
		if (!board->hayPiezaEnPos(nuevax, nuevay)) return true;

		if (board->hayPiezaEnPos(nuevax, nuevay, colorEnemigo)) return true;
	}
	
	return false;
}

bool Pieza::comprobarHorizontal(int origenx, int origeny, int nuevax, int nuevay, class Board* board, int colorEnemigo) {
	//Movimiento vertical
	if (origenx == nuevax && origeny != nuevay) {
		int i = min(origeny, nuevay) + 1, j = max(origeny, nuevay) - 1;
		bool posible = true;
		//Mirar si el camino entre las dos piezas esta vacio
		while (i <= j && posible) {
			posible = !board->hayPiezaEnPos(nuevax, i);
			++i;
		}
		if (!posible) return false;

		//Que pieza hay en la posicion a la que quiero ir?
		if (!board->hayPiezaEnPos(nuevax, nuevay)) return true;

		if (board->hayPiezaEnPos(nuevax, nuevay, colorEnemigo)) return true;
	}
	//Movimiento horizontal
	else if (origeny == nuevay && origenx != nuevax) {
		int i = min(origenx, nuevax) + 1, j = max(origenx, nuevax) - 1;
		bool posible = true;
		//Mirar si el camino entre las dos piezas esta vacio
		while (i <= j && posible) {
			posible = !board->hayPiezaEnPos(i, nuevay);
			++i;
		}
		if (!posible) return false;

		//Que pieza hay en la posicion a la que quiero ir?
		if (!board->hayPiezaEnPos(nuevax, nuevay)) return true;

		if (board->hayPiezaEnPos(nuevax, nuevay, colorEnemigo)) return true;
	}
	
	return false;
}