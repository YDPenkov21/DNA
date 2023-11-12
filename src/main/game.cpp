// Include the needed header files.
#include <iostream>
#include <iomanip>
#include <vector>
#include "raylib.h"
#include "game.h"
#include "questionBank.h"
#include "rules.h"

// Declare the images and the textures.
Image image1; 
Texture2D flappy1;
Image image2;
Texture2D flappy2;
Image image3;
Texture2D raindropTexture;
Image image4;
Texture2D cloudTexture;

// Declare the colors.
Color sky_c = Color { 85, 111, 122, 255 };
Color cloud_c = Color { 94, 94, 94, 255 };
Color raindrop_c = Color { 177, 230, 54, 255 };

// Declare the needed global variables.
const int screenWidth = 1920;
const int screenHeight = 975;
const int maxRaindrops = 40;
const int maxClouds = 5;
bool mainMenu = false;
bool pause = false;
bool pauseMenu = false;
float currentTime = 0.0f;
float elapsedTime = currentTime;
int answeredQuestions = 0;
int wing = 110;

// Initialize the cloud class.
class Cloud {
public:
    // Initialize the needed attributes.
    Vector2 position;
    Vector2 size;
    Color color;
    float speed;
};

// Instantiate the clouds container and the cloud object.
std::vector<Cloud> clouds;
Cloud cloud;

// Initialize the raindrop class.
class Raindrop {
public:
    // Initialize the needed attributes.
    Vector2 position;
    Color color;
    float radius;
    float speed;
};

// Instantiate the raindrops container and the raindrop object.
std::vector<Raindrop> raindrops;
Raindrop raindrop;

// Initialize the bird class, which inherits from the raindrop class.
class Bird : public Raindrop {
public:
    // Initialize the needed attributes.
    Rectangle head;
    Rectangle wings;
    Rectangle tail;
    float x;
    float y;
    int speedX;
    float radius;
    float wingLength;

    // Declare the bird update method.
    const void update() {
        if (IsKeyDown(KEY_LEFT)) {
            // Change coordinates.
            x -= speedX;
            head.x -= speedX;
            wings.x -= speedX;
            tail.x -= speedX;
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            // Change coordinates.
            x += speedX;
            head.x += speedX;
            wings.x += speedX;
            tail.x += speedX;
        }

        // Check border collision.
        if (x - wing <= 0) {
            x = wing;
        }

        else if (x >= screenWidth) {
            x = screenWidth;
        }
    }

    // Declare the bird draw method.
    const void draw() const {
        // Draw the avatar.
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)) {
            DrawTextureEx(flappy2, Vector2{ x, y }, 0, -0.2f, WHITE);
        }
        else {
            DrawTextureEx(flappy1, Vector2{ x, y }, 0, -0.2f, WHITE);
        }
    }
};

//  Declare the collision functions between the bird and the raindrops.
bool checkCollisionHead(Bird& bird, Raindrop& raindrop) {
    return CheckCollisionCircleRec(raindrop.position, raindrop.radius, bird.head);
}
bool checkCollisionWings(Bird& bird, Raindrop& raindrop) {
    return CheckCollisionCircleRec(raindrop.position, raindrop.radius, bird.wings);
}
bool checkCollisionTail(Bird& bird, Raindrop& raindrop) {
    return CheckCollisionCircleRec(raindrop.position, raindrop.radius, bird.tail);
}

// Declare collision check function between mouse cursor and the rectanglular buttons.
bool checkCollisionPointRec(Vector2 point, Rectangle rec) {
    return (point.x >= rec.x && point.x <= (rec.x + rec.width) &&
        point.y >= rec.y && point.y <= (rec.y + rec.height));
}

// Instantiate the bird object.
Bird bird;

// Declare the game function.
void game() {

    // Initalize the button's sizes and postions.
    Rectangle playButton = { (screenWidth / 2) - 120, (screenHeight / 2) + 100, 250, 100 };
    Rectangle rulesButton = { (screenWidth / 2) - 120, (screenHeight / 2) + 250, 250, 100 };
    Rectangle returnButton = { (screenWidth / 2) - 120, (screenHeight / 2) + 250, 250, 100 };

    // Assign the bird's body parts coordiates, speed, radius and wing span.
    bird.x = screenWidth / 2.0;
    bird.y = screenHeight - 40;
    bird.head = { (bird.x) - 40, (bird.y) - 90, 20, 10 };
    bird.wings = { (bird.x) - 90, (bird.y) - 55, 100, 5 };
    bird.tail = { (bird.x) - 20, bird.y, 5, 10 };
    bird.speedX = 10;
    bird.radius = 50;
    bird.wingLength = 15;

    // Assign the radius of the raindrops.
    raindrop.radius = 1;

    //Intialize the window.
    InitWindow(screenWidth, screenHeight, "Flappy Quiz");

    //Intialize the audio device.
    InitAudioDevice();

    // Load the game music.
    Music music = LoadMusicStream("audio/game_song.mp3");

    // Booleans to check if the music is playing and to display the music icon.
    bool isSoundPlaying = false;
    bool showMusicIcon = false;

    // Start the timer.
    currentTime = GetTime();

    // Load the main images.
    image1 = LoadImage("sprites/flappy_1.png");
    flappy1 = LoadTextureFromImage(image1);
    UnloadImage(image1);
    image2 = LoadImage("sprites/flappy_2.png");
    flappy2 = LoadTextureFromImage(image2);
    UnloadImage(image2);
    image3 = LoadImage("sprites/raindrop.png");
    raindropTexture = LoadTextureFromImage(image3);
    UnloadImage(image3);
    image4 = LoadImage("sprites/cloud.png");
    cloudTexture = LoadTextureFromImage(image4);
    UnloadImage(image4);

    // Load the images and textures of the main menu and rules tab.
    Image background = LoadImage("images/background.png");
    ImageResize(&background, screenWidth, screenHeight);
	Texture2D resizedTexture = LoadTextureFromImage(background);
    UnloadImage(background);

    Image rulesBackground = LoadImage("images/rules_background.png");
    ImageResize(&rulesBackground, screenWidth, screenHeight);
    Texture2D resizedRules = LoadTextureFromImage(rulesBackground);
    UnloadImage(rulesBackground);

    Image logo = LoadImage("images/DNA.png");
    ImageResize(&logo, 200, 150);
    Texture2D resizedLogo = LoadTextureFromImage(logo);
    UnloadImage(logo);

    Image eighthNote = LoadImage("images/eighth_note.png");
    ImageResize(&eighthNote, 50, 50);
    Texture2D resizedNote = LoadTextureFromImage(eighthNote);
    UnloadImage(eighthNote);

    // Set target FPS to 60 frames per second.
    SetTargetFPS(60);

    // Set up cloud mechanism.
    for (size_t i = 0; i < maxClouds; i++) {
        cloud.position.x = GetRandomValue(0, screenWidth);
        cloud.position.y = GetRandomValue(0, screenHeight);
        cloud.color = cloud_c;
        cloud.speed = GetRandomValue(40, 50) * 0.1;
        clouds.push_back(cloud);
    }

    // Set up raindrop mechanism.
    for (size_t i = 0; i < maxRaindrops; i++) {
        raindrop.position.x = GetRandomValue(0, screenWidth);
        raindrop.position.y = GetRandomValue(0, screenHeight);
        raindrop.color = raindrop_c;
        raindrop.speed = GetRandomValue(50, 55) * 0.1;
        raindrops.push_back(raindrop);
    }

    // Output messages to the console.
    std::cout << std::endl;
    std::cout << "FLAPPY QUIZ" << std::endl;
    std::cout << std::endl;
    std::cout << "TEST YOUR KNOWLEDGE!" << std::endl;
    std::cout << "ANSWER A QUESTION TO SAVE YOURSELF!" << std::endl;
    std::cout << "THE QUESTION WILL APPEAR ON THE CONSOLE." << std::endl;
    std::cout << "NOTE! Please write your answers with a capital letter!" << std::endl;

    // Main game loop.
    while (!WindowShouldClose()) {

        // Begin drawing.
        BeginDrawing();

        // Game music mechanisms.
        if (IsKeyPressed(KEY_P)) {
            if (isSoundPlaying) {
                StopMusicStream(music);
                showMusicIcon = false;
            }
            else {
                PlayMusicStream(music);
                showMusicIcon = true;
            }
            isSoundPlaying = !isSoundPlaying;
        }
        UpdateMusicStream(music);

        // Main menu mechanisms.
        if (!mainMenu) {
            if (!pauseMenu) {
                DrawTexture(resizedTexture, 0, 0, WHITE);

                // Display the music icon in different colours if currently playing or not.
                if (showMusicIcon) {
                    DrawCircle(screenWidth - 50,50, 40, GREEN);
                    DrawTexture(resizedNote, screenWidth - 75, 25, BLACK);
                }
                else if (!showMusicIcon) {
                    DrawCircle(screenWidth - 50,50, 40, RED);
					DrawTexture(resizedNote, screenWidth - 75, 25, BLACK);
                }

                // Set up the raindrop random spawn.
                for (size_t i = 0; i < raindrops.size(); i++) {
                    raindrops[i].position.y += raindrops[i].speed;

                    if (raindrops[i].position.y > screenHeight) {
                        raindrops[i].position.y = 0;
                        raindrops[i].position.x = GetRandomValue(0, screenWidth);
                    }
                    DrawTextureEx(raindropTexture, raindrops[i].position, 0, -0.1f, raindrops[i].color);
                }

                // Initalize the needed variables for 'PLAY' button.
                Vector2 mousePosition = GetMousePosition();
                bool isMouseOverButtonPlay = checkCollisionPointRec(mousePosition, playButton);

                // Draw the "PLAY" button and display the text.
                DrawRectangleRec(playButton, (isMouseOverButtonPlay ? SKYBLUE : BLUE));
                DrawText("PLAY", (screenWidth / 2) - 60, (screenHeight / 2) + 130, 50, BLACK);

                // Logic of "PLAY" button.
                if (isMouseOverButtonPlay && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    mainMenu = true;
                }

				// Initalize the needed variables for 'RULES' button.
                bool isMouseOverButtonRules = checkCollisionPointRec(mousePosition, rulesButton);

                // Draw the "RULES" button and display the text.
                DrawRectangleRec(rulesButton, (isMouseOverButtonRules ? GREEN : DARKGREEN));
                DrawText("RULES", (screenWidth / 2) - 75, (screenHeight / 2) + 280, 50, BLACK);

                // Logic of "RULES" button.
                if (isMouseOverButtonRules && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    pauseMenu = true;
                }
            }

            // Show the rules of the game.
            else if (pauseMenu) {
                DrawTexture(resizedRules, 0, 0, WHITE);

                if (showMusicIcon) {
                    DrawCircle(screenWidth - 50, 50, 40, GREEN);
                    DrawTexture(resizedNote, screenWidth - 75, 25, BLACK);
                }
                else if (!showMusicIcon) {
                    DrawCircle(screenWidth - 50, 50, 40, RED);
                    DrawTexture(resizedNote, screenWidth - 75, 25, BLACK);
                }
                
                // Call the rules function.
                rules();

                // Declare the needed variables.
                Vector2 mousePosition = GetMousePosition();

                bool isMouseOverButtonReturn = checkCollisionPointRec(mousePosition, returnButton);

                // Draw the "RETURN" button which sends the user back to the start.
                DrawRectangleRec(returnButton, (isMouseOverButtonReturn ? GREEN : DARKGREEN));
                DrawText("RETURN", (screenWidth / 2) - 95, (screenHeight / 2) + 280, 50, BLACK);

                // Logic of "RETURN" button.
                if (isMouseOverButtonReturn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    pauseMenu = false;
                }
            }
            // Draw logo of the team.
            DrawTexture(resizedLogo, screenWidth - 190, screenHeight -  170, WHITE);
        }

        // Game mechanism.
        else if (mainMenu) {
            // Clear background with the sky colour.
            ClearBackground(sky_c);

            bird.update();

            // Get the elapsed time.
            elapsedTime -= currentTime / 1.95;

            // Unpaused game logic.
            if (!pause) {
                // Set up the cloud random spawn.
                for (size_t i = 0; i < clouds.size(); i++) {
                    clouds[i].position.y += clouds[i].speed;

                    if (clouds[i].position.y > screenHeight) {
                        clouds[i].position.y = 0;
                        clouds[i].position.x = GetRandomValue(0, screenWidth);
                        clouds[i].size.y = GetRandomValue(200, 250);
                        clouds[i].size.x = GetRandomValue(220, 270);
                    }
                    DrawTextureEx(cloudTexture, clouds[i].position, 0, -0.6f, cloud_c);
                }

                // Set up the raindrop random spawn.
                for (size_t i = 0; i < raindrops.size(); i++) {
                    raindrops[i].position.y += raindrops[i].speed;

                    if (raindrops[i].position.y > screenHeight) {
                        raindrops[i].position.y = 0;
                        raindrops[i].position.x = GetRandomValue(0, screenWidth);
                    }

                    // Collision logic between the avatar and the raindrops.
                    if (checkCollisionHead(bird, raindrops[i]) || checkCollisionWings(bird, raindrops[i]) || checkCollisionTail(bird, raindrops[i])) {
                        pause = true;
                        raindrops[i].position.y = 0;
                        raindrops[i].position.x = GetRandomValue(0, screenWidth);
                    }
                    DrawTextureEx(raindropTexture, raindrops[i].position, 0, -0.1f, raindrops[i].color);
                }

                // Draw the FPS, the time, the score and the music icon.
                DrawFPS(15, 20);
                DrawText(TextFormat("%.2f", abs(elapsedTime) / 10), 30, 45, 100, YELLOW);
                DrawText("Score: ", 30, 130, 50, YELLOW);
                DrawText(TextFormat("%i", answeredQuestions), 200, 130, 50, YELLOW);
                if (showMusicIcon) {
                    DrawCircle(screenWidth - 50, 50, 40, GREEN);
                    DrawTexture(resizedNote, screenWidth - 75, 25, BLACK);
                }
                else if (!showMusicIcon) {
                    DrawCircle(screenWidth - 50, 50, 40, RED);
                    DrawTexture(resizedNote, screenWidth - 75, 25, BLACK);
                }
            }

            // Paused game logic.
            if (pause) {

                // Boolean to check if the user's answer is correct.
                bool checkAnswer = false;
                // Call the question function.
                question(checkAnswer);

                // User's response logic.
                if (checkAnswer) {
                    pause = false;
                    answeredQuestions++;
                }

                else {
                    pause = true;
                    std::cout << "Your final time is: " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << abs(elapsedTime) / 10 << " s." << std::endl;
                    std::cout << "You answered: " << answeredQuestions << " questions!" << std::endl;
                    break;
                }
            }
            else {
                bird.draw();
            }
            
        }

        // End drawing.
        EndDrawing();
    }

    // Unload all images and audio.
    UnloadTexture(flappy1);
    UnloadTexture(flappy2);
    UnloadTexture(raindropTexture);
    UnloadTexture(cloudTexture);
    UnloadTexture(resizedTexture);
    UnloadTexture(resizedNote);
    UnloadMusicStream(music);

    //Close audio device.
    CloseAudioDevice();
    
    // Close the window.
    CloseWindow();
}