#include "raylib.h"
#include "rules.h"

void rules() {
    DrawText("The 'Flappy Quiz' Rules:", GetScreenWidth() / 2 - MeasureText("The 'Flappy Quiz' Rules:", 30) / 2, 50, 30, GOLD);
    DrawText("1) The primary objective of the game is to enhance your knowledge of ecology, chemistry, and biology!", 50, 120, 20, RAYWHITE);
    DrawText("2) In order for you to learn you must keep your feathered friend alive by skillfully avoiding the falling acid raindrops.", 50, 170, 20, RAYWHITE);
    DrawText("3) Don't be alarmed by the falling clouds – they can't hurt you.", 50, 220, 20, RAYWHITE);
    DrawText("4) If you happen to collide with a raindrop, your journey doesn't conclude! You can revive your friend by correctly answering a question related to the mentioned aspects.", 50, 270, 20, RAYWHITE);
    DrawText("5) Find the randomly generated question in the console and provide your answer there.", 50, 320, 20, RAYWHITE);
    DrawText("6) PLEASE BEGIN YOUR ANSWER WITH A CAPITAL LETTER; OTHERWISE, IT WON'T BE COUNTED AS CORRECT IF IT IS.", 50, 370, 20, RAYWHITE);
    DrawText("7) For questions requiring numerical answers, use numbers instead of words.", 50, 420, 20, RAYWHITE);
    DrawText("8) You're playing against time and aiming for the highest score in terms of both time and answered questions. Your time and score are displayed in the top-left corner of the window.", 50, 470, 20, RAYWHITE);
    DrawText("9) Control your avatar using the Left and Right arrow keys.", 50, 520, 20, RAYWHITE);
    DrawText("10) Enjoy learning with our game 'Flappy Quiz'!", 50, 570, 20, RAYWHITE);
}