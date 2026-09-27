#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
private:
    int color;
    int numero;

public:
    Carta();
    Carta(int color, int numero);

    int elegirColor();
    int elegirNumero();
    int consultarNumero();
    std::string mostrarCarta();
};

#endif
