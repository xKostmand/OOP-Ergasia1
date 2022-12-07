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
    int random[2] = {-1,1};
    int RandIndex = rand()%2;
    int count=(Width*Height)/(15*21*21);
    for(int i=0;i<count;i++){
        Rec* temp=Rectangles[i];
        temp[0].position.x+= random[RandIndex];
        temp[0].position.x = Clamp(temp[0].position.x,0,Width-50);

        temp[1].position.x+= random[RandIndex];
        temp[1].position.x = Clamp(temp[1].position.x,0,Width-50);

        temp[1].position.y+= GetRandomValue(-1,1);
        temp[1].position.y = Clamp(temp[1].position.y,0,Height-50);
        
        DrawTextureRec(temp[0].texture, temp[0].source, temp[0].position, temp[0].tint);
        DrawTextureRec(temp[1].texture, temp[1].source, temp[1].position, temp[1].tint);
    }
}

void CreateWindow(int Width, int Height){
    bool FirstTime=true;
    Rec** Rectangles;
    InitWindow(Width, Height, "Werewolves vs Vampires");
    SetTargetFPS(60);
    /*int myWidth = GetMonitorWidth(0),myHeight = GetMonitorHeight(0);
    if(Height < myHeight/4 || Height > myHeight || Width < myWidth/4 || Width > myWidth){
              CloseWindow();
        cout << "\n\n\n\nWrong inputs, window size must have scaling : \nWidth : "<<myWidth/4<<" - "<<
        myWidth<<"\nHeight : " << myHeight/2<<" - "<<myHeight<<"\n";
        return;
    }*/
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
            int count=(Width*Height)/(15*21*21);
            for(int i=0;i<count;i++){
                Rec* temp=Rectangles[i];
                DrawTextureRec(temp[0].texture, temp[0].source, temp[0].position, temp[0].tint);
                DrawTextureRec(temp[1].texture, temp[1].source, temp[1].position, temp[1].tint);
            }
        }
        UpdateEntites(Rectangles, Width, Height);
        EndDrawing();
    }
    CloseWindow();
}
