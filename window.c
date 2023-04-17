#include "raylib.h"
#include "stdbool.h" // Libreria para usar booleanos
#include <stdlib.h>
#include <stdio.h>
#include "invasor.c"

#define MAX_PROYECTILES 100


//----------------------------
// Definicion de estructuras
//---------------------------

//Estructura del proyectil

typedef struct Proyectil {
    Vector2 position;
    Vector2 speed;
    bool active;
} Proyectil;


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


    // Inicializacion de la ventana y OpenGL , se de definen el alto y ancho de la ventana
    const int screenWidth = 630;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Space Invaders Jugador");
    SetTargetFPS(60);
    Texture2D gameBack = LoadTexture("./recursos/fondo1.png");
    Texture2D nave = LoadTexture("./recursos/nave.png");
    Texture2D proyectil = LoadTexture("resources/proyectil.png");

    // Crear array de proyectiles
    Proyectil proyectiles[MAX_PROYECTILES] = { 0 };
    bool disparando = false;


    //Inicializar el invasor ovni
    Invasor invasor;
    inicializarInvasor(&invasor, screenWidth);


     // Inicializar la posición de la nave
    float naveX = screenWidth/2 -nave.width;
    float naveY = (screenHeight-20) - nave.height;


     //Para evitar que la nave salga de la pantalla se establecen los limites de ella
    const float limitLeft = 0;
    const float limitRight = screenWidth - nave.width;
     
     
    //Bucle principal del juego
    while (!WindowShouldClose()) {

        //Movimiento de la nave con las teclas derecha e izquierda

        if (IsKeyDown(KEY_RIGHT))
        {
            naveX = (naveX + 5 > limitRight) ? limitRight : naveX + 5;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            naveX = (naveX - 5 < limitLeft) ? limitLeft : naveX - 5;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            naveY += 0;
        }
        else if (IsKeyDown(KEY_UP))
        {
            naveY -= 0;
        }

        // Comprobar si se ha presionado la tecla espacio
        if (IsKeyPressed(KEY_SPACE) &&! disparando) {
            // Buscar un proyectil disponible en el array
            disparando = true;
            for (int i = 0; i < MAX_PROYECTILES; i++) {
                if (!proyectiles[i].active) {
                    // Establecer la posición y velocidad del proyectil
                    proyectiles[i].position = (Vector2) { naveX + nave.width/2 - proyectil.width/2, naveY };
                    proyectiles[i].speed = (Vector2) { 0, -10 };
                    proyectiles[i].active = true;
                    break;
                }
            }
        }


        // Actualizar la posición de los proyectiles activos
        for (int i = 0; i < MAX_PROYECTILES; i++) {
            if (proyectiles[i].active) {
                proyectiles[i].position.x += proyectiles[i].speed.x;
                proyectiles[i].position.y += proyectiles[i].speed.y;
                // Si el proyectil sale de la pantalla, desactivarlo
                if (proyectiles[i].position.y < 0) proyectiles[i].active = false;
            }
        }

        
        actualizarInvasor(&invasor, true);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(gameBack, 0, 0, WHITE);
        DrawTexture(nave, naveX, naveY, WHITE);
        dibujarInvasor(&invasor);

        // Dibujar los proyectiles activos
        for (int i = 0; i < MAX_PROYECTILES; i++) {
    if (proyectiles[i].active) {
        DrawTexture(proyectil, proyectiles[i].position.x, proyectiles[i].position.y, WHITE);
    }
}

        
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