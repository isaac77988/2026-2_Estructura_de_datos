#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include "Jugador.h"

class Juego {
private:
    Jugador jugadores[4];
    int cantidadJugadores;
    int rondaActual;
    int turnoActual;

    void repartirCartas();
    int evaluarGanador(Carta cartasJugadas[], int colorRequerido, int regla);

public:
    Juego();
    void agregarJugador(std::string nombre);
    void iniciarPartida();
    void jugarRonda();
    bool estadoPartida();
    bool guardarPartida(std::string archivo);
    bool cargarPartida(std::string archivo);
};

#endif