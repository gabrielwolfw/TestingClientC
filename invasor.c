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
    Vector2 posicionInvasor;
} Invasor;

void inicializarInvasor(Invasor *invasor, int anchoPantalla) {
    invasor->posX = 50;
    invasor->posY = 20;
    invasor->anchoPantalla = anchoPantalla;
    invasor->vida = 50;
    invasor->imagen1 = LoadTexture("./recursos/calamar.png");
    invasor->imagen2 = LoadTexture("./recursos/explosion.png");
    invasor->velocidad = 2;
    invasor->posicionInvasor.x = invasor->posX;
    invasor->posicionInvasor.y = invasor->posY;
    
}

void moverInvasor(Invasor *invasor, bool direccionDerecha) {
    if(direccionDerecha){
            invasor->posicionInvasor.x += invasor->velocidad;
            invasor->posicionInvasor.y += 0.1;
        }else{
            invasor->posicionInvasor.x -= invasor->velocidad;
            invasor->posicionInvasor.y += 0.1;
        }
}

void actualizarPosicion(Invasor *invasor, bool direccionDerecha) {
    moverInvasor(invasor,direccionDerecha);
    if(invasor->posicionInvasor.x >= 300){
        direccionDerecha = false;
    } else if(invasor->posicionInvasor.x <= 0){
        direccionDerecha = true;
    }
}

void dibujarInvasor(Invasor *invasor) {
    if (invasor->vida > 25) {
        DrawTexture(invasor->imagen1, invasor->posicionInvasor.x, invasor->posicionInvasor.y, WHITE);
    } else {
        DrawTexture(invasor->imagen2, invasor->posicionInvasor.x, invasor->posicionInvasor.y, WHITE);
    }
}

