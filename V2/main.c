#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"

/*
 * 
 */
int main(int argc, char** argv) {
    
    configuracion config;
    tablero tab[2];
    int contador = 1;

    printf("\n\t.:CONFIGURACION DEL JUEGO:.\n");
    setConfiguracion(config);
    pideConfiguracion();

    for (int i = 0; i < 2; i++) {
        printf("\n\t.:LLENAR EL TABLERO DEL JUGADOR %d:.\n", i + 1);
        creaTablero(&tab[i]);
        llenaTablero(&tab[i]);
    }
    

    do {
        for (int j = 0; j < 2; j++) {
            system("clear");
            printf("\n.:TURNO: %d JUGADOR: %d:.", contador, j + 1);
            printf("\n\tTABLERO\n");
            mostrarTablero(&tab[j]);
            
            printf("\n\t.:ATAQUE DEL JUGADOR %d:.\n", j + 1);
            if (j == 0) {
                printf("%s", turnoJugador(&tab[0], &tab[1]));
            } else {
                printf("%s", turnoJugador(&tab[1], &tab[0]));
            }
        }
        contador++;
    } while (estadoJuego(tab[0]) && estadoJuego(tab[1]));


    system("clear");
    if (navesFlotando(tab[0]) == 0) {
        printf("\n\t.:GANA EL JUGADOR 2:.\n\n");
    } else if (navesFlotando(tab[1]) == 0) {
        printf("\n\t.:GANA EL JUGADOR 1:.\n\n");
    }else{
        printf("\n\t.:NO HAY GANADOR:.\n\n");
    }

    for (int i = 0; i < 2; i++) {
        printf("\n\tTABLERO DEL JUGADOR %d\n", i + 1);
        mostrarTablero(&tab[i]);
    }

    return (EXIT_SUCCESS);
}

