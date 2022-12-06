#include "Classes.h"

TwoTextures LoadTextures(){
    const char *Werewolves="assets/Werewolves.png";
    const char *Vampires="assets/Vampires.png";
    Texture2D WerewolfSprite=LoadTexture(Werewolves);
    Texture2D VampireSprite=LoadTexture(Vampires);
    return {WerewolfSprite, VampireSprite};
}

Rec** LoadEntites(int Width, int Height, Texture2D WT, Texture2D VT){
    SetRandomSeed(time(NULL));
    Vector2 WerewolfSpritePosition,VampireSpritePosition;
    int count=(Width*Height)/(15*21*21);
    Rec** Recs=new Rec*[count];
    Rectangle frameRec={0.0f, 0.0f, 21.0f, 21.0f};
    Rectangle frameRec2={0.0f, 0.0f, 21.0f, 21.0f};
    for(int i=0;i<count;i++){
        Recs[i]=new Rec[2];
        WerewolfSpritePosition={float(GetRandomValue(0, int(Width*30/100))), float(GetRandomValue(0, Height-21))};
        VampireSpritePosition={float(GetRandomValue(int(Width*70/100), Width-21)), float(GetRandomValue(0, Height-21))};
        Recs[i][0]={WT, frameRec, WerewolfSpritePosition, WHITE};
        Recs[i][1]={VT, frameRec2, VampireSpritePosition, WHITE};
        DrawTextureRec(WT, frameRec, WerewolfSpritePosition, WHITE);
        DrawTextureRec(VT, frameRec2, VampireSpritePosition, WHITE);
    }
    return Recs;
}

void UpdateEntites(Rec** Rectangles, int Width, int Height){
    int count=(Width*Height)/(15*21*21);
    for(int i=0;i<count;i++){
        Rec* temp=Rectangles[i];
        DrawTextureRec(temp[0].texture, temp[0].source, temp[0].position, temp[0].tint);
        DrawTextureRec(temp[1].texture, temp[1].source, temp[1].position, temp[1].tint);
    }
}

void CreateWindow(int Width, int Height){
    bool FirstTime=true;
    Rec** Rectangles;
    InitWindow(Width, Height, "Werewolves vs Vampires");
    SetTargetFPS(60);
    Texture2D WerewolfTexture, VampireTexture;
    TwoTextures temp=LoadTextures();
    WerewolfTexture=temp.T1;
    VampireTexture=temp.T2;
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        if(FirstTime==true){
            Rectangles=LoadEntites(Width, Height, WerewolfTexture, VampireTexture);
            FirstTime=false;
        }
        UpdateEntites(Rectangles, Width, Height);
        EndDrawing();
        //DrawText("You created your 1st game.", Width/2, Height/2, 20, WHITE);
    }
    CloseWindow();
}
