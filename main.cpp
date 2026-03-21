#include <iostream>
#include <cstdlib>
#include <ctime>
#include "funciones.h"

using namespace std;

int main()
{
    srand(time(NULL));

    int ancho, alto;

    // 🔹 VALIDACIÓN ANCHO
    do {
        cout << "Ingrese el ancho del tablero (minimo 8 y multiplos de 8): ";
        cin >> ancho;

        if(ancho < 8 || ancho % 8 != 0) {
            cout << "❌ Error: debe ser minimo 8 y multiplo de 8\n";
        }

    } while(ancho < 8 || ancho % 8 != 0);

    // 🔹 VALIDACIÓN ALTO
    do {
        cout << "Ingrese el alto del tablero (minimo 8 y multiplos de 8): ";
        cin >> alto;

        if(alto < 8 || alto % 8 != 0) {
            cout << "❌ Error: debe ser minimo 8 y multiplo de 8\n";
        }

    } while(alto < 8 || alto % 8 != 0);

    int bytesFila = (ancho + 7) / 8;

    unsigned char **tablero;
    crearTablero(tablero, alto, bytesFila);

    unsigned char pieza[4];
    generarPieza(pieza);
    ajustarIzquierda(pieza);
    ajustarArriba(pieza);

    int posX = 2;
    int posY = 0;

    char tecla;

    while (true)
    {
        system("cls"); // 🔥 limpiar pantalla

        imprimirTableroConPieza(tablero, pieza, posX, posY, alto, ancho);

        cout << "\nControles:\n";
        cout << "a = izquierda | d = derecha | s = bajar | w = rotar | q = salir\n";

        cin >> tecla;

        if (tecla == 'q')
            break;

        if (tecla == 'a')
        {
            posX--;
            if (hayColision(tablero, pieza, posX, posY, alto, ancho))
                posX++;
        }

        if (tecla == 'd')
        {
            posX++;
            if (hayColision(tablero, pieza, posX, posY, alto, ancho))
                posX--;
        }

        if (tecla == 'w')
        {
            rotarPieza(pieza);

            if (hayColision(tablero, pieza, posX, posY, alto, ancho))
            {
                // revertir rotación
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
                fijarPieza(tablero, pieza, posX, posY, ancho, alto);
                limpiarFilas(tablero, alto, bytesFila);

                generarPieza(pieza);
                ajustarIzquierda(pieza);
                ajustarArriba(pieza);

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