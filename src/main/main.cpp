#include <iostream>
#include "raylib.h"

class Bird {
public:
    float x, y;
    int speedX;
    int radius;

    void draw() {
        DrawCircle(x, y, radius, WHITE);
    }
    
    void update() {
        if (IsKeyDown(KEY_LEFT)) {
            x -= speedX;
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            x += speedX;
        }
        if (x - radius <= 0) {
            x = radius;
        }
        else if (x + radius >= GetScreenWidth()) {
            x = GetScreenWidth() - radius;
        }
    }
};

Bird bird;

int main()
{
    
    const int screenWidth = 1920;
    const int screenHeight = 975;

    bird.x = screenWidth / 2;
    bird.y = 900;
    bird.speedX = 10;
    bird.radius = 20;
    InitWindow(screenWidth, screenHeight, "Flappy Quiz");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        bird.update();
        ClearBackground(BLACK);
        bird.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}