#ifndef TICTACTOE_H
#define TICTACTOE_H

const int TAM = 3;

// Variables globales externamente declaradas
extern char tablero[TAM][TAM];
extern bool turnoJugador;
extern char jugador;
extern char IA;

// Declaraciones de funciones
void inicializaJuego();
void dibujaTablero();
void dibujaGanador(int fila, int col, bool esFila);
void dibujaGanadorDiagonal(bool esPrincipal);
bool manejaEntradaJugador();
bool checaGanador();
bool tableroLleno();
int evaluaTablero();
int miniMax(char tablero[TAM][TAM], int profundidad, bool esMaximizador);
void mejorMovimiento(int &fila, int &col);
void realizaMovimientoAI();

#endif // TICTACTOE_H

