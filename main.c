#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"

/*
 * 
 */
int main(int argc, char** argv) {
    
    configuracion config;
    tablero tab[2];

    pideConfiguracion(&config);
    creaTablero(&config, &tab[0]);
    creaTablero(&config, &tab[1]);

    llenaTablero(&config, &tab[0]);
    llenaTablero(&config, &tab[1]);

    for (int i = 0;i < config.noTtiros; i++) {
        for (int j = 0; j < 2; j++) {
            system("clear");
            printf("\n\tTablero del jugador %d\n", j + 1);
            mostrarTablero(tab[j]);
            if (j == 0) {
                turnoJugador(&tab[0], &tab[1], config);
            } else {
                turnoJugador(&tab[1], &tab[0], config);
            }
        }

        if(estadoJuego(tab[0], config) && estadoJuego(tab[1], config)){
            break;
        }
    }

    return (EXIT_SUCCESS);
}

