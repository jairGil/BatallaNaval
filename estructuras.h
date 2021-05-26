/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estructuras.h
 * Author: salas
 *
 * Created on 26 de mayo de 2021, 05:26 PM
 */

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#ifdef __cplusplus
extern "C" {
#endif


/*Coordenadas (x,y)*/
typedef struct cordenada {
    int x;
    char y;
} cordenada;

/*Casilla de un tablero, contiene coordenada (x,y)*/
typedef struct casilla {
    cordenada cord;
    int atacada;
} casilla;

/*Hace referencia a las naves o barcos de el juego*/
typedef struct nave {
    int longitud;
    int orientacion;
    casilla * casillas;
    int estado;
} nave;

/*Estructura que almacena a las naves y las casillas atacadas*/
typedef struct tablero {
    int tamX;
    int tamY;
    nave * naves;
    casilla * tiradas;
} tablero;

/*Almacena la configuracion con la que se iniciará el juego*/
typedef struct {
    int tamX;
    int tamY;
    int noNaves;
    int noTtiros;
    int longMax;
} configuracion;


#ifdef __cplusplus
}
#endif

#endif /* ESTRUCTURAS_H */

