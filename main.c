#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"

/*
 * 
 */
int main(int argc, char** argv) {
    
    configuracion config;
    tablero tab;

    pideConfiguracion(&config);
    creaTablero(&config, &tab);
    llenaTablero(&config, &tab);

    mostrarTablero(tab);

    return (EXIT_SUCCESS);
}

