#include "raylib.h"
#include "stdbool.h" // Libreria para usar booleanos
#include <stdlib.h>
#include <stdio.h>


typedef struct {
    int posX;           // posición x del invasor en la pantalla
    int posY;           // posición y del invasor en la pantalla
    int anchoPantalla;  // ancho de la pantalla
    int vida;           // vida del invasor
    Texture2D imagen1;  // imagen del invasor 1
    Texture2D imagen2;  // imagen del invasor 2
} Invasor;

void inicializarInvasor(Invasor *invasor, int anchoPantalla) {
    invasor->posX = 0;
    invasor->posY = 0;
    invasor->anchoPantalla = anchoPantalla;
    invasor->vida = 50;
    invasor->imagen1 = LoadTexture("./recursos/calamar.png");
    invasor->imagen2 = LoadTexture("./recursos/explosion.png");
}

void moverInvasor(Invasor *invasor, bool direccion) {
    if (direccion) {
        invasor->posX++;
    } else {
        invasor->posX--;
    }
}

void dibujarInvasor(Invasor *invasor) {
    Vector2 posicion = { invasor->posX, invasor->posY };
    if (invasor->vida > 25) {
        DrawTexture(invasor->imagen1, posicion.x, posicion.y, WHITE);
    } else {
        DrawTexture(invasor->imagen2, posicion.x, posicion.y, WHITE);
    }
}

