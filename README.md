# \# Juego de Cartas en C++ (POO)

# 

# Proyecto académico para la asignatura \*\*Estructura de Datos (2026-2)\*\*. Implementación de un sistema de juego de cartas por rondas utilizando Programación Orientada a Objetos en C++, arreglos estáticos y persistencia de datos en disco.

# 

# \## Arquitectura y Diagrama UML

# 

# El sistema se divide en tres clases principales conectadas mediante relaciones de composición fuerte, garantizando el manejo estricto de memoria estática:

# 

# !\[Diagrama UML](./Diagrama%20UML.jpg)

# 

# \* \*\*`Carta`\*\*: Representa la unidad básica del mazo con atributos codificados para el color (`0` = Rojo, `1` = Azul) y el número (`1` al `14`).

# \* \*\*`Jugador`\*\*: Administra la mano estática de hasta 7 cartas (`Carta\[7]`), el conteo de cartas disponibles y el puntaje acumulado.

# \* \*\*`Juego`\*\*: Motor principal que controla los jugadores (`Jugador\[4]`), el barajado mediante el algoritmo \*\*Fisher-Yates\*\*, la evaluación de reglas por ronda (carta mayor o menor del color requerido) y la serialización mediante `<fstream>`.

# 

# \## Compilación y Ejecución

# 

# Para compilar todos los módulos desde la terminal (usando `g++`):

# 

# ```bash

# g++ main.cpp Juego.cpp Jugador.cpp Carta.cpp -o juego\_cartas

# ./juego\_cartas

