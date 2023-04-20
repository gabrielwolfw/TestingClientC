#include "raylib.h"
#include "stdbool.h" // Libreria para usar booleanos
#include <stdlib.h>
#include <stdio.h>

typedef struct Sprite {
    float pos_x;
    float pos_y;
    float speed_x;
    Texture2D texture;
} Sprite;


int main()
{
    // Initialize the game window and other settings
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Space Shooter");


    // Load the spaceship and bullet images
    Texture2D spaceship = LoadTexture("./recursos/nave.png");
    Texture2D bullet = LoadTexture("./recursos/proyectil.png");
     // Cargar textura del sprite
    Texture2D spriteTexture = LoadTexture("./recursos/ovni.png");
    // Crear instancia del sprite
    Sprite sprite = {
        .pos_x = 0,
        .pos_y = GetRandomValue(10,250),
        .speed_x = 0.15,
        .texture = spriteTexture
    };


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

        // Actualizar posición del sprite
             sprite.pos_x += sprite.speed_x;

        // Verificar si el sprite ha alcanzado el borde derecho de la pantalla
        if (sprite.pos_x > screenWidth) {
            UnloadTexture(sprite.texture);
        }

        // Draw the game objects
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(spaceship, spaceshipPosition.x, spaceshipPosition.y, WHITE);
        if (bulletActive) DrawTexture(bullet, bulletPosition.x, bulletPosition.y, WHITE);

        DrawTexture(sprite.texture, sprite.pos_x, sprite.pos_y, WHITE);
        EndDrawing();
    }

    // Unload the game objects
    UnloadTexture(spaceship);
    UnloadTexture(bullet);

    // Close the game window
    CloseWindow();

    return 0;
}




