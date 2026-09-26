#include "Jugador.h"

Jugador::Jugador() : nombre(""), cantidadCartas(0), puntaje(0) {}

Jugador::Jugador(std::string nombre) : nombre(nombre), cantidadCartas(0), puntaje(0) {}

void Jugador::recibirCarta(Carta nuevaCarta) {
    if (cantidadCartas < 7) {
        mano[cantidadCartas] = nuevaCarta;
        cantidadCartas++;
    }
}

Carta Jugador::jugarCarta(int indice) {
    Carta cartaJugada;
    if (indice >= 0 && indice < cantidadCartas) {
        cartaJugada = mano[indice];
        for (int i = indice; i < cantidadCartas - 1; i++) {
            mano[i] = mano[i + 1];
        }
        cantidadCartas--;
    }
    return cartaJugada;
}

bool Jugador::tieneColor(int colorRequerido) {
    for (int i = 0; i < cantidadCartas; i++) {
        if (mano[i].elegirColor() == colorRequerido) {
            return true;
        }
    }
    return false;
}

void Jugador::sumarPunto() {
    puntaje++;
}

std::string Jugador::consultarNombre() {
    return nombre;
}

int Jugador::consultarPuntaje() {
    return puntaje;
}

int Jugador::consultarCantidadCartas() {
    return cantidadCartas;
}

std::string Jugador::mostrarJugador() {
    return "Jugador: " + nombre + " | Puntaje: " + std::to_string(puntaje);
}

std::string Jugador::verMano() {
    std::string res = "";
    for (int i = 0; i < cantidadCartas; i++) {
        res += "[" + std::to_string(i) + "] " + mano[i].mostrarCarta() + "\n";
    }
    return res;
}
