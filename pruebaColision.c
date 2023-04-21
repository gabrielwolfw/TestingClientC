#include "raylib.h"
#include "raymath.h"
#include "stdbool.h"
#include <stdlib.h>
#include <stdio.h>


        
typedef struct{
    Texture2D cangrejo;
    Vector2 position;
    bool activo;
    int alto;
    int ancho;
    float speedInvasor;

}Invasor;




int main()
{
    // Initialize the game window and other settings
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Space Shooter");

    // Load the spaceship and bullet images
    Texture2D spaceship = LoadTexture("./recursos/nave.png");
    Texture2D bullet = LoadTexture("./recursos/proyectil.png");
    //Texture2D invasor = LoadTexture("./recursos/cangrejo.png");


    //Invasor: definitivo
    const int MAX_INVASORES = 5;
    Invasor invasores[MAX_INVASORES];
    int invasoresEliminados = 0;

    //Inicializa los invasores
    for (int i = 0; i < MAX_INVASORES; i++) {
    invasores[i].cangrejo = LoadTexture("./recursos/cangrejo.png");
    invasores[i].position = (Vector2){ 50 + i * 100, 20 };
    invasores[i].activo = true;
    invasores[i].ancho = invasores[i].cangrejo.width;
    invasores[i].alto = invasores[i].cangrejo.height;
    invasores[i].speedInvasor = 100;
    }
    



    // Set the starting position of the spaceship
    Vector2 spaceshipPosition = {screenWidth / 2 - spaceship.width / 2, screenHeight - spaceship.height - 20};

    // Set the speed of the spaceship and bullet
    const float spaceshipSpeed = 500;
    const float bulletSpeed = 1000;

    // Set the starting position and velocity of the bullet
    Vector2 bulletPosition = {0, 0};
    Vector2 bulletVelocity = {0, -bulletSpeed};

    // Set the status of the bullet (active or inactive)
    bool bulletActive = false;
    bool invaderDirectionRight = true;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Move the spaceship left or right with arrow keys
        if (IsKeyDown(KEY_LEFT)) spaceshipPosition.x -= spaceshipSpeed * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) spaceshipPosition.x += spaceshipSpeed * GetFrameTime();

        // Keep the spaceship inside the screen boundaries
        if (spaceshipPosition.x <= 0) spaceshipPosition.x = 0;
        if (spaceshipPosition.x >= screenWidth - spaceship.width) spaceshipPosition.x = screenWidth - spaceship.width;

        // Shoot a bullet with space key
        if (IsKeyPressed(KEY_SPACE))
        {
            bulletActive = true;
            bulletPosition.x = spaceshipPosition.x + spaceship.width / 2 - bullet.width / 2;
            bulletPosition.y = spaceshipPosition.y - bullet.height;
        }

        // Update the position of the bullet if it's active
        if (bulletActive)
        {
            bulletPosition.x += bulletVelocity.x * GetFrameTime();
            bulletPosition.y += bulletVelocity.y * GetFrameTime();

            // Deactivate the bullet if it goes off the screen
            if (bulletPosition.y + bullet.height < 0) bulletActive = false;
        }
        
        //Barreras y movimiento de los invasores
        for (int i = 0; i < MAX_INVASORES; i++) {
            if (invasores[i].activo) {
                if (invaderDirectionRight) {
                    invasores[i].position.x += invasores[i].speedInvasor * GetFrameTime();
                    if (invasores[i].position.x + invasores[i].ancho >= screenWidth) {
                        invaderDirectionRight = false;
                        for (int j = 0; j < MAX_INVASORES; j++) {
                            invasores[j].position.y += invasores[j].alto;
                            }
                        }
                } else {
                invasores[i].position.x -= invasores[i].speedInvasor * GetFrameTime();
                if (invasores[i].position.x <= 0) {
                    invaderDirectionRight = true;
                    for (int j = 0; j < MAX_INVASORES; j++) {
                        invasores[j].position.y += invasores[j].alto;
                    }
                }
            }
        }
    }

        

        //Colisiones de los invasores
        // Chequear colisiones de disparos con invasores
        
        if (bulletActive) {
            for (int j = 0; j < MAX_INVASORES; j++) {
                if (invasores[j].activo) {
                    // Chequear si el disparo colisiona con el invasor
                    if (CheckCollisionRecs((Rectangle){bulletPosition.x, bulletPosition.y, bullet.width, bullet.height},
                                    (Rectangle){invasores[j].position.x, invasores[j].position.y, invasores[j].ancho, invasores[j].alto})) {
                                    // Desactivar el disparo y el invasor impactado
                                    bulletActive = false;
                                    invasores[j].activo = false;
                                    }
                                }
                            }
                        }
        // Eliminar los invasores impactados
        for (int j = 0; j < MAX_INVASORES; j++) {
            if (!invasores[j].activo) {
                invasoresEliminados++;
            }
        }


        // Draw the game objects
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(spaceship, spaceshipPosition.x, spaceshipPosition.y, WHITE);

        //dibujar al invasor solo si no ha sido eliminado
        // Dibuja los invasores solo si no han sido eliminados

        for (int i = 0; i < MAX_INVASORES; i++) {
            if (invasores[i].activo) {
                DrawTexture(invasores[i].cangrejo, invasores[i].position.x, invasores[i].position.y, WHITE);
                }
            }

        if (bulletActive) DrawTexture(bullet, bulletPosition.x, bulletPosition.y, WHITE);
        EndDrawing();
    }

    // Unload the game objects
    UnloadTexture(spaceship);
    UnloadTexture(bullet);

    // Close the game window
    CloseWindow();

    return 0;
}
