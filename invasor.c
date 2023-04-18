#include "raylib.h"
#include "stdbool.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    float posX;             // position x of the invader on the screen
    float posY;             // position y of the invader on the screen
    int anchoPantalla;      // screen width
    int alturaPantalla;     // screen height
    int vida;               // invader's life
    Texture2D imagen1;      // invader's image 1
    Texture2D imagen2;      // invader's image 2
    float velocidad;
} Invasor;

void inicializarInvasor(Invasor *invasor, int anchoPantalla) {
    invasor->posX = 50.0f;
    invasor->posY = 50.0f;
    invasor->anchoPantalla = anchoPantalla;
    invasor->vida = 50;
    invasor->imagen1 = LoadTexture("./recursos/calamar.png");
    invasor->imagen2 = LoadTexture("./recursos/explosion.png");
    invasor->velocidad = 1.5f;
}

void moverInvasor(Invasor *invasor, bool direccionDerecha) {
    if (direccionDerecha) {
        invasor->posX += invasor->velocidad;
    } else {
        invasor->posX -= invasor->velocidad;
    }
}

void actualizarPosicion(Invasor *invasor, bool direccionDerecha) {
    // Si el invasor llegó al límite derecho, cambiamos la dirección del movimiento.
    moverInvasor(invasor, direccionDerecha);
    if (invasor->posX >= 400) {
        direccionDerecha = false;
        moverInvasor(invasor, direccionDerecha);
    }
    // Si el invasor llegó al límite izquierdo, cambiamos la dirección del movimiento.
    else if (invasor->posX <= 0) {
        direccionDerecha = true;
        moverInvasor(invasor, direccionDerecha);
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

