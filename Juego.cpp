#include "Juego.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

Juego::Juego() {
    cantidadJugadores = 0;
    rondaActual = 1;
    turnoActual = 0;
}

void Juego::agregarJugador(string nombre) {
    if (cantidadJugadores < 4) {
        jugadores[cantidadJugadores] = Jugador(nombre);
        cantidadJugadores++;
    } else {
        cout << "Error: Limite maximo de 4 jugadores alcanzado." << endl;
    }
}

void Juego::repartirCartas() {
    Carta mazo[28];
    
    for (int i = 0; i < 14; i++) {
        mazo[i] = Carta(0, i + 1);
        mazo[i + 14] = Carta(1, i + 1);
    }

    srand(time(0));
    for (int i = 27; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }

    int cartaActual = 0;
    for (int i = 0; i < cantidadJugadores; i++) {
        for (int c = 0; c < 7; c++) {
            jugadores[i].recibirCarta(mazo[cartaActual]);
            cartaActual++;
        }
    }
}

void Juego::iniciarPartida() {
    if (cantidadJugadores < 2) {
        cout << "Se necesitan al menos 2 jugadores para iniciar." << endl;
        return;
    }
    rondaActual = 1;
    srand(time(0));
    turnoActual = rand() % cantidadJugadores;
    repartirCartas();
    cout << "\nPartida iniciada correctamente con " << cantidadJugadores << " jugadores." << endl;
}

bool Juego::estadoPartida() {
    return rondaActual <= 7;
}

int Juego::evaluarGanador(Carta cartasJugadas[], int colorRequerido, int regla) {
    int indiceGanador = turnoActual;
    int valorGanador = (regla == 0) ? -1 : 999;

    for (int i = 0; i < cantidadJugadores; i++) {
        Carta c = cartasJugadas[i];
        
        if (c.elegirColor() == colorRequerido) {
            int num = c.consultarNumero();
            
            if (regla == 0 && num > valorGanador) {
                valorGanador = num;
                indiceGanador = i;
            } else if (regla == 1 && num < valorGanador) {
                valorGanador = num;
                indiceGanador = i;
            }
        }
    }
    return indiceGanador;
}

void Juego::jugarRonda() {
    cout << "\n==========================================" << endl;
    cout << "RONDA " << rondaActual << " | LIDER: " << jugadores[turnoActual].consultarNombre() << endl;
    cout << "==========================================" << endl;

    int colorRequerido, regla;
    cout << "Lider, selecciona el color requerido [0 = Rojo, 1 = Azul]: ";
    cin >> colorRequerido;
    cout << "Lider, selecciona la regla [0 = Carta Mayor, 1 = Carta Menor]: ";
    cin >> regla;

    Carta cartasJugadas[4];

    for (int i = 0; i < cantidadJugadores; i++) {
        cout << "\n--- Turno de " << jugadores[i].consultarNombre() << " ---" << endl;
        cout << jugadores[i].verMano();
        
        int indice;
        cout << "Selecciona el indice de la carta a lanzar: ";
        cin >> indice;

        cartasJugadas[i] = jugadores[i].jugarCarta(indice);
        cout << jugadores[i].consultarNombre() << " jugo la carta: " << cartasJugadas[i].mostrarCarta() << endl;
    }

    int ganador = evaluarGanador(cartasJugadas, colorRequerido, regla);
    jugadores[ganador].sumarPunto();
    turnoActual = ganador;

    cout << "\n>>> Ganador de la ronda: " << jugadores[ganador].consultarNombre() 
         << " (Puntaje total: " << jugadores[ganador].consultarPuntaje() << ") <<<" << endl;
         
    rondaActual++;
}