#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieza.hpp"


using namespace std;

class Peon : public Pieza {

	const string blanca = "textures/BPeon.png";
	const string negra = "textures/NPeon.png";

	bool primerMovimiento;

public:
	Peon(int color);

	bool movimientoLegal(int origenx, int origeny, int nuevax, int nuevay, class Board* board) override;

	void transformar();
};