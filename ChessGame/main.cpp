#include <iostream>
#include "Board.hpp"

#include <SFML/Graphics.hpp>

const float Width = 800;
const float Heigth = 800;

#define BLANCO 1
#define NEGRO 0

void finalizarPartida(sf::RenderWindow* window, Board* board) {
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cout << "Fonts don't load" << endl;
    }

    text.setFont(font);
    if (board->isReiBlancoVivo()) {
        text.setString("Han ganado la blancas");
    }
    else {
        text.setString("Han ganado la negras");
    }
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Black);
    text.setPosition(100, 300);
    window->draw(text);
}

int main()
{
    int turno = BLANCO;
    bool arrastrando = false;
    bool partidaContinua = true;

    sf::RenderWindow window(sf::VideoMode(Width, Heigth), "Chess Game by Marc G!");
    window.clear();

    // Forma del tablero
    Board board;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!arrastrando) {
                        sf::Vector2i coords = sf::Mouse::getPosition(window);
                        arrastrando = board.seleccionaPieza(coords.x, coords.y, turno);
                    }
                }
            }
            
            if (event.type == sf::Event::MouseMoved) {
                if (arrastrando) {
                    board.arrastraPieza(event.mouseMove.x, event.mouseMove.y);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (arrastrando) {
                        sf::Vector2i coords = sf::Mouse::getPosition(window);
                        if (board.sueltaPieza(coords.x, coords.y)) {
                            //Cambiar de turno
                            if (turno == BLANCO) turno = NEGRO;
                            else turno = BLANCO;
                            cout << turno << endl;
                            
                            //Mirar si la partida sigue
                            if (!board.isReiBlancoVivo() || !board.isReiNegroVivo()) {
                                partidaContinua = false;
                            }
                        }
                        arrastrando = false;
                    }
                }
            }
        }

        if (partidaContinua) {
            board.dibujarTablero(&window);
        }
        else {
            finalizarPartida(&window, &board);
        }

        window.display();
    }

    return 0;
}

