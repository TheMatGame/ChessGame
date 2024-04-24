#include "Rei.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#define NEGRO 0
#define BLANCO 1

Rei::Rei(int color) : Pieza() {
	if (color == BLANCO)
		this->texture.loadFromFile(blanca);
	else if (color == NEGRO)
		this->texture.loadFromFile(negra);
	else
		cout << "ERROR: color selecionado no es ni blanco ni negro" << endl;

	this->sprite.setTexture(this->texture);
	this->color = color;
}


//TODO: hacerlo mas facil, solo hace falta restar posiciones y comprobar.
bool Rei::movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, Board* board) {
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

//SOLO SE USA CUANDO EL REI ESTA EN JAQUE 
bool Rei::puedeSalvarse(int origenx, int origeny, class Board board) {
	if (color == BLANCO) {
		//pair<int, int> casillaJaque;
		for (int i = 0; i < 8; ++i) {
			int x = origenx + movimientox[i];
			int y = origeny + movimientoy[i];
			if (x >= 0 && x < 8 && y >= 0 && y < 8) {
				if (board.hayPiezaEnPos(x, y, NEGRO) && !board.hayPiezaEnPos(x, y)) {
					//Muevo el rei a la supuesta nueva posicion
					Pieza* aux = board.tablero[origenx][origeny];
					board.tablero[x][y] = aux;
					board.tablero[origenx][origeny] = nullptr;

					if (!board.esJaque(x, y, BLANCO)) return true;
					else {
						//casillaJaque = { x,y };
					}

					board.tablero[x][y] = nullptr;
					board.tablero[origenx][origeny] = aux;
				}

			}
		}

		//Esto es una veguenza
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (board.tablero[i][j] && (i != origenx || j != origeny)) {
					for (int k = 0; k < 8; ++k) {
						for (int l = 0; l < 8; ++l) {
							if (board.tablero[i][j]->color == color &&
								board.tablero[i][j]->movimientoLegal(i, j, k, l, &board)) {

								Pieza* aux = board.tablero[k][l];
								board.tablero[k][l] = board.tablero[i][j];
								board.tablero[i][j] = nullptr;

								if (!board.esJaque(origenx, origeny, BLANCO)) return true;

								board.tablero[i][j] = board.tablero[k][l];
								board.tablero[k][l] = aux;
							}
						}
					}
				}
			}
		}

		return false;

	}
	else if (color == NEGRO) {
		//pair<int, int> casillaJaque;
		for (int i = 0; i < 8; ++i) {
			int x = origenx + movimientox[i];
			int y = origeny + movimientoy[i];
			if (x >= 0 && x < 8 && y >= 0 && y < 8) {
				if (board.hayPiezaEnPos(x, y, BLANCO) && !board.hayPiezaEnPos(x, y)) {
					//Muevo el rei a la supuesta nueva posicion
					Pieza* aux = board.tablero[origenx][origeny];
					board.tablero[x][y] = aux;
					board.tablero[origenx][origeny] = nullptr;

					if (!board.esJaque(x, y, NEGRO)) return true;
					else {
						//casillaJaque = { x,y };
					}

					board.tablero[x][y] = nullptr;
					board.tablero[origenx][origeny] = aux;
				}

			}
		}

		//Esto es una veguenza
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (board.tablero[i][j] && (i != origenx || j != origeny)) {
					for (int k = 0; k < 8; ++k) {
						for (int l = 0; l < 8; ++l) {
							if (board.tablero[i][j]->color == color &&
								board.tablero[i][j]->movimientoLegal(i, j, k, l, &board)) {

								Pieza* aux = board.tablero[k][l];
								board.tablero[k][l] = board.tablero[i][j];
								board.tablero[i][j] = nullptr;

								if (!board.esJaque(origenx, origeny, NEGRO)) return true;

								board.tablero[i][j] = board.tablero[k][l];
								board.tablero[k][l] = aux;
							}
						}
					}
				}
			}
		}

		return false;
	}
	return false;
}