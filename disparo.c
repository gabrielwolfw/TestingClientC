#include "raylib.h"
#include "stdbool.h" // Libreria para usar booleanos
#include <stdlib.h>
#include <stdio.h>
#include "window.c"

//estructura defina para el disparo

typedef struct{
    Texture2D imagenDisparo;
    int posX;
    int posY;

}Disparo;

void inicialarDisparo(Disparo *disparo){
    disparo->posX = 0;
    disparo->posY = 0;
    disparo->imagenDisparo = LoadTexture("./resources/proyectil.png");    
}

void moverDisparo(Disparo *disparo){
    disparo->posY += 1;
}

void posicionaDisparo(Disparo *disparo, Nave *nave) {
    disparo->posX = nave.posX + nave.imagen.width / 2 - disparo->imagenDisparo.width / 2;
    disparo->posY = nave.posY - nave.imagen.height / 2;
}
