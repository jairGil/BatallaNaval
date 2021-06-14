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
    int y;
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
    int ** mapa;
    nave * naves;
    casilla * tiradas;
    int noTiros;
} tablero;

/*Almacena la configuracion con la que se iniciará el juego*/
typedef struct {
    int tamX;
    int tamY;
    int noNaves;
    int noTtiros;
    int longMax;
} configuracion;


void pideConfiguracion(configuracion *config);
void creaTablero(configuracion *config, tablero *tab);
int setOrientacion();
casilla *setCasillas(int tam, int orientacion, tablero *tab);
nave setNave(int n, int tam, tablero *tab);
void llenaTablero(configuracion *config, tablero *tab);

/* FUNCIONES DEL JUEGO */

int comparaCordenada(const cordenada c1, const cordenada c2);
int turnoJugador(tablero *jugador, tablero *rival, const configuracion config);
nave buscarNave(tablero *tab, const casilla c, const configuracion config);
int naveHundida(nave nav);
int verificarTiros(const tablero tab, const configuracion config);
int navesFlotando(const tablero tab, const configuracion config);
int estadoJuego(const tablero tab, const configuracion config);
int validaTiro(tablero *tab, const cordenada cord, const configuracion config);
void llenaTiradas(tablero *jugador, tablero *rival, casilla *cas);
void mostrarTablero(const tablero tab);

#ifdef __cplusplus
}
#endif

#endif /* ESTRUCTURAS_H */

