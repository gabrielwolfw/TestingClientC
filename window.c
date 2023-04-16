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
        button->color = WHITE;
    }
    return button->pressed;
}



//Se dibuja el button del espectador
void draw_espectadorButton(Button* button) {
    DrawRectangleRec(button->rect, button->color);
    DrawText("MIRAR", button->rect.x + button->rect.width/2 - MeasureText("PRESS", 25)/2, 
             button->rect.y + button->rect.height - 38, 26, BLACK);
}

//Se dibuja el button del jugador
void draw_jugadorButton(Button* button) {
    DrawRectangleRec(button->rect, button->color);
    DrawText("JUGAR", button->rect.x + button->rect.width/2 - MeasureText("PRESS", 25)/2, 
             button->rect.y + button->rect.height - 38, 26, BLACK);
}


//Donde todas las acciones del jugador van a ser vistas, no se puede modificar nada
void ventanaEspectador() {
    InitWindow(640, 480, "Space Invaders Espectador");
    SetTargetFPS(60);
    Texture2D gameBack = LoadTexture("./recursos/fondo1.png");

    
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
    Texture2D gameBack = LoadTexture("./recursos/fondo1.png");

    
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
    //Button espectador
    Rectangle buttonEspecRect = { 170, 380, 100, 50 };   //100 y 50 son el ancho y alto del boton, 170 y 380 son las coordenadas del boton
    Color buttonEspecColor = GRAY;

    //Button jugador
    Rectangle buttonJugRect = {410,380,100,50};
    Color buttonJugColor = GRAY;

    //Define los botones en la ventana principal
    Button buttonEspectador;
    Button buttonJugar;

    //Inicializa buttones
    init_button(&buttonEspectador, buttonEspecRect, buttonEspecColor);
    init_button(&buttonJugar, buttonJugRect, buttonJugColor);


    

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

        draw_espectadorButton(&buttonEspectador); // Dibujar el botón

        
        if (is_button_pressed(&buttonEspectador)) {
            printf("Ha sido presionado el buttonEspectador");
            ventanaEspectador(); // Abrir la nueva ventana
            init_button(&buttonEspectador, (Rectangle){screenWidth/2 - 100, screenHeight/2 - 25, 200, 50}, GRAY); // Reinicializar el botón
        }
        
        draw_jugadorButton(&buttonJugar);
        if(is_button_pressed(&buttonJugar)){
            printf("Ha sido presionado el buttonJugador");
            ventanaJugador(); // Abrir la nueva ventana
            init_button(&buttonJugar, (Rectangle){screenWidth/2 - 100, screenHeight/2 - 25, 200, 50}, GRAY);
        }
        

            //DrawText("BIENVENIDO A SPACE INVADERS", 190, 200, 20, BLACK);
            // Dibujar el fondo
            

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Cerrar ventana y contexto OpenGL

    return 0;
}