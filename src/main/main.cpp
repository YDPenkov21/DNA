#include <vector>
#include "raylib.h"
#include "questionBank.h"

Color sky_c = Color { 85, 111, 122, 255 };
Color cloud_c = Color { 94, 94, 94, 255};
Color raindrop_c = Color { 177, 230, 54, 255 };

const int screenWidth = 1920;
const int screenHeight = 975;
const int maxRaindrops = 75;
const int maxClouds = 5;
bool pause = false;

class Cloud {
public:
    Vector2 position;
    Vector2 size;
    Color color;
    float speed;
};

std::vector<Cloud> clouds;
Cloud cloud;

class Raindrop {
public:
    Vector2 position;
    Color color;
    float speed;

    const Rectangle getCollisionRectangle() const {
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

    const void draw() const {
        DrawCircle(x, y, radius, WHITE);
    }

    const void update() {
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
    const Rectangle getBirdCollisionRectangle() const {
        return { x - radius, y - radius, radius * 2, radius * 2 };
    }
};

const bool checkCollisionBirdRain(Bird& bird, Raindrop& raindrop) {
    return CheckCollisionRecs(bird.getBirdCollisionRectangle(), raindrop.getCollisionRectangle());
}

Bird bird;

int main() {
    bird.x = screenWidth / 2;
    bird.y = screenHeight - 75;
    bird.speedX = 10;
    bird.radius = 25;

    InitWindow(screenWidth, screenHeight, "Flappy Quiz");
    SetTargetFPS(60);

	for (size_t i = 0; i < maxClouds; i++) {
		cloud.position.x = GetRandomValue(0, screenWidth);
		cloud.position.y = GetRandomValue(0, screenHeight);
		cloud.color = cloud_c;
		cloud.speed = GetRandomValue(40, 50) * 0.1;
		clouds.push_back(cloud);
	}

    for (size_t i = 0; i < maxRaindrops; i++) {
        raindrop.position.x = GetRandomValue(0, screenWidth);
        raindrop.position.y = GetRandomValue(0, screenHeight);
        raindrop.color = raindrop_c;
        raindrop.speed = GetRandomValue(50, 55) * 0.1;
        raindrops.push_back(raindrop);
    }

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(sky_c);

        DrawFPS(15, 20);

        bird.update();

        if (!pause) {
            float currentTime = GetTime();
            for (size_t i = 0; i < clouds.size(); i++) {
                clouds[i].position.y += clouds[i].speed;

                if (clouds[i].position.y > screenHeight) {
                    clouds[i].position.y = 0;
                    clouds[i].position.x = GetRandomValue(0, screenWidth);
                    clouds[i].size.y = GetRandomValue(200, 250);
                    clouds[i].size.x = GetRandomValue(220, 270);
                }
                DrawRectangleV(clouds[i].position, clouds[i].size, cloud_c);
            }

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
            DrawText(TextFormat("%.2f", currentTime), 30, 45, 100, YELLOW);
        }
        if (pause) {
            DrawText("TEST YOUR KNOWLEDGE!", screenWidth / 2 - 650, screenHeight - 620, 100, BLACK);
            DrawText("ANSWER A QUESTION TO SAVE YOURSELF!", screenWidth / 2 - 820, screenHeight - 470, 75, BLACK);
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