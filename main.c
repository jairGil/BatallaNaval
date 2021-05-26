/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: salas
 *
 * Created on 26 de mayo de 2021, 05:24 PM
 */

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

    return (EXIT_SUCCESS);
}

