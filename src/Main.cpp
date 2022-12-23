#include "Functions.h"

//argv[1]=WindowWidth
//argv[2]=WindowHeight
//argv[3]=Team which user supports. Vampires or Werewolves

//good map size could be 750x750. Entity could be 21x21 pixels(20 pixels=sprite, 1 pixel for collision checking). (750*750/20)/(21*21)=63 entities per team

int main(int argc, char** argv){
    try{
        if(argc!=4){
            throw argc;
        }
        if(strcmp(argv[3], "Vampires") && strcmp(argv[3], "vampires") && strcmp(argv[3], "Werewolves") && strcmp(argv[3], "werewolves")){
            throw argv[3];
        }
        if(atoi(argv[1])<500 || atoi(argv[1])>1500 || atoi(argv[2])<500 || atoi(argv[2])>1000){
            cout<<argv[1];
            Position x(atof(argv[1]), atof(argv[2]));
            throw x;
        }
    }
    catch(int argc){
        cout << "\nProgram needs to have exactly 4 arguements, you gave " << argc << ".\nExiting...\n\n";
        return -1;
    }
    catch(char* chr){
        cout << "\nWrong team selection. Choose either Werewolves or Vampires.\nExiting...\n\n";
        return -1;
    }
    catch(Position x){
        InitWindow(500, 500, "Error");
        string posX = to_string((int)x.get_x());
        string posY = to_string((int)x.get_y());
        const char* X = posX.c_str();
        const char* Y = posY.c_str();
        SetTargetFPS(60);
        BeginDrawing();
        ClearBackground(BLACK);
        while(!WindowShouldClose()){
            DrawText("Wrong Inputs Given for the Window",150,220,2,WHITE);
            DrawText(X,210,235,2,RED);
            DrawText(" - ",235,235,2,RED);
            DrawText(Y,250,235,2,RED);
            DrawText("Inputs should be between",170,260,2,WHITE);
            DrawText("Width : 500 - 1500",170,280,2,WHITE);
            DrawText("Height : 500 - 1000",170,300,2,WHITE);
            EndDrawing();
        }
        CloseWindow();
        return -1;
    }
    int WindowWidth=atoi(argv[1]), WindowHeight=atoi(argv[2]);
    const char* name="Werewolves";
    if(!strcmp(argv[3], "Vampires") || !strcmp(argv[3], "vampires")){
        name="Vampires";
    }
    CreateWindow(WindowWidth, WindowHeight, name);
    return 0;
}
