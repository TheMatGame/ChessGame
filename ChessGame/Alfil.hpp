#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieza.hpp"

using namespace std;

class Alfil : public Pieza {

	const string blanca = "textures/BAlfil.png";
	const string negra = "textures/NAlfil.png";

public:
	Alfil(int color);

	bool movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, class Board* board) override;

};