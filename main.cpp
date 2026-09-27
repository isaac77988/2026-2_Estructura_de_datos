#include <iostream>
#include <string>
#include "Juego.h"

using namespace std;

int main() {
    Juego miJuego;
    int opcion;

    cout << "===============================" << endl;
    cout << "   JUEGO DE CARTAS C++ (POO)   " << endl;
    cout << "===============================" << endl;
    cout << "1. Iniciar Nueva Partida" << endl;
    cout << "2. Cargar Partida Guardada" << endl;
    cout << "Elige una opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        int numJugadores;
        cout << "\nCuantos jugadores participaran (2 a 4)? ";
        cin >> numJugadores;
        
        if (numJugadores > 4) numJugadores = 4; 
        if (numJugadores < 2) numJugadores = 2;

        for (int i = 0; i < numJugadores; i++) {
            string nombre;
            cout << "Ingresa el nombre del jugador " << (i + 1) << ": ";
            cin >> nombre;
            miJuego.agregarJugador(nombre);
        }
        
        miJuego.iniciarPartida();

    } else if (opcion == 2) {
        string archivo;
        cout << "\nIngresa el nombre del archivo a cargar (ej. partida.txt): ";
        cin >> archivo;
        
        if (miJuego.cargarPartida(archivo)) {
            cout << "\n>>> Partida cargada exitosamente. <<<" << endl;
        } else {
            cout << "Error: No se pudo abrir el archivo especificado." << endl;
            return 1;
        }
    } else {
        cout << "Opcion invalida. Saliendo del programa..." << endl;
        return 0;
    }

    while (miJuego.estadoPartida()) {
        miJuego.jugarRonda();

        if (miJuego.estadoPartida()) {
            char guardar;
            cout << "\nDeseas guardar la partida y salir ahora? (s/n): ";
            cin >> guardar;
            
            if (guardar == 's' || guardar == 'S') {
                string archivo;
                cout << "Ingresa el nombre del archivo para guardar (ej. partida.txt): ";
                cin >> archivo;
                
                if (miJuego.guardarPartida(archivo)) {
                    cout << "Estado guardado correctamente en " << archivo << ". Hasta luego!" << endl;
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