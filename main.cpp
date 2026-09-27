#include <iostream>
#include <string>
#include <limits>
#include "Juego.h"

using namespace std;

string normalizarNombreArchivo(string archivo) {
    if (archivo.length() < 4 || archivo.substr(archivo.length() - 4) != ".txt") {
        archivo += ".txt";
    }
    return archivo;
}

int main() {
    Juego miJuego;
    int opcion;

    cout << "===============================" << endl;
    cout << "   JUEGO DE CARTAS C++ (POO)   " << endl;
    cout << "===============================" << endl;
    cout << "1. Iniciar Nueva Partida" << endl;
    cout << "2. Continuar Partida Guardada" << endl;
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opcion == 1) {
        int numJugadores;
        cout << "\nCuantos jugadores participaran (2 a 4)? ";
        cin >> numJugadores;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (numJugadores > 4) numJugadores = 4;
        if (numJugadores < 2) numJugadores = 2;

        for (int i = 0; i < numJugadores; i++) {
            string nombre;
            cout << "Ingresa el nombre del jugador " << (i + 1) << " (sin espacios): ";
            cin >> nombre;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            miJuego.agregarJugador(nombre);
        }

        miJuego.iniciarPartida();

    } else if (opcion == 2) {
        string archivo;
        cout << "\nIngresa el nombre del archivo a cargar (ej. partida1.txt): ";
        getline(cin, archivo);
        archivo = normalizarNombreArchivo(archivo);

        if (miJuego.cargarPartida(archivo)) {
            cout << "\n>>> Partida '" << archivo << "' cargada exitosamente. Continuando juego... <<<" << endl;
        } else {
            cout << "Error: No se encontro el archivo '" << archivo << "'." << endl;
            return 1;
        }
    } else {
        cout << "Opcion invalida. Saliendo del programa..." << endl;
        return 0;
    }

    while (miJuego.estadoPartida()) {
        miJuego.jugarRonda();

        if (miJuego.estadoPartida()) {
            int accionRonda = 0;
            cout << "\n------------------------------------------" << endl;
            cout << "1. Continuar partida (Siguiente ronda)" << endl;
            cout << "2. Guardar partida y salir" << endl;
            cout << "Elige una opcion: ";
            cin >> accionRonda;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (accionRonda == 2) {
                string archivo;
                cout << "Ingresa el nombre del archivo para guardar (ej. partida1.txt): ";
                getline(cin, archivo);
                archivo = normalizarNombreArchivo(archivo);

                if (miJuego.guardarPartida(archivo)) {
                    cout << "Estado guardado correctamente en '" << archivo << "'. Hasta luego!" << endl;
                } else {
                    cout << "Error al intentar escribir el archivo en disco." << endl;
                }
                return 0;
            }
        }
    }

    cout << "\n==========================================" << endl;
    cout << "   FIN DE LA PARTIDA (7 Rondas Jugadas)   " << endl;
    cout << "==========================================" << endl;

    return 0;
}
