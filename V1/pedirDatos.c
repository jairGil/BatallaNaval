/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*  Validacion de numeros con codigo ASCII  incluyebdo el 0*/
int validaInt (char * numero) {
    // Reocrrer en totalidad la cadena que almacena el numero
    for (int i = 0; i < strlen(numero); i++) {
        /* 
            el valor 48 corresponde al caracter 1
            el valor 57 corresponde al caracter 9
        */
        if (numero[i] < 48 || numero[i] > 57) {
            printf("\nIngrese un numero valido\n");
            return 0;
        }
    }
    return 1;
}

/* Pedir un numero entero mayor a 0 desde consola */
int pideInt(char * txt) {
    char valido[5];
    int esValido;
    int num;

    // Ciclo indeterminado para obligar una entrada de dato válida
    do {
        printf("%s", txt);
        scanf("%s", valido);

        // Dato para poder validar si es mayor a cero
        esValido = validaInt(valido);

        /*
            Si esValido == 1 convierte el numero en entero para poder validar
            que este sea mayor a cero
        */
        if (esValido) {
            num = atoi(valido);
            if (num == 0) {
                printf("\nIngrese un numero mayor a 0");
                esValido = 0;
            }
        } 

    } while (esValido == 0);

    return num;
}

/*  Validacion de numeros con codigo ASCII incluyendo el numero 0*/
int validaIntConCero (char * numero) {
    // Reocrrer en totalidad la cadena que almacena el numero
    for (int i = 0; i < strlen(numero); i++) {
        /* 
            el valor 47 corresponde al caracter 0
            el valor 57 corresponde al caracter 9
        */
        if (numero[i] < 47 || numero[i] > 57) {
            printf("\nIngrese un numero valido\n");
            return 0;
        }
    }
    return 1;
}

/* Pedir un numero entero mayor o igual a 0 desde consola */
int pideIntNave(char * txt) {
    char valido[5];
    int esValido;
    int num;

    // Ciclo indeterminado para obligar una entrada de dato válida
    do {
        printf("%s", txt);
        scanf("%s", valido);

        // Dato para poder validar si es mayor a cero
        esValido = validaIntConCero(valido);

        /*
            Si esValido == 1 convierte el numero en entero para poder validar
            que este sea mayor a cero
        */
        if (esValido) {
            num = atoi(valido);
            if (num < 0) {
                printf("\nIngrese un numero mayor o igual a 0\n");
                esValido = 0;
            }
        } 

    } while (esValido == 0);

    return num;
}