#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Pieza.hpp"
#include "Peon.hpp"
#include "Torre.hpp"
#include "Caballo.hpp"
#include "Alfil.hpp"
#include "Reina.hpp"
#include "Rei.hpp"

#define BS 7

class Board {
public:

    Pieza* tablero[8][8];

    sf::Texture texture;
    sf::Sprite sprite;

    Pieza* piezaArrastrada;
    float arrx, arry;   //Cordenadas de pantalla mientras se arrastra
    int orix, oriy;     //Posiciones de origen

    pair<int, int> posReiBlanco;
    pair<int, int> posReiNegro;

    bool jaqueBlanco;
    bool jaqueNegro;

    bool reiBlancoVivo;
    bool reiNegroVivo;

    Board();

    void dibujarTablero(sf::RenderWindow* window);

    bool seleccionaPieza(float x, float y, int color);
    void arrastraPieza(float x, float y);
    bool sueltaPieza(float x, float y);

    void inizializarBlancas();
    void inizializarNegras();

    bool hayPiezaEnPos(int x, int y);
    bool hayPiezaEnPos(int x, int y, int color);

    void eliminarPieza(int x, int y);

    bool isReiBlancoVivo();
    bool isReiNegroVivo();
    bool esJaque(int posx, int posy, int color);

};