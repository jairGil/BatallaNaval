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
void pideConfiguracion(configuracion *config) {
    printf("\n\t.:CONFIGURACION DEL JUEGO:.\n");
    config->tamX = pideInt("Tamano en X: ");
    config->tamY = pideInt("Tamano en Y: ");
    config->noNaves = pideInt("Numero de Naves: ");
    config->longMax = pideInt("Longitud maxima de las naves: ");
    config->noTtiros = pideInt("Maximo de tiros: ");
}

/*Crea el tablero en base a la configuracion del juego*/
void creaTablero(configuracion *config, tablero *tab) {
    tab->tamX = config->tamX;
    tab->tamY = config->tamY;
    tab->naves = (nave *)malloc(sizeof(nave) * config->noNaves);
    tab->tiradas = (casilla *)malloc(sizeof(casilla) * config->noTtiros);
    tab->mapa = (int **)malloc(sizeof(int *) * config->tamX);
    
    for(int i = 0; i < config->tamX; i++){
        tab->mapa[i] = (int *)malloc(sizeof(int) * config->tamY);
        for(int j = 0; j < config->tamY; j++){
            tab->mapa[i][j] = 0;
        }
    }
    tab->noTiros = 0;
}

/* Setear la orientacion de una nave */
int setOrientacion() {
    int valor;
    printf("\nOrientacion\n1.Horizontal (o un numero impar)\n2.Vertical (o un numero par)");
    valor = pideInt("\nOrientacion de la nave: ");
    if (valor % 2 == 0)
        return VERTICAL;
    else
        return HORIZONTAL;
}

/* Setear las casillas que ocupa la nave */
casilla *setCasillas(int tam, int orientacion, tablero *tab) {
    casilla *casillas;
    casillas = (casilla *)malloc(sizeof(casilla) * tam);

    casillas[0].cord.x = pideInt("\nX: ");
    casillas[0].cord.y = pideInt("Y: ");

    tab->mapa[casillas[0].cord.x - 1][casillas[0].cord.y - 1] = 1;
    
    switch (orientacion) {
        case HORIZONTAL:
            for (int i = 1; i < tam; i++) {
                casillas[i].cord.y = casillas[i-1].cord.y + 1;
                casillas[i].cord.x = casillas[0].cord.x;
                tab->mapa[casillas[i].cord.x - 1][casillas[i].cord.y - 1] = 1;
            }
            break;
        case VERTICAL:
            for (int i = 1; i < tam; i++) {
                casillas[i].cord.x = casillas[i-1].cord.x + 1;
                casillas[i].cord.y = casillas[0].cord.y;
                tab->mapa[casillas[i].cord.x - 1][casillas[i].cord.y - 1] = 1;
            }
            break;
    }

    return casillas;
}

/* Setear los valores de las naves */
nave setNave(int n, int tam, tablero *tab) {
    nave nav;
    nav.longitud = tam;
    nav.estado = 0;
    if (tam > 1) {
        nav.orientacion = setOrientacion();
    } else {
        nav.orientacion = HORIZONTAL;
    }
    nav.casillas = setCasillas(tam, nav.orientacion, tab);
}

/*Crea y coloca las naves del juego en el tablero*/
void llenaTablero(configuracion *config, tablero *tab) {
    int i = 0;
    int n = 0;
    int tamano;
    int cantidad;

    printf("\n\t.:CREACION DE LAS NAVES:.");
    // Control de numero de naves
    while (n < config->noNaves) {
        // Controlar que el tamaño de las naves no sea mayor que el maximo permitido
        do {
            printf("\nCantidad de naves asignadas: %d\n", n);
            tamano = pideInt("Tamano de las naves: ");
            if (tamano > config->longMax)
                printf("La longitud supera el maximo permitido (%d)\n", config->longMax);
            else {
                // Asignar la cantidad de naves de el tamaño ingresado anteriormente
                do {
                    cantidad = pideInt("Cantidad de naves a asignar: ");
                    n += cantidad;
                    if (n > config->noNaves) {
                        printf("\nEste numero de naves rebasa el maximo permitido\n");
                        n -= cantidad;
                    } else {
                        for (i; i < n; i++) {
                            printf("Nave no.%d\n", i);
                            tab->naves[i] = setNave(cantidad, tamano, tab);
                        }
                    }
                } while (n > config->noNaves);
            }
        } while (tamano > config->longMax);
    }
}

/********************/
/*Funciones de juego*/
/********************/

/*Verifica si 2 coordenadas son iguales*/
int comparaCordenada(const cordenada c1, const cordenada c2) {
    if (c1.x == c2.x && c1.y == c2.y) {
        return 1;
    }
    return 0;
}

/* Pide un tiro a un jugador */
int turnoJugador(tablero *jugador, tablero *rival, const configuracion config) {
    casilla c;
    casilla *cas;
    int ataque;
    nave navAtacada;

    printf("\n.:ATAQUE:.\n");
    c.cord.x = pideInt("Posicion en x: ");
    c.cord.y = pideInt("Posicion en y: ");
    cas = &c;
    llenaTiradas(jugador, rival, cas);
    ataque = validaTiro(rival, c.cord, config);

    switch (ataque) {
        case 0:
            printf("\nEl ataque dio al mar");
            break;
        case 1:
            navAtacada = buscarNave(rival, c, config);
            printf("\nEl ataque dio a una nave!");

            if (naveHundida(navAtacada)) {
                printf("\nHundiste una nave!");
            }
            break;
        case 2:
            printf("\nEsta posicion ya habia sido atacada");
            break;
    }
    
}

nave buscarNave(tablero *tab, const casilla c, const configuracion config) {
    for (int i = 0; i < config.noNaves ; i++) {        
        for(int j = 0; j < tab->naves[i].longitud; j++) {
            if(comparaCordenada(tab->naves[i].casillas[j].cord, c.cord)) {  
                return tab->naves[i];
            }
        }
    }
}

/*Verificar si una nave esta hundida*/
int naveHundida(nave nav) {
    if (nav.estado == nav.longitud) {
        return 1;
    }
    return 0;
}

/* Verifica que el jugador aun tenga tiradas disponibles */
int verificarTiros(const tablero tab, const configuracion config){
    return (config.noTtiros - tab.noTiros);
}

/* Verifica que aun haya naves en el tablero */
int navesFlotando(const tablero tab, const configuracion config) {
    int contador = config.noNaves;
    for (int i = 0; i < config.noNaves; i++) {
        if (naveHundida(tab.naves[i])) {
            contador--;
        }
    }
    return contador;
}

/* Verificar el estado del juego*/
int estadoJuego(const tablero tab, const configuracion config) {
    if (navesFlotando(tab, config) || verificarTiros(tab, config)) {
        return 1;
    }
    return 0;
}

/*Validar si un tiro da en una nave*/
int validaTiro(tablero *tab, const cordenada cord, const configuracion config)  {
    int i, j;
    for (i = 0; i < config.noNaves; i++) {
        for(j = 0; j < tab->naves[i].longitud; j++) {
            if(comparaCordenada(tab->naves[i].casillas->cord, cord)) {
                if (tab->naves[i].casillas->atacada != 1) {
                    tab->naves[i].estado++;
                    tab->naves[i].casillas->atacada = 1;
                    tab->mapa[tab->naves[i].casillas->cord.x - 1][tab->naves[i].casillas->cord.x - 1] = 2;
                    return 1; // Casilla nueva atacada
                }
                return 2; // Casilla atacada anteriormente
            }
        }
    }
    
    return 0; // Casilla atacada sin nave (cae en agua)
}

/* Llena el arreglo de tiros del jugador */
void llenaTiradas(tablero *jugador, tablero *rival,casilla *cas) {
    cas->atacada = 1;
    jugador->tiradas[jugador->noTiros] = *cas;
    jugador->noTiros++;
    rival->mapa[cas->cord.x - 1][cas->cord.y - 1] = 3;
}

/* Imprime el tablero en pantalla */
void mostrarTablero(const tablero tab) {
    for (int y = 0; y < tab.tamY; y++) {
            printf("|----");
        }
        
        printf("|\n");

    for (int x = 0; x < tab.tamX; x++) {
        for (int y = 0; y < tab.tamY; y++) {
            if (tab.mapa[x][y] == 1) {
                printf("| ██ ");
            } else if(tab.mapa[x][y] == 2) {
                printf("| ¤¤ ");
            } else if(tab.mapa[x][y] == 3) {
                printf("| xx ");
            } else {
                printf("|    ");
            }
        }

        printf("|\n");

        for (int y = 0; y < tab.tamY; y++) {
            printf("|----");
        }
        
        printf("|\n");
    }
}