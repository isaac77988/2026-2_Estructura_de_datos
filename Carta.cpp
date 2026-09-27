#include "Carta.h"

Carta::Carta() {
    color = 0;
    numero = 0;
}

Carta::Carta(int c, int n) {
    color = c;
    numero = n;
}

int Carta::elegirColor() {
    return color;
}

int Carta::elegirNumero() {
    return numero;
}

int Carta::consultarNumero() {
    return numero;
}

std::string Carta::mostrarCarta() {
    std::string nombreColor;
    if (color == 0) {
        nombreColor = "Rojo";
    } else if (color == 1) {
        nombreColor = "Azul";
    } else {
        nombreColor = "Desconocido";
    }
    return nombreColor + " " + std::to_string(numero);
}
