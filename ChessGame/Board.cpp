#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#define BLANCO 1
#define NEGRO 0

Board::Board() {
	texture.loadFromFile("textures/Board.png");
	sprite.setTexture(texture);

	inizializarBlancas();
	inizializarNegras();

	jaqueBlanco = false;
	jaqueNegro = false;
	reiBlancoVivo = true;
	reiNegroVivo= true;
}

void Board::dibujarTablero(sf::RenderWindow* window) {
	window->draw(sprite);
	
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (tablero[i][j]) {
				tablero[i][j]->dibujarPieza(window, j*100, i*100);
			}
		}
	}

	if (piezaArrastrada) {
		piezaArrastrada->dibujarPieza(window, arrx, arry);
	}
}

//---------- MOVIMIENTO DE PIEZAS ----------//

bool Board::seleccionaPieza(float x, float y, int color) {
	int posx = y / 100;
	int posy = x / 100;
	
	if (tablero[posx][posy]) {
		if (tablero[posx][posy]->color == BLANCO && color == BLANCO) {
			//Asignamos la pieza seleccionada como Arrastrada y la quitamos del tablero
			piezaArrastrada = tablero[posx][posy];
			tablero[posx][posy] = nullptr;

			orix = posx;
			oriy = posy;

			piezaArrastrada->sprite.setOrigin(50, 50);

			arrx = x;
			arry = y;

			return true;
		}
		else if (tablero[posx][posy]->color == NEGRO && color == NEGRO) {
			piezaArrastrada = tablero[posx][posy];
			tablero[posx][posy] = nullptr;

			orix = posx;
			oriy = posy;

			piezaArrastrada->sprite.setOrigin(50, 50);

			arrx = x;
			arry = y;

			return true;
		}
	}
	else return false;
}
void Board::arrastraPieza(float x, float y) {
	if (piezaArrastrada) {
		arrx = x;
		arry = y;
		//cout << x << " " << y << endl;
	}
}
bool Board::sueltaPieza(float x, float y) {	
	if (piezaArrastrada) {
		int posx = y / 100;
		int posy = x / 100;

		if ((orix != posx || oriy != posy) && piezaArrastrada->movimientoLegal(orix, oriy, posx, posy, this)) {

			// Mirar si hay que actualizar la posicion del rei
			pair<int, int> posAux = {-1,-1};
			if (dynamic_cast<Rei*>(piezaArrastrada)) {
				if (piezaArrastrada->color == BLANCO) {
					posAux = posReiBlanco;
					posReiBlanco = { posx,posy };
				}
				else {
					posAux = posReiNegro;
					posReiNegro = { posx,posy };
				}
			}

			//Suponemos el nuevo tablero y se mira si hay jaque
			Pieza* aux = tablero[posx][posy];
			tablero[posx][posy] = piezaArrastrada;

			if (piezaArrastrada->color == BLANCO) {
				if (esJaque(posReiBlanco.first, posReiBlanco.second, BLANCO)) {
					tablero[orix][oriy] = piezaArrastrada;
					piezaArrastrada->sprite.setOrigin(0, 0);
					piezaArrastrada = nullptr;

					tablero[posx][posy] = aux;

					if (posAux.first != -1) {
						posReiBlanco = posAux;
					}
					return false;
				}
				else {
					jaqueBlanco = false;
					if (piezaArrastrada->movimientoLegal(posx, posy, posReiNegro.first, posReiNegro.second, this)) {
						jaqueNegro = true;
					}
				}
			}
			else {
				if (esJaque(posReiNegro.first, posReiNegro.second, NEGRO)) {
					tablero[orix][oriy] = piezaArrastrada;
					piezaArrastrada->sprite.setOrigin(0, 0);
					piezaArrastrada = nullptr;

					tablero[posx][posy] = aux;

					if (posAux.first != -1) {
						posReiNegro = posAux;
					}
					return false;
				}
				else {
					jaqueNegro = false;
					if (piezaArrastrada->movimientoLegal(posx, posy, posReiBlanco.first, posReiBlanco.second, this)) {
						jaqueBlanco = true;
					}
				}
			}
			//Dejamos de hacer la suposicion, todo es valido
			tablero[posx][posy] = aux;

			if (dynamic_cast<Rei*>(tablero[posx][posy])) {
				if (piezaArrastrada->color == BLANCO) reiNegroVivo = false;
				else reiBlancoVivo = false;
				//no deberia ser el tablero el que controle si el juego se ha acabdo o no,
				//deberia ser el main que actua como algo parecido al GameMode, el board
				//solo tiene que hacer el comportamiento del board no de como se gana o no
			}


			eliminarPieza(posx, posy);


			//PELIGRO DONDE COLOCAR ESTO
			if (Peon* p = dynamic_cast<Peon*>(piezaArrastrada)) {
				p->transformar();
			}

			tablero[posx][posy] = piezaArrastrada;
			piezaArrastrada->sprite.setOrigin(0, 0);
			piezaArrastrada = nullptr;


			if (jaqueBlanco) {
				if (Rei* rei = dynamic_cast<Rei*>(tablero[posReiBlanco.first][posReiBlanco.second])) {
					bool ps = rei->puedeSalvarse(posReiBlanco.first, posReiBlanco.second, *this);

					if (ps) {
						jaqueBlanco = false;
					}
					else {
						reiBlancoVivo = false;
					}

				}
				else cout << "ERROR: el rei no esta en la posicion esperada" << endl;
			}
			else if (jaqueNegro) {
				if (Rei* rei = dynamic_cast<Rei*>(tablero[posReiNegro.first][posReiNegro.second])) {
					bool ps = rei->puedeSalvarse(posReiNegro.first, posReiNegro.second, *this);

					if (ps) {
						jaqueNegro = false;
					}
					else {
						reiNegroVivo = false;
					}

				}
				else cout << "ERROR: el rei no esta en la posicion esperada" << endl;
			}


			return true;

		}
		else {
			tablero[orix][oriy] = piezaArrastrada;
			piezaArrastrada->sprite.setOrigin(0, 0);
			piezaArrastrada = nullptr;
			return false;
		}
	}
	return false;
}

//------------------------------------------//

void Board::inizializarBlancas() {
	//Crear peones
	for (int i = 0; i < 8; ++i) {
		Peon* p = new Peon(BLANCO);
		tablero[6][i] = p;
	}
	//Crear torres
	Torre* t = new Torre(BLANCO);
	tablero[7][0] = t;
	t = new Torre(BLANCO);
	tablero[7][7] = t;
	
	//Crear caballos
	Caballo* c = new Caballo(BLANCO);
	tablero[7][1] = c;
	c = new Caballo(BLANCO);
	tablero[7][6] = c;
	
	//Crear alfils
	Alfil* a = new Alfil(BLANCO);
	tablero[7][2] = a;
	a = new Alfil(BLANCO);
	tablero[7][5] = a;
	
	//Crear reina
	Reina* rn = new Reina(BLANCO);
	tablero[7][3] = rn;

	//Crear rei
	Rei* ri = new Rei(BLANCO);
	tablero[7][4] = ri;
	posReiBlanco = { 7,4 };
}
void Board::inizializarNegras() {
	//Crear peones
	for (int i = 0; i < 8; ++i) {
		Peon* p = new Peon(NEGRO);
		tablero[1][i] = p;
	}
	//Crear torres
	Torre* t = new Torre(NEGRO);
	tablero[0][0] = t;
	t = new Torre(NEGRO);
	tablero[0][7] = t;
	
	//Crear caballos
	Caballo* c = new Caballo(NEGRO);
	tablero[0][1] = c;
	c = new Caballo(NEGRO);
	tablero[0][6] = c;
	
	//Crear alfils
	Alfil* a = new Alfil(NEGRO);
	tablero[0][2] = a;
	a = new Alfil(NEGRO);
	tablero[0][5] = a;
	
	//Crear reina
	Reina* rn = new Reina(NEGRO);
	tablero[0][3] = rn;

	//Crear rei
	Rei* ri = new Rei(NEGRO);
	tablero[0][4] = ri;
	posReiNegro = { 0,4 };
}

bool Board::hayPiezaEnPos(int x, int y) {
	if (tablero[x][y]) {
		return true;
	}
	else return false;
}
bool Board::hayPiezaEnPos(int x, int y, int color) {
	if (tablero[x][y]) {
		if (tablero[x][y]->color == color) return true;
		return false;
	}
	else return false;
}

void Board::eliminarPieza(int x, int y) {
	if (tablero[x][y]) {
		Pieza* ptr = tablero[x][y];
		delete ptr;
	}
}

bool Board::isReiBlancoVivo() {
	return reiBlancoVivo;
}
bool Board::isReiNegroVivo() {
	return reiNegroVivo;
}

//esto es una guarrada pero es lo manera mas sencilla de implementarlo O(n^2)
bool Board::esJaque(int posx, int posy, int color) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (tablero[i][j]) {
				if (tablero[i][j]->color != color &&
					tablero[i][j]->movimientoLegal(i, j, posx, posy, this)) {
					cout << i << j << endl;
					return true;
				}
			}
		}
	}
	return false;
}