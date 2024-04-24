#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieza.hpp"

using namespace std;

class Torre : public Pieza {

	const string blanca = "textures/BTorre.png";
	const string negra = "textures/NTorre.png";

public:
	Torre(int color);

	bool movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, class Board* board) override;

};