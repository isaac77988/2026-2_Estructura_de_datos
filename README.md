## Juego de Cartas en C++

Proyecto de la asignatura **Estructura de Datos (2026-2)**. Implementación en consola de un juego de cartas por rondas (de 2 a 4 jugadores) usando clases en C++, arreglos estáticos y guardado de partidas en archivos `.txt`.

### Estructura del proyecto

* **Carta (`Carta.h` / `Carta.cpp`):** Define el color (0 = Rojo, 1 = Azul) y el número de cada carta (del 1 al 14).
* **Jugador (`Jugador.h` / `Jugador.cpp`):** Maneja la mano de 7 cartas del jugador, el conteo de puntos y valida qué cartas puede lanzar.
* **Juego (`Juego.h` / `Juego.cpp`):** Controla las 7 rondas, reparte el mazo de 28 cartas sin repetir, evalúa quién gana cada turno y guarda o carga la partida.
* **Main (`main.cpp`):** Menú inicial para crear una partida nueva o continuar una guardada.

### Diagrama de clases

<p align="center">
  <img src="./Diagrama%20UML.jpg" width="520">
</p>

### Cómo compilar y ejecutar

Desde la consola con `g++`:

    g++ main.cpp Juego.cpp Jugador.cpp Carta.cpp -o juego
    ./juego