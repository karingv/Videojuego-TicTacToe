#include "miniwin.h"
#include "tictactoe.h"
#include <iostream>

using namespace std;
using namespace miniwin;

char jugador = 'X';
char IA = 'O';

void seleccionaJugador() {

    vredimensiona(400, 200);
    color(BLANCO);
    texto(50, 50, "Elige tu símbolo:");
    texto(50, 100, "Presiona 'X' para ser X");
    texto(50, 150, "Presiona 'O' para ser O");
    refresca();

    while (true) {
        int tecla = miniwin::tecla();
        if (tecla == 'X') {
            jugador = 'X';
            IA = 'O';
            break;
        } else if (tecla == 'O') {
            jugador = 'O';
            IA = 'X';
            break;
        }
        espera(100);
    }
}

int main() {
    cout << "Iniciando el juego...\n";
    seleccionaJugador();
  
    vredimensiona(400, 400); // Redimensiona la ventana
    inicializaJuego();

    cout << "Jugador seleccionado: " << jugador << "\n";
    cout << "IA: " << IA << "\n";

    while (true) {
        dibujaTablero();
        if (turnoJugador) {
            cout << "Turno del jugador...\n";
            if (manejaEntradaJugador()) {
                cout << "Jugador hizo un movimiento.\n";
                if (checaGanador() || tableroLleno()) {
                    break;
                }
                turnoJugador = false;
            }
        } else {
            cout << "Turno de la IA...\n";
            realizaMovimientoAI(); // Utiliza la función que realiza el movimiento y marca las jugadas de la IA
            if (checaGanador() || tableroLleno()) {
                break;
            }
            turnoJugador = true;
        }
        espera(100);
    }

    dibujaTablero();
    if (checaGanador()) {
        mensaje((turnoJugador ? "Has ganado!" : "La IA ha ganado!"));
    } else {
        mensaje("Es un empate!");
    }

    vcierra();
    return 0;
}

