#include <iostream>
#include "../include/Classes.h"

using namespace std;

int main(void){
    int WindowWidth=0, WindowHeight=0;
    cout << "How big do you want the window to be: ";
    cin >> WindowWidth;
    cin >> WindowHeight;
    InitWindow(WindowWidth, WindowHeight, "Werewolves vs Vampires");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("You created your 1st game.", WindowWidth/2, WindowHeight/2, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
}