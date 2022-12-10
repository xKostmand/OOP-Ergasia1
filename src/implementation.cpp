#include "Classes.h"

Textures LoadTextures(const char* Team){
    const char *Werewolves="assets/Werewolves.png";
    const char *Vampires="assets/Vampires.png";
    const char *Avatar1="assets/AvatarVamp.png";
    const char *Avatar2="assets/AvatarWere.png";
    const char *A;
    Texture2D WerewolfSprite=LoadTexture(Werewolves);
    Texture2D VampireSprite=LoadTexture(Vampires);
    if(!strcmp(Team, "Werewolves")){
        A=Avatar2;
    }else{
        A=Avatar1;
    }
    Texture2D AvatarSprite=LoadTexture(A);
    return {WerewolfSprite, VampireSprite, AvatarSprite};
}

bool CheckCollisionsRectangles(Vector2 v1, Vector2 v2){
    bool collision=false;
    if(v1.x<v2.x+21 && v1.x+21>v2.x && v1.y<v2.y+21 && v1.y+21>v2.y)
        collision=true;
    return collision;
}

bool CheckCollisions(Rec** Rectangles, int number, int count, int type, int CheckWithOther){
    for(int i=0;i<count;i++){
        if(i!=number){
            if(type==0){
                if(CheckCollisionsRectangles(Rectangles[number][0].position, Rectangles[i][0].position)){
                    return true;
                }
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(Rectangles[number][0].position, Rectangles[i][1].position)){
                        return true;
                    }
                }
            }else if(type==1){
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(Rectangles[number][1].position, Rectangles[i][0].position)){
                        return true;
                    }
                }
                if(CheckCollisionsRectangles(Rectangles[number][1].position, Rectangles[i][1].position)){
                    return true;
                }
            }
        }else{
            if(CheckWithOther==1){
                if(type==0){
                    if(CheckCollisionsRectangles(Rectangles[number][0].position, Rectangles[i][1].position)){
                        return true;
                    }
                }else if(type==1){
                    if(CheckCollisionsRectangles(Rectangles[number][1].position, Rectangles[i][0].position)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void DayNightCycle(int* time, int Width, int Height){
    (*time)++;
    if(*time>0 && *time<151){
        DrawText("Time: Day",(Width/2)-50,5,18,GOLD);
    }else if(*time>150 && *time<301){
        DrawText("Time: Night",(Width/2)-50,5,18,SKYBLUE);
        if(*time==300){    
            *time=0;
        }
    }
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
        Recs[i][0]={WT, frameRec, WerewolfSpritePosition, WHITE};
        while(CheckCollisions(Recs, i, i, 0, 0)){
            WerewolfSpritePosition={float(GetRandomValue(0, int(Width*30/100))), float(GetRandomValue(0, Height-21))};
            Recs[i][0]={WT, frameRec, WerewolfSpritePosition, WHITE};
        }
        VampireSpritePosition={float(GetRandomValue(int(Width*70/100), Width-21)), float(GetRandomValue(0, Height-21))};
        Recs[i][1]={VT, frameRec2, VampireSpritePosition, WHITE};
        while(CheckCollisions(Recs, i, i, 1, 0)){
            VampireSpritePosition={float(GetRandomValue(int(Width*70/100), Width-21)), float(GetRandomValue(0, Height-21))};
            Recs[i][1]={VT, frameRec2, VampireSpritePosition, WHITE};
        }
        Recs[i][0]={WT, frameRec, WerewolfSpritePosition, WHITE};
        Recs[i][1]={VT, frameRec2, VampireSpritePosition, WHITE};
        DrawTextureRec(WT, frameRec, WerewolfSpritePosition, WHITE);
        DrawTextureRec(VT, frameRec2, VampireSpritePosition, WHITE);
    }
    return Recs;
}

Avatar LoadAvatar(int Width, int Height, Texture2D AvatarTexture, const char* Team){
    Rectangle frameRec={0.0f, 0.0f, 21.0f, 21.0f};
    Vector2 SpritePosition={float(Width/2), float(0.9*Height)};
    Avatar A;
    A.Team=Team;
    A.texture=AvatarTexture;
    A.z=SpritePosition;
    DrawTextureRec(AvatarTexture, frameRec, SpritePosition, WHITE);
    return A;
}

void MoveWerewolves(Game State, int Width,int Height, int i, int count){
    int z1=GetRandomValue(1,4);     //1=move right, 2=move left, 3=move up, 4=move down
    switch(z1){
        case 1:
            State.Rectangles[i][0].position.x+=5;
            if(State.Rectangles[i][0].position.x>Width-21)
                State.Rectangles[i][0].position.x=Width-21;
            if(CheckCollisions(State.Rectangles,i,count,0,1)){
                State.Rectangles[i][0].position.x-=5;
            }
            break;
        case 2:
            State.Rectangles[i][0].position.x-=5;
            if(State.Rectangles[i][0].position.x<0)
                State.Rectangles[i][0].position.x=0;
            if(CheckCollisions(State.Rectangles,i,count,0,1)){
                State.Rectangles[i][0].position.x+=5;
            }
            break;
        case 3:
            State.Rectangles[i][0].position.y+=5;
            if(State.Rectangles[i][0].position.y>Height-21)
                State.Rectangles[i][0].position.y=Height-21;
            if(CheckCollisions(State.Rectangles,i,count,0,1)){
                State.Rectangles[i][0].position.y-=5;
            }
            break;
        case 4:
            State.Rectangles[i][0].position.y-=5;
            if(State.Rectangles[i][0].position.y<0)
                State.Rectangles[i][0].position.y=0;
            if(CheckCollisions(State.Rectangles,i,count,0,1)){
                State.Rectangles[i][0].position.y+=5;
            }
            break;
        default:
            break;
    }
}

void MoveVampires(Game State, int Width,int Height, int i, int count){
    int z2=GetRandomValue(1,8);     //1=move right, 2=move left, 3=move up, 4=move down, 5=diagonal top right, 6=diagonal bottom right, 7=diagonal bottom left, 8=diagonal top left
    switch(z2){
        case 1:
            State.Rectangles[i][1].position.x+=5;
            if(State.Rectangles[i][1].position.x>Width-21)
                State.Rectangles[i][1].position.x=Width-21;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.x-=5;
            }
            break;
        case 2:
            State.Rectangles[i][1].position.x-=5;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.x+=5;
            }
            break;
        case 3:
            State.Rectangles[i][1].position.y+=5;
            if(State.Rectangles[i][1].position.y>Height-21)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.y-=5;
            }
            break;
        case 4:
            State.Rectangles[i][1].position.y-=5;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.y+=5;
            }
            break;
        case 5:
            State.Rectangles[i][1].position.x+=5;
            State.Rectangles[i][1].position.y+=5;
            if(State.Rectangles[i][1].position.x>Width-21)
                State.Rectangles[i][1].position.x=Width-21;
            if(State.Rectangles[i][1].position.y>Height-21)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.x-=5;
                State.Rectangles[i][1].position.y-=5;
            }
            break;
        case 6:
            State.Rectangles[i][1].position.x+=5;
            State.Rectangles[i][1].position.y-=5;
            if(State.Rectangles[i][1].position.x>Width-21)
                State.Rectangles[i][1].position.x=Width-21;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.x-=5;
                State.Rectangles[i][1].position.y+=5;
            }
            break;
        case 7:
            State.Rectangles[i][1].position.x-=5;
            State.Rectangles[i][1].position.y-=5;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.x+=5;
                State.Rectangles[i][1].position.y+=5;
            }
            break;
        case 8:
            State.Rectangles[i][1].position.x-=5;
            State.Rectangles[i][1].position.y+=5;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(State.Rectangles[i][1].position.y>Height-21)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State.Rectangles,i,count,1,1)){
                State.Rectangles[i][1].position.x+=5;
                State.Rectangles[i][1].position.y-=5;
            }
            break;
        default:
            break;
    }
}

void UpdateEntities(Game State, int Width, int Height){
    int count=(Width*Height)/(15*21*21);
    for(int i=0;i<count;i++){
        MoveWerewolves(State, Width, Height, i, count);
        MoveVampires(State, Width, Height, i, count);
        //MoveAvatar
        DrawTextureRec(State.avatar.texture, {0.0f, 0.0f, 21.0f, 21.0f}, State.avatar.z, WHITE);
        DrawTextureRec(State.Rectangles[i][0].texture, State.Rectangles[i][0].source, State.Rectangles[i][0].position, State.Rectangles[i][0].tint);
        DrawTextureRec(State.Rectangles[i][1].texture, State.Rectangles[i][1].source, State.Rectangles[i][1].position, State.Rectangles[i][1].tint);
    }
}

void EntityInteractions(Game State, int Width, int Height){

}

void CreateWindow(int Width, int Height, const char* Team){
    int time=0;
    bool pause = false;
    bool FirstTime=true;
    Game State(Width, Height);
    //State=LoadState();
    InitWindow(Width, Height, "Werewolves vs Vampires");
    SetTargetFPS(60);
    Texture2D WerewolfTexture, VampireTexture, AvatarTexture;
    Textures temp=LoadTextures(Team);
    WerewolfTexture=temp.T1;
    VampireTexture=temp.T2;
    AvatarTexture=temp.T3;
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DayNightCycle(&time, Width, Height);
        if(FirstTime==true){
            State.Rectangles=LoadEntites(Width, Height, WerewolfTexture, VampireTexture);
            State.avatar=LoadAvatar(Width, Height, AvatarTexture, Team);
            FirstTime=false;
            int count=(Width*Height)/(15*21*21);
            for(int i=0;i<count;i++){
                Rec* temp=State.Rectangles[i];
                DrawTextureRec(temp[0].texture, temp[0].source, temp[0].position, temp[0].tint);
                DrawTextureRec(temp[1].texture, temp[1].source, temp[1].position, temp[1].tint);
            }
        }
        if(IsKeyPressed(KEY_P))
            pause = !pause;
        if(!pause){
            UpdateEntities(State, Width, Height);
            EntityInteractions(State, Width, Height);
        }
        else if(pause){
            DrawText("Game Paused",(Width/2)-70,Height/2,30,WHITE);
            DrawText("If you want to Continue Press [ENTER]/[P]",5,10,Width/36,WHITE);
            DrawText("If you want to exit Press [X]/[ESCAPE]",5,40,Width/36,WHITE);
            if(IsKeyPressed(KEY_ENTER))
                pause = false;
            if(IsKeyPressed(KEY_X)){
                EndDrawing(); 
                CloseWindow();
                return;   
            }    
        }
        EndDrawing();
    }
    CloseWindow();
}
