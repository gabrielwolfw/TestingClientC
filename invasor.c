#include "raylib.h"
#include "stdbool.h" // Libreria para usar booleanos
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    float posX;           // posición x del invasor en la pantalla
    float posY;           // posición y del invasor en la pantalla
    int anchoPantalla;  // ancho de la pantalla
    int alturaPantalla; // altura de la pantalla
    int vida;           // vida del invasor
    Texture2D imagen1;  // imagen del invasor 1
    Texture2D imagen2;  // imagen del invasor 2
    float velocidad;
} Invasor;

void inicializarInvasor(Invasor *invasor, int anchoPantalla) {
    invasor->posX = 50;
    invasor->posY = 50;
    invasor->anchoPantalla = anchoPantalla;
    invasor->vida = 50;
    invasor->imagen1 = LoadTexture("./recursos/calamar.png");
    invasor->imagen2 = LoadTexture("./recursos/explosion.png");
    invasor->velocidad = 1;
}


//Movilidad del invasor de izquierda a derecha en la pantalla
void moverInvasor(Invasor *invasor, bool direccion) {
    if (direccion) {
        invasor->posX += 0.5;
    } else {
        invasor->posX -= 2;
    }
}
//Actualiza la movilidad del invasor
void actualizarPosicion(Invasor *invasor, bool direccion){
    moverInvasor(invasor, direccion);
    if(invasor->posX >= 440 - invasor->imagen1.width || invasor->posX <= 0){
        moverInvasor(invasor, !direccion);
        invasor->posY += invasor->velocidad;
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

