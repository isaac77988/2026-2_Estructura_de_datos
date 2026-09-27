#include "Carta.h"

Carta::Carta() {
    color = 0;
    numero = 0;
}

Carta::Carta(int c, int n) {
    color = c;
    numero = n;
}
int carta::elegirColor() {
    return color;
}

int carta::elegirNumero() {
    return numero;
}

std::string Carta::mostrarCarta() {
    std::string nombreColor;
    if (Color== 0) {
        nombreColor = "Rojo";
    } else if (Color == 1) {
        nombreColor = "Azul";
    } else {
        nombreColor = "Desconocido";
    }
    return nombreColor + " " + std::to_string(numero); }
    