#include "raylib.h"
#include "stdbool.h" // Libreria para usar booleanos
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Rectangle rect;
    Color color;
    bool pressed;
} Button;



void init_button(Button* button, Rectangle rect, Color color) {
    button->rect = rect;
    button->color = color;
    button->pressed = false;
}






bool is_button_pressed(Button* button) {
    if (CheckCollisionPointRec(GetMousePosition(), button->rect)) {
        button->color = LIGHTGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            button->pressed = true;
        }
    } else {
        button->color = GRAY;
    }
    return button->pressed;
}




void draw_button(Button* button) {
    DrawRectangleRec(button->rect, button->color);
    DrawText("PRESS", button->rect.x + button->rect.width/2 - MeasureText("PRESS", 20)/2, 
             button->rect.y + button->rect.height/2 - 10, 20, BLACK);
}



//Donde todas las acciones del jugador van a ser vistas, no se puede modificar nada
void ventanaEspectador() {
    InitWindow(640, 480, "Space Invaders Espectador");
    SetTargetFPS(60);
    Texture2D gameBack = LoadTexture("./recursos/fondo.png");

    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(gameBack, 0, 0, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}

//Donde todas las acciones del jugador van a ocurrir
void ventanaJugador() {
    InitWindow(640, 480, "Space Invaders Jugador");
    SetTargetFPS(60);
    Texture2D gameBack = LoadTexture("./recursos/fondo.png");

    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(gameBack, 0, 0, WHITE);
        EndDrawing();
    } 
    CloseWindow();
}





int main(void){ 

    // Inicializacion de la ventana y OpenGL , se de definen el alto y ancho de la ventana
    const int screenWidth = 650;
    const int screenHeight = 550;


    InitWindow(screenWidth, screenHeight, "Game Window");
    Texture2D background = LoadTexture("./recursos/fondo.png");

    //CREANDO UN BOTON
    Rectangle buttonRect = { 100, 280, 100, 50 };   //100 y 50 son el ancho y alto del boton
    Color buttonColor = GRAY;

    Button button;
    init_button(&button, buttonRect, buttonColor);


    

    // Configurar nuestro juego para que se ejecute a 60 fotogramas por segundo
    SetTargetFPS(60);              


    // Buble principal del juego. En este punto se ejecuta todo el juego
    while (!WindowShouldClose())    // Detecta botón de cierre de ventana o tecla ESC
    {
        // Actualizar variables 

        // Dibujar 

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(background, 0, 0, WHITE);

        draw_button(&button); // Dibujar el botón
        if (is_button_pressed(&button)) {
            printf("Ha sido presionado");
            ventanaEspectador(); // Abrir la nueva ventana
            init_button(&button, (Rectangle){screenWidth/2 - 100, screenHeight/2 - 25, 200, 50}, GRAY); // Reinicializar el botón
        }

            //DrawText("BIENVENIDO A SPACE INVADERS", 190, 200, 20, BLACK);
            // Dibujar el fondo
            

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Cerrar ventana y contexto OpenGL

    return 0;
}