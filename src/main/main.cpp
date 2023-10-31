#include <vector>
#include "raylib.h"

const int screenWidth = 1920;
const int screenHeight = 975;
const int maxRaindrops = 100;
bool pause = false;

class Raindrop {
public:
    Vector2 position;
    Color color;
    float speed;

    Rectangle getCollisionRectangle() {
        return { position.x, position.y, 1, 1 };
    }
};

std::vector<Raindrop> raindrops;
Raindrop raindrop;

class Bird : public Raindrop {
public:
    float x;
    float y;
    int speedX;
    float radius;

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
    Rectangle getBirdCollisionRectangle() {
        return { x - radius, y - radius, radius * 2, radius * 2 };
    }
};

Bird bird;

bool checkCollisionBirdRain(Bird& bird, Raindrop& raindrop) {
    return CheckCollisionRecs(bird.getBirdCollisionRectangle(), raindrop.getCollisionRectangle());
}

int main() {
    bird.x = screenWidth / 2;
    bird.y = screenHeight - 75;
    bird.speedX = 10;
    bird.radius = 20;

    InitWindow(screenWidth, screenHeight, "Flappy Quiz");
    SetTargetFPS(60);
    

    for (int i = 0; i < maxRaindrops; i++) {
        raindrop.position.x = GetRandomValue(0, screenWidth);
        raindrop.position.y = GetRandomValue(0, screenHeight);
        raindrop.color = YELLOW;
        raindrop.speed = GetRandomValue(40, 42) * 0.1;
        raindrops.push_back(raindrop);
    }

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(SKYBLUE);

        DrawFPS(15, 15);

        bird.update();

        if (!pause) {
            for (size_t i = 0; i < raindrops.size(); i++) {
                raindrops[i].position.y += raindrops[i].speed;

                if (raindrops[i].position.y > screenHeight) {
                    raindrops[i].position.y = 0;
                    raindrops[i].position.x = GetRandomValue(0, screenWidth);
                }

                if (checkCollisionBirdRain(bird, raindrops[i])) {
                    pause = true;
                    raindrops[i].position.y = 0;
                    raindrops[i].position.x = GetRandomValue(0, screenWidth);
                }
                DrawCircleV(raindrops[i].position, 10, raindrops[i].color);
            }
        }
        if (pause) {
            DrawText("TEST YOUR KNOWLEDGE!", screenWidth / 2 - 650, screenHeight - 620 , 100, BLACK);
            DrawText("ANSWER A QUESTION TO SAVE YOURSELF!", screenWidth / 2 - 820 , screenHeight - 470, 75, BLACK);
			DrawText("THE QUESTION WILL APPEAR ON THE CONSOLE.", screenWidth / 2 - 640, screenHeight - 350, 50, BLACK);
        }
        else {
            bird.draw();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}