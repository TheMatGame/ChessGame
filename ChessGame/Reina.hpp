#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieza.hpp"

using namespace std;

class Reina : public Pieza {

	const string blanca = "textures/BReina.png";
	const string negra = "textures/NReina.png";

public:
	Reina(int color);
	
	bool movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, class Board* board) override;

};