#include "Classes.h"

int main(void){
    int WindowWidth, WindowHeight;
    cout << "How big do you want the window to be: ";
    cin >> WindowWidth , WindowHeight;
    InitWindow(WindowWidth, WindowHeight, "Werewolves vs Vampires");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("You created your 1st game.", WindowWidth/2, WindowHeight/2, 20, WHITE);
    }
    CloseWindow();
}
