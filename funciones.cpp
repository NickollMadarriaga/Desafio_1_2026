#include <cstdlib>

void generarPieza(unsigned char pieza[4]) {

    int tipo = rand() % 6;

    switch (tipo) {

    case 0: // Cuadrado
        pieza[0] = 0b00110000;
        pieza[1] = 0b00110000;
        pieza[2] = 0b00000000;
        pieza[3] = 0b00000000;
        break;

    case 1: // Línea
        pieza[0] = 0b11110000;
        pieza[1] = 0b00000000;
        pieza[2] = 0b00000000;
        pieza[3] = 0b00000000;
        break;

    case 2: // L
        pieza[0] = 0b10000000;
        pieza[1] = 0b10000000;
        pieza[2] = 0b11000000;
        pieza[3] = 0b00000000;
        break;

    case 3: // J
        pieza[0] = 0b01000000;
        pieza[1] = 0b01000000;
        pieza[2] = 0b11000000;
        pieza[3] = 0b00000000;
        break;

    case 4: // T
        pieza[0] = 0b11100000;
        pieza[1] = 0b01000000;
        pieza[2] = 0b00000000;
        pieza[3] = 0b00000000;
        break;

    case 5: // S
        pieza[0] = 0b01100000;
        pieza[1] = 0b11000000;
        pieza[2] = 0b00000000;
        pieza[3] = 0b00000000;
        break;
    }
}

void moverIzquierda(unsigned char pieza[4]) {

    for (int i = 0; i < 4; i++) {
        pieza[i] <<= 1;
    }

}
void moverDerecha(unsigned char pieza[4]) {

    for (int i = 0; i < 4; i++) {
        pieza[i] >>= 1;
    }

}
void fijarPieza(unsigned char **tablero,
                unsigned char pieza[4],
                int posX,
                int posY) {

    for (int i = 0; i < 4; i++) {

        unsigned char filaPieza = pieza[i] >> posX;

        tablero[posY + i][0] |= filaPieza;

    }

}

void rotarPieza(unsigned char pieza[4]) {
    unsigned char nueva[4] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((pieza[3-j] >> (7-i)) & 1) {
                nueva[i] |= (1 << (7-j));
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        pieza[i] = nueva[i];
    }
}
