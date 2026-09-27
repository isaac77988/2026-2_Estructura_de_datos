#include "Juego.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>

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
    cout << "RONDA " << rondaActual << " de 7 | LIDER: " << jugadores[turnoActual].consultarNombre() << endl;
    cout << "==========================================" << endl;

    cout << "Mano actual del lider (" << jugadores[turnoActual].consultarNombre() << "):" << endl;
    cout << jugadores[turnoActual].verMano();

    int colorRequerido = -1, regla = -1;
    while (colorRequerido != 0 && colorRequerido != 1) {
        cout << "Lider, selecciona el color requerido [0 = Rojo, 1 = Azul]: ";
        cin >> colorRequerido;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (regla != 0 && regla != 1) {
        cout << "Lider, selecciona la regla [0 = Carta Mayor, 1 = Carta Menor]: ";
        cin >> regla;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Carta cartasJugadas[4];

    for (int turno = 0; turno < cantidadJugadores; turno++) {
        int i = (turnoActual + turno) % cantidadJugadores;

        cout << "\n--- Turno de " << jugadores[i].consultarNombre() << " ---" << endl;
        cout << jugadores[i].verMano();

        bool obligarColor = jugadores[i].tieneColor(colorRequerido);
        if (obligarColor) {
            cout << "(Aviso: Tienes cartas de color " << (colorRequerido == 0 ? "Rojo" : "Azul")
                 << ", debes lanzar una de ese color)" << endl;
        }

        while (true) {
            int indice = -1;
            cout << "Selecciona el indice de la carta a lanzar (0 a "
                 << (jugadores[i].consultarCantidadCartas() - 1) << "): ";
            cin >> indice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (indice < 0 || indice >= jugadores[i].consultarCantidadCartas()) {
                cout << "Indice invalido. Intenta de nuevo." << endl;
                continue;
            }

            Carta elegida = jugadores[i].jugarCarta(indice);
            if (obligarColor && elegida.elegirColor() != colorRequerido) {
                cout << "Jugada invalida: Debes jugar una carta del color requerido ("
                     << (colorRequerido == 0 ? "Rojo" : "Azul") << ")." << endl;
                jugadores[i].recibirCarta(elegida);
                cout << jugadores[i].verMano();
                continue;
            }

            cartasJugadas[i] = elegida;
            cout << jugadores[i].consultarNombre() << " jugo la carta: " << cartasJugadas[i].mostrarCarta() << endl;
            break;
        }
    }

    int ganador = evaluarGanador(cartasJugadas, colorRequerido, regla);
    jugadores[ganador].sumarPunto();
    turnoActual = ganador;

    cout << "\n>>> Ganador de la ronda: " << jugadores[ganador].consultarNombre()
         << " (Puntaje total: " << jugadores[ganador].consultarPuntaje() << ") <<<" << endl;

    rondaActual++;

    if (rondaActual > 7) {
        cout << "\n==========================================" << endl;
        cout << "           TABLA FINAL DE PUNTOS          " << endl;
        cout << "==========================================" << endl;
        int maxPuntos = -1;
        for (int i = 0; i < cantidadJugadores; i++) {
            cout << " - " << jugadores[i].mostrarJugador() << endl;
            if (jugadores[i].consultarPuntaje() > maxPuntos) {
                maxPuntos = jugadores[i].consultarPuntaje();
            }
        }
        cout << "\n>>> GANADOR(ES) DE LA PARTIDA CON " << maxPuntos << " PUNTOS: ";
        for (int i = 0; i < cantidadJugadores; i++) {
            if (jugadores[i].consultarPuntaje() == maxPuntos) {
                cout << jugadores[i].consultarNombre() << " ";
            }
        }
        cout << "<<<" << endl;
    }
}

bool Juego::guardarPartida(string archivo) {
    ofstream salida(archivo);
    if (!salida.is_open()) return false;

    salida << cantidadJugadores << "\n" << rondaActual << "\n" << turnoActual << "\n";

    for (int i = 0; i < cantidadJugadores; i++) {
        salida << jugadores[i].consultarNombre() << "\n";
        salida << jugadores[i].consultarPuntaje() << "\n";

        int cantCartas = jugadores[i].consultarCantidadCartas();
        salida << cantCartas << "\n";

        for (int c = 0; c < cantCartas; c++) {
            Carta temp = jugadores[i].jugarCarta(0);
            salida << temp.elegirColor() << " " << temp.consultarNumero() << "\n";
            jugadores[i].recibirCarta(temp);
        }
    }
    salida.close();
    return true;
}

bool Juego::cargarPartida(string archivo) {
    ifstream entrada(archivo);
    if (!entrada.is_open()) return false;

    entrada >> cantidadJugadores >> rondaActual >> turnoActual;

    for (int i = 0; i < cantidadJugadores; i++) {
        string nombre;
        int puntaje, cantCartas;

        entrada >> nombre >> puntaje >> cantCartas;
        jugadores[i] = Jugador(nombre);

        for (int p = 0; p < puntaje; p++) {
            jugadores[i].sumarPunto();
        }

        for (int c = 0; c < cantCartas; c++) {
            int color, numero;
            entrada >> color >> numero;
            jugadores[i].recibirCarta(Carta(color, numero));
        }
    }
    entrada.close();
    return true;
}
