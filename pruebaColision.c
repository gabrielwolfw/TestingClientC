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

}InvasorCangrejo;


typedef struct{
    Texture2D calamar;
    Vector2 positionCalamar;
    bool activoCala;
    int altoCalamar;
    int anchoCalamar;
    float speedCalamar;
}InvasorCalamar;




int main()
{
    // Initialize the game window and other settings
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Space Shooter");

    // Load the spaceship and bullet images
    Texture2D spaceship = LoadTexture("./recursos/nave.png");
    Texture2D bullet = LoadTexture("./recursos/proyectil.png");
    //Texture2D InvasorCangrejo = LoadTexture("./recursos/cangrejo.png");


    //InvasorCangrejo: definitivo, cangrejo
    const int MAX_INVASORES = 5;
    InvasorCangrejo invasoresCangrejos[MAX_INVASORES];
    int invasoresEliminados = 0;
    //Inicializa los invasoresCangrejos
    for (int i = 0; i < MAX_INVASORES; i++) {
    invasoresCangrejos[i].cangrejo = LoadTexture("./recursos/cangrejo.png");
    invasoresCangrejos[i].position = (Vector2){ 50 + i * 100, 20 };
    invasoresCangrejos[i].activo = true;
    invasoresCangrejos[i].ancho = invasoresCangrejos[i].cangrejo.width;
    invasoresCangrejos[i].alto = invasoresCangrejos[i].cangrejo.height;
    invasoresCangrejos[i].speedInvasor = 100;
    }


    //Invasores Calamar
    const int MAX_CALAMAR = 5;
    InvasorCalamar invasoresCalamar[MAX_CALAMAR];
    int calamaresEliminados = 0;

    //Inicializar Invasores Calamar
    for (int i = 0; i < MAX_CALAMAR; i++) {
    invasoresCalamar[i].calamar = LoadTexture("./recursos/calamar.png");
    invasoresCalamar[i].positionCalamar = (Vector2){ 50 + i * 110, 20 + invasoresCalamar[i].calamar.height + 10};
    invasoresCalamar[i].activoCala = true;
    invasoresCalamar[i].anchoCalamar = invasoresCangrejos[i].cangrejo.width;
    invasoresCalamar[i].altoCalamar = invasoresCangrejos[i].cangrejo.height;
    invasoresCalamar[i].speedCalamar = 100;
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
        
        //Barreras y movimiento de los invasoresCangrejos
        for (int i = 0; i < MAX_INVASORES; i++) {
            if (invasoresCangrejos[i].activo) {
                if (invaderDirectionRight) {
                    invasoresCangrejos[i].position.x += invasoresCangrejos[i].speedInvasor * GetFrameTime();
                    if (invasoresCangrejos[i].position.x + invasoresCangrejos[i].ancho >= screenWidth) {
                        invaderDirectionRight = false;
                        for (int j = 0; j < MAX_INVASORES; j++) {
                            invasoresCangrejos[j].position.y += invasoresCangrejos[j].alto;
                            }
                        }
                } else {
                invasoresCangrejos[i].position.x -= invasoresCangrejos[i].speedInvasor * GetFrameTime();
                if (invasoresCangrejos[i].position.x <= 0) {
                    invaderDirectionRight = true;
                    for (int j = 0; j < MAX_INVASORES; j++) {
                        invasoresCangrejos[j].position.y += invasoresCangrejos[j].alto;
                    }
                }
            }
        }
    }

        

        //Colisiones de los invasoresCangrejos
        // Chequear colisiones de disparos con invasoresCangrejos
        
        if (bulletActive) {
            for (int j = 0; j < MAX_INVASORES; j++) {
                if (invasoresCangrejos[j].activo) {
                    // Chequear si el disparo colisiona con el InvasorCangrejo
                    if (CheckCollisionRecs((Rectangle){bulletPosition.x, bulletPosition.y, bullet.width, bullet.height},
                                    (Rectangle){invasoresCangrejos[j].position.x, invasoresCangrejos[j].position.y, invasoresCangrejos[j].ancho, invasoresCangrejos[j].alto})) {
                                    // Desactivar el disparo y el InvasorCangrejo impactado
                                    bulletActive = false;
                                    invasoresCangrejos[j].activo = false;
                                    }
                                }
                            }
                        }
        // Eliminar los invasoresCangrejos impactados
        for (int j = 0; j < MAX_INVASORES; j++) {
            if (!invasoresCangrejos[j].activo) {
                invasoresEliminados++;
            }
        }




        //Barreras y movimiento de los invasoresCalamar
        for (int i = 0; i < MAX_CALAMAR; i++) {
            if (invasoresCalamar[i].activoCala) {
                if (invaderDirectionRight) {
                    invasoresCalamar[i].positionCalamar.x += invasoresCalamar[i].speedCalamar * GetFrameTime();
                    if (invasoresCalamar[i].positionCalamar.x + invasoresCalamar[i].anchoCalamar >= screenWidth) {
                        invaderDirectionRight = false;
                        for (int j = 0; j < MAX_CALAMAR; j++) {
                            invasoresCalamar[j].positionCalamar.y += invasoresCalamar[j].altoCalamar;
                            }
                        }
                } else {
                invasoresCalamar[i].positionCalamar.x -= invasoresCalamar[i].speedCalamar * GetFrameTime();
                if (invasoresCalamar[i].positionCalamar.x <= 0) {
                    invaderDirectionRight = true;
                    for (int j = 0; j < MAX_CALAMAR; j++) {
                        invasoresCalamar[j].positionCalamar.y += invasoresCalamar[j].altoCalamar;
                    }
                }
            }
        }
    }
        //Deteccion de colisiones con las balas de los calamares
        if (bulletActive) {
            for (int j = 0; j < MAX_CALAMAR; j++) {
                if (invasoresCalamar[j].activoCala) {
                    // Chequear si el disparo colisiona con el InvasorCangrejo
                    if (CheckCollisionRecs((Rectangle){bulletPosition.x, bulletPosition.y, bullet.width, bullet.height},
                                    (Rectangle){invasoresCalamar[j].positionCalamar.x, invasoresCalamar[j].positionCalamar.y, invasoresCalamar[j].anchoCalamar, invasoresCalamar[j].altoCalamar})) {
                                    // Desactivar el disparo y el InvasorCangrejo impactado
                                    bulletActive = false;
                                    invasoresCalamar[j].activoCala = false;
                                    }
                                }
                            }
                        }
        // Eliminar los invasoresCalamar impactados
        for (int j = 0; j < MAX_CALAMAR; j++) {
            if (!invasoresCalamar[j].activoCala) {
                calamaresEliminados++;
            }
        }

        // Draw the game objects
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(spaceship, spaceshipPosition.x, spaceshipPosition.y, WHITE);

        //dibujar al InvasorCangrejo solo si no ha sido eliminado
        // Dibuja los invasoresCangrejos solo si no han sido eliminados

        for (int i = 0; i < MAX_INVASORES; i++) {
            if (invasoresCangrejos[i].activo) {
                DrawTexture(invasoresCangrejos[i].cangrejo, invasoresCangrejos[i].position.x, invasoresCangrejos[i].position.y, WHITE);
                }
            }

        for (int i = 0; i < MAX_CALAMAR; i++) {
            if (invasoresCalamar[i].activoCala) {
                DrawTexture(invasoresCalamar[i].calamar, invasoresCalamar[i].positionCalamar.x, invasoresCalamar[i].positionCalamar.y, WHITE);
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
