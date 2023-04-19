#include "raylib.h"
#include "stdbool.h"
#include <stdlib.h>
#include <stdio.h>
#include "raymath.h"


typedef struct  {
    Vector2 speed;
    int puntos;
    Texture2D ovniImage;      // ovni.png
    float posX;           // position x of the ovni on the screen
    float posY;             // position y of the ovni on the screen
    int anchoPantalla;      // screen width
    int alturaPantalla;     // screen height
    Vector2 posicionOvni;
    bool mostrar;
    int direccion;
} Ovni;


void inicializarOvni(Ovni *ovni, int anchoPantalla, int alturaPantalla) {
    ovni->posX = GetRandomValue(0, anchoPantalla);
    ovni->posY = GetRandomValue(0, alturaPantalla);
    ovni->anchoPantalla = anchoPantalla;
    ovni->alturaPantalla = alturaPantalla;
    ovni->puntos = GetRandomValue(1, 10);
    ovni-> ovniImage= LoadTexture("./recursos/ovni.png");
    ovni->speed= (Vector2){ 0.1, 0.1};
    ovni->posicionOvni.x = ovni->posX;
    ovni->posicionOvni.y = ovni->posY;
    ovni->mostrar = false;
    
}


//movimiento del ovni sea random en cualquier posicion x y y de la ventana 

void moverOvni(Ovni* ovni) {
    if (IsKeyPressed(KEY_O)) {
        ovni->mostrar = true; // Mostrar el ovni en la pantalla

    }if (ovni->mostrar==true){

     ovni->posicionOvni = (Vector2){ (float)GetRandomValue(0, ovni->anchoPantalla - ovni->ovniImage.width),
            /*(float)GetRandomValue(0, ovni->alturaPantalla - ovni->ovniImage.height)*/};
        ovni->speed = (Vector2){ (float)GetRandomValue(-0.1,0.1), (float)GetRandomValue(-0.1,0.1) };
        ovni->puntos = GetRandomValue(1, 10);
        
    }
}


// Actualizar la posicion del ovni

// Actualizar la posicion del ovni
void actualizarPosicionOvni(Ovni* ovni) {

    printf("prueba");
    ovni->posicionOvni.x += ovni->speed.x;
    ovni->posicionOvni.y += ovni->speed.y;

    if (ovni->posicionOvni.y > ovni->alturaPantalla - ovni->ovniImage.height) {
        ovni->posicionOvni.y = ovni->alturaPantalla - ovni->ovniImage.height;
        ovni->speed.y *= -1;
    }
    else if (ovni->posicionOvni.y < 0) {
        ovni->posicionOvni.y = 0;
        ovni->speed.y *= -1;
    }
}


// Dibujar el ovni en la pantalla

void DibujarOvni(Ovni *ovni){
    if (ovni->mostrar) {
        DrawTexture(ovni->ovniImage, ovni->posicionOvni.x, ovni->posicionOvni.y, WHITE);
    }
}

 

