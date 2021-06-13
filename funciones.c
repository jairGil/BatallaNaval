/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include "pedirDatos.c"
#include "estructuras.h"
#define HORIZONTAL 1
#define VERTICAL 0

/*Pide a un usuario las configuraciones iniciales del juego*/
void pideConfiguracion(configuracion *config)
{
    printf("\n\t.:CONFIGURACION DEL JUEGO:.\n");
    config->tamX = pideInt("Tamano en X: ");
    config->tamY = pideInt("Tamano en Y: ");
    config->noNaves = pideInt("Numero de Naves: ");
    config->longMax = pideInt("Longitud maxima de las naves: ");
    config->noTtiros = pideInt("Maximo de tiros: ");
}

/*Crea el tablero en base a la configuracion del juego*/
void creaTablero(configuracion *config, tablero *tab)
{
    tab->tamX = config->tamX;
    tab->tamY = config->tamY;
    tab->naves = (nave *)malloc(sizeof(nave) * config->noNaves);
    tab->tiradas = (casilla *)malloc(sizeof(casilla) * config->noTtiros);
}

/* Setear la orientacion de una nave */
int setOrientacion () {
    int valor;
    printf("\nOrientacion\n1.Horizontal (o un numero impar)\n2.Vertical (o un numero par)");
    valor = pideInt("Orientacion de la nave: ");
    if (valor % 2 == 0)
        return VERTICAL;
    else 
        return HORIZONTAL;
}

/* Setear las casillas que ocupa la nave */
casilla * setCasillas (int tam, int orientacion) {
    casilla * casillas;
    casillas = (casilla *) malloc(sizeof(casilla) * tam);

    for (int i = 0; i < tam; i++) {
        int incorrecto = 0;
        if (i > 0) 
        {
            switch (orientacion)
            {
            case HORIZONTAL:
                do {
                    casillas[i].cord.x = pideInt("\nX: ");
                    casillas[i].cord.y = pideInt("\nY: ");

                    if (casillas[i].cord.x != casillas[i-1].cord.x) 
                    {
                        printf("\nLa posicion no corresponde a la orientacion");
                        incorrecto = 1;
                    }

                    if ( (casillas[i].cord.x == casillas[i-1].cord.x) && (casillas[i].cord.y == casillas[i-1].cord.y) ) 
                    {
                        printf("\nNo puede colocar sobre una casilla ya ocupada por la nave");
                        incorrecto = 1;
                    }
                } while (incorrecto);
                break;
            case VERTICAL:

                break;
            }
        } else {
            casillas[i].cord.x = pideInt("X: ");
            casillas[i].cord.y = pideInt("Y: ");
        }
    }
}

/* Setear los valores de las naves */
nave setNave(int n, int tam) {
    nave nav;
    for(int i = 0; i < n; i++) {
        nav.longitud = tam;
        nav.estado = 0;
        if (tam > 1) {
            nav.orientacion = setOrientacion();
        } else {
            nav.orientacion = HORIZONTAL;
        }
        nav.casillas = setCasillas(tam, nav.orientacion);
    }
}

/*Crea y coloca las naves del juego en el tablero*/
void llenaTablero(configuracion *config, tablero *tab)
{
    int i = 0;
    int n = 0;
    int tamano;
    int cantidad;

    printf("\n\t.:CREACION DE LAS NAVES:.");
    // Control de numero de naves
    while (n < config->noNaves)
    {
        // Controlar que el tamaño de las naves no sea mayor que el maximo permitido
        do
        {
            printf("\nCantidad de naves asignadas: %d\n", n);
            tamano = pideInt("Tamano de las naves: ");
            if (tamano > config->longMax)
                printf("La longitud supera el maximo permitido (%d)\n", config->longMax);
            else
            {
                // Asignar la cantidad de naves de el tamaño ingresado anteriormente
                do
                {
                    cantidad = pideInt("Cantidad de naves a asignar: ");

                    n += cantidad;

                    if (n > config->noNaves)
                    {
                        printf("\nEste numero de naves rebasa el maximo permitido\n");
                        n -= cantidad;
                    } else
                    {
                        for (i; i < n; i++)
                        {
                            printf("Nave no.%d\n", i);
                            tab->naves[i] = setNave(cantidad, tamano);
                        }
                    }
                } while (n > config->noNaves);
            }
        } while (tamano > config->longMax);
    }
}