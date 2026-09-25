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

    void repartirCartas() {
        // Lógica para repartir cartas
    }

    