#include "Classes.h"


void CreateWindow(int Width, int Height){
    InitWindow(Width, Height, "Werewolves vs Vampires");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("You created your 1st game.", Width/2, Height/2, 20, WHITE);
    }
}