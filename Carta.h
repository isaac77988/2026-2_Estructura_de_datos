#ifndef CARTA_H
#define CARTA_H
#include <string>

class Carta {
private:
    int color;
    int numero;
public:
    carta();
    carta(int color, int numero);

    int elegirColor();
    int elegirNumero();
    std::string mostarCarta();
};
#endif