#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Carta.h" 

class Jugador {
private:
    std::string nombre;
    Carta mano[7];
    int cantidadCartas;
    int puntaje;

public:
    Jugador();
    Jugador(std::string nombre);

    void recibirCarta(Carta nuevaCarta);
    Carta jugarCarta(int indice);
    bool tieneColor(int colorRequerido);
    void sumarPunto();
    std::string consultarNombre();
    int consultarPuntaje();
    int consultarCantidadCartas();
    std::string mostrarJugador();
    std::string verMano();
};

#endif 
