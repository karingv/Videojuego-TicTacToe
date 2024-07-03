#include "tictactoe.h"
#include "miniwin.h"
#include <iostream>

using namespace std;
using namespace miniwin;

extern char jugador;
extern char IA;

char tablero[TAM][TAM];
bool turnoJugador = true;
bool esMovimientoAI[TAM][TAM];

void inicializaJuego() {
    cout << "Inicializando el juego...\n";
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tablero[i][j] = ' ';
            esMovimientoAI[i][j] = false;
        }
    }
}

void dibujaTablero() {
    borra();
    color(BLANCO);
    for (int i = 1; i < TAM; i++) {
        linea(i * 100, 0, i * 100, 300);
        linea(0, i * 100, 300, i * 100);
    }
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tablero[i][j] != ' ') {
                if (esMovimientoAI[i][j]) {
                    color(BLANCO);
                } else if (tablero[i][j] == jugador) {
                    color(ROJO);
                } else {
                    color(VERDE);
                }
                texto(j * 100 + 50, i * 100 + 50, string(1, tablero[i][j]));
            }
        }
    }
    refresca();
}

void dibujaGanador(int fila, int col, bool esFila) {
    color(AZUL);
    if (esFila) {
        linea(0, fila * 100 + 50, 300, fila * 100 + 50);
    } else {
        linea(col * 100 + 50, 0, col * 100 + 50, 300);
    }
    refresca();
}

void dibujaGanadorDiagonal(bool esPrincipal) {
    color(AZUL);
    if (esPrincipal) {
        linea(0, 0, 300, 300);
    } else {
        linea(0, 300, 300, 0);
    }
    refresca();
}

bool manejaEntradaJugador() {
    float x, y;
    if (raton(x, y) && raton_boton_izq()) {
        int fila = y / 100;
        int col = x / 100;
        if (tablero[fila][col] == ' ') {
            tablero[fila][col] = jugador;
            esMovimientoAI[fila][col] = false;
            return true;
        }
    }
    return false;
}

bool checaGanador() {
    for (int i = 0; i < TAM; i++) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ') {
            dibujaGanador(i, 0, true);
            return true;
        }
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != ' ') {
            dibujaGanador(0, i, false);
            return true;
        }
    }
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ') {
        dibujaGanadorDiagonal(true);
        return true;
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ') {
        dibujaGanadorDiagonal(false);
        return true;
    }
    return false;
}

bool tableroLleno() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tablero[i][j] == ' ') return false;
        }
    }
    return true;
}

int evaluaTablero() {
    for (int i = 0; i < TAM; i++) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
            if (tablero[i][0] == IA) return +10;
            else if (tablero[i][0] == jugador) return -10;
        }
    }
    for (int i = 0; i < TAM; i++) {
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i]) {
            if (tablero[0][i] == IA) return +10;
            else if (tablero[0][i] == jugador) return -10;
        }
    }
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        if (tablero[0][0] == IA) return +10;
        else if (tablero[0][0] == jugador) return -10;
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
        if (tablero[0][2] == IA) return +10;
        else if (tablero[0][2] == jugador) return -10;
    }
    return 0;
}

int miniMax(char tablero[TAM][TAM], int profundidad, bool esMaximizador) {
    int puntuacion = evaluaTablero();
    if (puntuacion == 10) return puntuacion;
    if (puntuacion == -10) return puntuacion;
    if (tableroLleno()) return 0;

    if (esMaximizador) {
        int mejor = -1000;
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tablero[i][j] == ' ') {
                    tablero[i][j] = IA;
                    mejor = max(mejor, miniMax(tablero, profundidad + 1, !esMaximizador));
                    tablero[i][j] = ' ';
                }
            }
        }
        return mejor;
    } else {
        int mejor = 1000;
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tablero[i][j] == ' ') {
                    tablero[i][j] = jugador;
                    mejor = min(mejor, miniMax(tablero, profundidad + 1, !esMaximizador));
                    tablero[i][j] = ' ';
                }
            }
        }
        return mejor;
    }
}

void mejorMovimiento(int &fila, int &col) {
    int mejorVal = -1000;
    fila = -1;
    col = -1;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tablero[i][j] == ' ') {
                tablero[i][j] = IA;
                int movVal = miniMax(tablero, 0, false);
                tablero[i][j] = ' ';
                if (movVal > mejorVal) {
                    fila = i;
                    col = j;
                    mejorVal = movVal;
                }
            }
        }
    }
}

void realizaMovimientoAI() {
    int fila, col;
    mejorMovimiento(fila, col);
    tablero[fila][col] = IA;
    esMovimientoAI[fila][col] = true;
}


