#include "raylib.h"
#include "stdbool.h"
#include <stdlib.h>
#include <stdio.h>
#include "raymath.h"
#include "time.h"

typedef struct  {
    int puntos;
    float posX;           // position x of the ovni on the screen
    float posY; 
    Texture2D ovniImage;             // ovni image
    bool mostrar;
    int screenWidth;      // screen width
    int screenHeight; 
    float speedX;

} Ovni;



void inicializarOvni(Ovni *ovni, int screenWidth, int screenHeight) {
    ovni-> posX = 0;
    ovni-> screenWidth = screenWidth;
    ovni-> screenHeight = screenHeight;
    ovni-> posY = GetRandomValue(10, 250);
    ovni-> ovniImage= LoadTexture("./recursos/ovni.png");
    ovni-> speedX = 2.5;
    ovni-> puntos = GetRandomValue(1, 10);
    ovni-> mostrar = false;
}


//movimiento del ovni sea random en cualquier posicion x y y de la ventana 

void moverOvni(Ovni *ovni) {
    
    if (IsKeyPressed(KEY_O)) {
        
        ovni->mostrar = true; // Mostrar el ovni en la pantalla
        

    }if (ovni->mostrar==true){

        ovni->posX += ovni->speedX;

        ovni->puntos = GetRandomValue(1, 10);
        
    }
}


// Actualizar la posicion del ovni
void actualizarPosicionOvni(Ovni *ovni) {

    //ovni empieza a moverse
    //ovni->posX += ovni->speedX;

     // Verificar si el sprite ha alcanzado el borde derecho de la pantalla
    if (ovni->posX > ovni->screenWidth) {
        UnloadTexture(ovni->ovniImage);}
}


// Dibujar el ovni en la pantalla

void DibujarOvni(Ovni *ovni){
    if (ovni->mostrar) {
        DrawTexture(ovni->ovniImage, ovni->posX, ovni->posY, WHITE);
    }   
}

 

