#include <cstdlib>
#include <iostream>
#include <ctime>
#include "funciones.h"

using namespace std;

void generarPieza(unsigned char pieza[4]) {

    int tipo = rand() % 7;

    switch (tipo) {

    case 0: // Cuadrado
        pieza[0] = 0b11000000;
        pieza[1] = 0b11000000;
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

    case 3: // J (CORREGIDA)
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
        pieza[0] = 0b11000000;
        pieza[1] = 0b01100000;
        pieza[2] = 0b00000000;
        pieza[3] = 0b00000000;
        break;

    case 6: // Z
        pieza[0] = 0b01100000;
        pieza[1] = 0b11000000;
        pieza[2] = 0b00000000;
        pieza[3] = 0b00000000;
        break;
    }
}

void ajustarIzquierda(unsigned char pieza[4])
{
    bool puedeMover = true;

    while (puedeMover)
    {
        for (int i = 0; i < 4; i++)
        {
            if (pieza[i] & 0b10000000)
            {
                puedeMover = false;
                break;
            }
        }

        if (puedeMover)
        {
            for (int i = 0; i < 4; i++)
                pieza[i] <<= 1;
        }
    }
}

void ajustarArriba(unsigned char pieza[4])
{
    while (pieza[0] == 0)
    {
        bool vacio = true;
        for (int i = 0; i < 4; i++)
            if (pieza[i] != 0)
                vacio = false;

        if (vacio) break;

        for (int i = 0; i < 3; i++)
            pieza[i] = pieza[i + 1];

        pieza[3] = 0;
    }
}

void rotarPieza(unsigned char pieza[4]) {

    unsigned char nueva[4] = {0};

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {

            if((pieza[3 - j] >> (7 - i)) & 1) {
                nueva[i] |= (1 << (7 - j));
            }

        }
    }

    for(int i = 0; i < 4; i++) {
        pieza[i] = nueva[i];
    }

    ajustarIzquierda(pieza);
    ajustarArriba(pieza);
}

bool hayColision(unsigned char **tablero,
                 unsigned char pieza[4],
                 int posX,
                 int posY,
                 int alto,
                 int ancho)
{
    int bytesFila = (ancho + 7) / 8;

    for(int i = 0; i < 4; i++)
    {
        if(pieza[i] == 0)
            continue;

        int fila = posY + i;

        if(fila >= alto)
            return true;

        int byteIndex = posX / 8;
        int desplazamiento = posX % 8;

        unsigned char p1 = pieza[i] >> desplazamiento;
        unsigned char p2 = 0;

        if(desplazamiento != 0)
            p2 = pieza[i] << (8 - desplazamiento);

        if(posX < 0)
            return true;

        if(byteIndex >= bytesFila)
            return true;

        if(byteIndex == bytesFila - 1 && desplazamiento != 0 && p2 != 0)
            return true;

        if(tablero[fila][byteIndex] & p1)
            return true;

        if(desplazamiento != 0 && byteIndex + 1 < bytesFila)
        {
            if(tablero[fila][byteIndex + 1] & p2)
                return true;
        }
    }

    return false;
}

// (resto igual)
void fijarPieza(unsigned char **tablero,
                unsigned char pieza[4],
                int posX,
                int posY,
                int ancho,
                int alto)
{
    int bytesFila = (ancho + 7) / 8;

    for(int i = 0; i < 4; i++)
    {
        int fila = posY + i;

        if(fila < 0 || fila >= alto)
            continue;

        int byteIndex = posX / 8;
        int desplazamiento = posX % 8;

        unsigned char parte1 = pieza[i] >> desplazamiento;

        if(byteIndex < bytesFila)
            tablero[fila][byteIndex] |= parte1;

        if(desplazamiento != 0 && byteIndex + 1 < bytesFila)
        {
            unsigned char parte2 = pieza[i] << (8 - desplazamiento);
            tablero[fila][byteIndex + 1] |= parte2;
        }
    }
}

void crearTablero(unsigned char **&tablero, int alto, int bytesFila)
{
    tablero = new unsigned char*[alto];

    for(int i = 0; i < alto; i++)
    {
        tablero[i] = new unsigned char[bytesFila];
        for(int j = 0; j < bytesFila; j++)
            tablero[i][j] = 0;
    }
}

void liberarTablero(unsigned char **tablero, int alto)
{
    for(int i = 0; i < alto; i++)
        delete[] tablero[i];

    delete[] tablero;
}

bool filaLlena(unsigned char *fila, int bytesFila)
{
    for(int i = 0; i < bytesFila; i++)
        if(fila[i] != 255)
            return false;

    return true;
}

void eliminarFila(unsigned char **tablero, int fila, int alto,int bytesFila)
{
    for(int i = fila; i > 0; i--)
        for(int j = 0; j < bytesFila; j++)
            tablero[i][j] = tablero[i - 1][j];

    for(int j = 0; j < bytesFila; j++)
        tablero[0][j] = 0;
}

void limpiarFilas(unsigned char **tablero, int alto, int bytesFila)
{
    for(int i = 0; i < alto; i++)
    {
        if(filaLlena(tablero[i], bytesFila))
        {
            eliminarFila(tablero, i, alto, bytesFila);
            i--;
        }
    }
}

void imprimirTableroConPieza(unsigned char **tablero,
                             unsigned char pieza[4],
                             int posX,
                             int posY,
                             int alto,
                             int ancho)
{
    int bytesFila = (ancho + 7) / 8;

    for(int i = 0; i < alto; i++)
    {
        for(int j = 0; j < bytesFila; j++)
        {
            unsigned char filaTemp = tablero[i][j];

            if(i >= posY && i < posY + 4)
            {
                int byteIndex = posX / 8;
                int desplazamiento = posX % 8;

                if(j == byteIndex)
                    filaTemp |= (pieza[i - posY] >> desplazamiento);

                if(j == byteIndex + 1 && desplazamiento != 0)
                    filaTemp |= (pieza[i - posY] << (8 - desplazamiento));
            }

            for(int bit = 7; bit >= 0; bit--)
                cout << ((filaTemp & (1 << bit)) ? "#" : ".");
        }
        cout << endl;
    }
}