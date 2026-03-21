#include <iostream>
#include <cstdlib>
#include <ctime>
#include "funciones.h"

using namespace std;

int main()
{
    srand(time(NULL));

    int ancho, alto;

    // Pedir ancho mínimo 8
    do {
        cout << "Ingrese el ancho del tablero: ";
        cin >> ancho;
    } while(ancho < 8);

    // Pedir alto mínimo 8
    do {
        cout << "Ingrese el alto del tablero: ";
        cin >> alto;
    } while(alto < 8);

    int bytesFila = ancho / 8;

    unsigned char **tablero;
    crearTablero(tablero, alto, bytesFila);

    unsigned char pieza[4];
    generarPieza(pieza);

    int posX = 2;
    int posY = 0;

    char tecla;

    while (true)
    {
        system("cls");

        imprimirTableroConPieza(tablero, pieza, posX, posY, alto, ancho);

        cout << "\nControles:\n";
        cout << "a = izquierda d = derecha  s = bajar  w = rotar  q = salir\n";

        cin >> tecla;

        // salir
        if (tecla == 'q')
            break;

        // mover izquierda
        if (tecla == 'a')
        {
            posX--;

            if (hayColision(tablero, pieza, posX, posY, alto, ancho))
                posX++;
        }

        // mover derecha
        if (tecla == 'd')
        {
            posX++;

            if (hayColision(tablero, pieza, posX, posY, alto, ancho))
                posX--;
        }

        // rotar
        if (tecla == 'w')
        {
            rotarPieza(pieza);

            if (hayColision(tablero, pieza, posX, posY, alto, ancho))
            {
                // deshacer rotación
                rotarPieza(pieza);
                rotarPieza(pieza);
                rotarPieza(pieza);
            }
        }

        if (tecla == 's')
        {

            if (!hayColision(tablero, pieza, posX, posY + 1, alto, ancho))
            {
                posY++;
            }
            else
            {

                fijarPieza(tablero, pieza, posX, posY, ancho);

                limpiarFilas(tablero, alto, bytesFila);

                generarPieza(pieza);

                posX = 2;
                posY = 0;

                if (hayColision(tablero, pieza, posX, posY, alto, ancho))
                {
                    system("cls");
                    imprimirTableroConPieza(tablero, pieza, posX, posY, alto, ancho);
                    cout << "\nGAME OVER\n";
                    break;
                }
            }
        }
    }

    liberarTablero(tablero, alto);
    return 0;

}
