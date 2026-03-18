#ifndef FUNCIONES_H
#define FUNCIONES_H


void crearTablero(unsigned char **&tablero, int alto, int bytesFila);

void liberarTablero(unsigned char **tablero, int alto);

void imprimirTableroConPieza(unsigned char **tablero,
                             unsigned char pieza[4],
                             int posX,
                             int posY,
                             int ancho);

bool filaLlena(unsigned char *fila, int bytesFila);

void eliminarFila(unsigned char **tablero, int fila, int alto, int bytesFila);

void limpiarFilas(unsigned char **tablero, int alto, int bytesFila);

void generarPieza(unsigned char pieza[4]);

void rotarPieza(unsigned char pieza[4]);

void moverIzquierda(unsigned char pieza[4]);

void moverDerecha(unsigned char pieza[4]);

bool hayColision(unsigned char **tablero, unsigned char pieza[4],
                 int posX, int posY, int alto, int ancho);

void fijarPieza(unsigned char **tablero, unsigned char pieza[4],
                int posX, int posY);



#endif
