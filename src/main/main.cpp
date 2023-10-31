#include <vector>
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

const int maxRaindrops = 60;

class Raindrop {
public:
    Vector2 position;
    Color color;
    float speed;
};

Bird bird;

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 975;

    bird.x = screenWidth / 2;
    bird.y = screenHeight - 75;
    bird.speedX = 10;
    bird.radius = 20;

    InitWindow(screenWidth, screenHeight, "Flappy Quiz");
    SetTargetFPS(60);

    std::vector<Raindrop> raindrops;

    for (int i = 0; i < maxRaindrops; i++) {
        Raindrop raindrop;
        raindrop.position.x = GetRandomValue(0, screenWidth);
        raindrop.position.y = GetRandomValue(0, screenHeight);
        raindrop.color = YELLOW;
        raindrop.speed = GetRandomValue(12, 15) * 0.1;
        raindrops.push_back(raindrop);
    }

    while (!WindowShouldClose()) {

        bird.update();

        BeginDrawing();
        ClearBackground(BLACK);

        for (size_t i = 0; i < raindrops.size(); i++) {
            raindrops[i].position.y += raindrops[i].speed;

            if (raindrops[i].position.y > screenHeight) {
                raindrops[i].position.y = 0;
                raindrops[i].position.x = GetRandomValue(0, screenWidth);
            }

            DrawCircleV(raindrops[i].position, 5, raindrops[i].color);
        }

        bird.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}