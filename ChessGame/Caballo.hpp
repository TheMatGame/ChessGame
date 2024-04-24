#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieza.hpp"

using namespace std;

class Caballo : public Pieza {

	const string blanca = "textures/BCaballo.png";
	const string negra = "textures/NCaballo.png";

	int movimientox[8] = {1,2,2,1,-1,-2,-2,-1};
	int movimientoy[8] = {2,1,-1,-2,-2,-1,1,2};

public:
	Caballo(int color);
	
	bool movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, class Board* board) override;

};