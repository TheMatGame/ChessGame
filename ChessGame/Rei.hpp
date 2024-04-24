#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieza.hpp"

using namespace std;

class Rei : public Pieza {

	const string blanca = "textures/BRei.png";
	const string negra = "textures/NRei.png";

	int movimientox[8] = {0,1,1,1,0,-1,-1,-1};
	int movimientoy[8] = {1,1,0,-1,-1,-1,0,1};

public:
	Rei(int color);

	bool movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, class Board* board) override;

	bool puedeSalvarse(int origenx, int origeny, class Board board);
};