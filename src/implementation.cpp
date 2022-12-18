#include "Classes.h"

Textures LoadTextures(const char* Team){
    const char *Werewolves="assets/Werewolves.png";
    const char *Vampires="assets/Vampires.png";
    const char *Avatar1="assets/AvatarVamp.png";
    const char *Avatar2="assets/AvatarWere.png";
    const char *Tree ="assets/Tree.png";
    const char *Lake ="assets/Lake.png";
    const char *A;
    Texture2D WerewolfSprite=LoadTexture(Werewolves);
    Texture2D VampireSprite=LoadTexture(Vampires);
    Texture2D TreeSprite = LoadTexture(Tree);
    Texture2D LakeSprite = LoadTexture(Lake);
    if(!strcmp(Team, "Werewolves")){
        A=Avatar2;
    }else{
        A=Avatar1;
    }
    Texture2D AvatarSprite=LoadTexture(A);
    return {WerewolfSprite, VampireSprite,AvatarSprite,TreeSprite,LakeSprite};
}

bool CheckCollisionsRectangles(Vector2 v1, Vector2 v2){
    bool collision=false;
    if(v1.x<v2.x+21 && v1.x+21>v2.x && v1.y<v2.y+21 && v1.y+21>v2.y)
        collision=true;
    return collision;
}

bool CheckCollisionTerrain(Game State,int number, int type,int TreeNum){
    for(int j = 0 ; j < TreeNum ; j++){
        if(CheckCollisionsRectangles(State.Rectangles[number][type].position,State.Terrains[j].TerPos))
            return 1;
    }
    return 0;    
}

void HealTeammate(Game State, int number, int i, int type){
    if(type==0){
        if(State.werewolf[i].get_health()!=100){
            int temp=GetRandomValue(0,1);
            if(temp==0){
                return;
            }else{
                if(State.werewolf[number].get_pot()!=0){
                    State.werewolf[number].usepotion();
                    State.werewolf[i].healup();
                }
            }
        }else if(State.werewolf[number].get_health()!=100){
            int temp=GetRandomValue(0,1);
            if(temp==0){
                return;
            }else{
                if(State.werewolf[i].get_pot()!=0){
                    State.werewolf[i].usepotion();
                    State.werewolf[number].healup();
                }
            }
        }
    }else if(type==1){
        if(State.vampire[i].get_health()!=100){
            int temp=GetRandomValue(0,1);
            if(temp==0){
                return;
            }else{
                if(State.vampire[number].get_pot()!=0){
                    State.vampire[number].usepotion();
                    State.vampire[i].healup();
                }
            }
        }else if(State.vampire[number].get_health()!=100){
            int temp=GetRandomValue(0,1);
            if(temp==0){
                return;
            }else{
                if(State.vampire[i].get_pot()!=0){
                    State.vampire[i].usepotion();
                    State.vampire[number].healup();
                }
            }
        }
    }
}

void Damage(Game State, int number, int i){
    if(State.werewolf[number].get_damage() > State.vampire[i].get_damage()){
        int Damage=State.werewolf[number].get_damage() - State.vampire[i].get_defense();
        if(Damage<0){
            Damage=0;
        }
        State.vampire[i].set_health(State.vampire[i].get_health() - Damage);
        if(State.vampire[i].get_health() <= 0){
            State.Rectangles[i][1].position={INF, INF};
        }
    }else if(State.werewolf[number].get_damage() < State.vampire[i].get_damage()){
        int Damage=State.vampire[i].get_damage() - State.werewolf[number].get_defense();
        if(Damage<0){
            Damage=0;
        }
        State.werewolf[number].set_health(State.werewolf[number].get_health() - Damage);
        if(State.werewolf[number].get_health() <= 0){
            State.Rectangles[number][0].position={INF/2, INF/2};
        }
    }else{
        int Damage1=State.werewolf[number].get_damage() - State.vampire[i].get_defense();
        if(Damage1<0){
            Damage1=0;
        }
        State.vampire[i].set_health(State.vampire[i].get_health() - Damage1);
        if(State.vampire[i].get_health() <= 0){
            State.Rectangles[i][1].position={INF, INF};
        }
        int Damage2=State.vampire[i].get_damage() - State.werewolf[number].get_defense();
        if(Damage2<0){
            Damage2=0;
        }
        State.werewolf[number].set_health(State.werewolf[number].get_health() - Damage2);
        if(State.werewolf[number].get_health() <= 0){
            State.Rectangles[number][0].position={INF/2, INF/2};
        }
    }
}

int CheckCollisions(Game State, int number, int count, int type, int CheckWithOther, int Spawning){
    for(int i=0;i<count;i++){
        if(i!=number){
            if(type==0){
                if(CheckCollisionsRectangles(State.Rectangles[number][0].position, State.Rectangles[i][0].position)){
                    if(!Spawning){
                        HealTeammate(State, number, i, type);
                    }
                    return 1;
                }
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][0].position, State.Rectangles[i][1].position)){
                        if(!Spawning){
                            Damage(State, number, i);
                        }
                        return 2;
                    }
                }
            }else if(type==1){
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].position, State.Rectangles[i][0].position)){
                        if(!Spawning){
                            Damage(State, i, number);
                        }
                        return 2;
                    }
                }
                if(CheckCollisionsRectangles(State.Rectangles[number][1].position, State.Rectangles[i][1].position)){
                    if(!Spawning){
                        HealTeammate(State, number, i, type);
                    }
                    return 3;
                }
            }
        }else{
            if(CheckWithOther==1){
                if(type==0){
                    if(CheckCollisionsRectangles(State.Rectangles[number][0].position, State.Rectangles[i][1].position)){
                        if(!Spawning){
                            Damage(State, number, i);
                        }
                        return 2;
                    }
                }else if(type==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].position, State.Rectangles[i][0].position)){
                        if(!Spawning){
                            Damage(State, i, number);
                        }
                        return 2;
                    }
                }
            }
        }
    }
    return 0;
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
    int count=(Width*Height)/(20*21*21);
    Game State;
    State.Rectangles=new Rec*[count];
    Rectangle frameRec={0.0f, 0.0f, 21.0f, 21.0f};
    Rectangle frameRec2={0.0f, 0.0f, 21.0f, 21.0f};
    for(int i=0;i<count;i++){
        State.Rectangles[i]=new Rec[2];
        WerewolfSpritePosition={float(GetRandomValue(0, int(Width*30/100))), float(GetRandomValue(0, Height-21))};
        State.Rectangles[i][0]={WT, frameRec, WerewolfSpritePosition, WHITE};
        while(CheckCollisions(State, i, i, 0, 0, 1)){
            WerewolfSpritePosition={float(GetRandomValue(0, int(Width*30/100))), float(GetRandomValue(0, Height-21))};
            State.Rectangles[i][0]={WT, frameRec, WerewolfSpritePosition, WHITE};
        }
        VampireSpritePosition={float(GetRandomValue(int(Width*70/100), Width-21)), float(GetRandomValue(0, Height-21))};
        State.Rectangles[i][1]={VT, frameRec2, VampireSpritePosition, WHITE};
        while(CheckCollisions(State, i, i, 1, 0, 1)){
            VampireSpritePosition={float(GetRandomValue(int(Width*70/100), Width-21)), float(GetRandomValue(0, Height-21))};
            State.Rectangles[i][1]={VT, frameRec2, VampireSpritePosition, WHITE};
        }
        DrawTextureRec(WT, frameRec, WerewolfSpritePosition, WHITE);
        DrawTextureRec(VT, frameRec2, VampireSpritePosition, WHITE);
    }
    return State.Rectangles;
}

void DeallocateMem(Game State, int count){
    for(int i=0; i<count; i++){
        delete [] State.Rectangles[i];
    }
    delete [] State.Rectangles;
    delete [] State.werewolf;
    delete [] State.vampire;
    delete [] State.Terrains;
}

Terrain* LoadTerrain(int Width,int Height,Texture2D TreeTex,Texture2D LakeTex){
    Rectangle frameRec={0.0, 0.0, 21.0, 21.0};
    int TreeCount;
    int LakeCount ;
    int total = 0;
    if(Height<750){
        TreeCount = 2;LakeCount = 2;total = 4;
    }
    else{
        TreeCount = 4;LakeCount = 4;total = 8;
    }
    Terrain *T;
    bool check = false;
    Vector2 TerPosition;
    Rectangle RecTable[total];
    T = new Terrain[total]; 
    for(int i=0;i<TreeCount;i++){
        T[i].texture = TreeTex;
        T[i].set_pos({float(GetRandomValue(Width/2-25,Width/2+25)),float(GetRandomValue(50,Height/3))});
        RecTable[i] = {T[i].TerPos.x,T[i].TerPos.y,21.0,21.0};
        for(int j = 0 ; j < i ; j++){
            while(CheckCollisionRecs(RecTable[i],RecTable[j])){
                T[i].set_pos({float(GetRandomValue(Width/2-40,Width/2+40)),float(GetRandomValue(50,Height/2))});
                RecTable[i] = {T[i].TerPos.x,T[i].TerPos.y,21.0,21.0};
            }
        }
        T[i].Recta = RecTable[i];
        DrawTextureRec(T[i].texture,T[i].Recta,T[i].TerPos,WHITE);  
    }
    for(int i=TreeCount;i<total;i++){
        T[i].texture = LakeTex;
        T[i].set_pos({float(GetRandomValue(Width/2-25,Width/2+25)),float(GetRandomValue(Height/3,Height/2))});
        RecTable[i] = {T[i].TerPos.x,T[i].TerPos.y,21.0,21.0};
        for(int j = 0 ; j < i ; j++){
            while(CheckCollisionRecs(RecTable[i],RecTable[j])){
                T[i].set_pos({float(GetRandomValue(Width/2-40,Width/2+40)),float(GetRandomValue(50,Height/2+100))});
                RecTable[i] = {T[i].TerPos.x,T[i].TerPos.y,21.0,21.0};
            }
        }
        T[i].Recta = RecTable[i];
        DrawTextureRec(T[i].texture,T[i].Recta,T[i].TerPos,WHITE);
    }
    
    return T;
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
    int CollisionType;
    int z1=GetRandomValue(1,4);     //1=move right, 2=move left, 3=move up, 4=move down
    int TerrainCount = sizeof(State.Terrains);
    switch(z1){
        case 1:
            State.Rectangles[i][0].position.x+=5;
            if(State.Rectangles[i][0].position.x>Width-21)
                State.Rectangles[i][0].position.x=Width-21;
            if(CollisionType=CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.x-=5;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.x-=5;
            }
            break;
        case 2:
            State.Rectangles[i][0].position.x-=5;
            if(State.Rectangles[i][0].position.x<0)
                State.Rectangles[i][0].position.x=0;
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.x+=5;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.x+=5;
            }
            break;
        case 3:
            State.Rectangles[i][0].position.y+=5;
            if(State.Rectangles[i][0].position.y>Height-21)
                State.Rectangles[i][0].position.y=Height-21;
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.y-=5;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.y-=5;
            }
            break;
        case 4:
            State.Rectangles[i][0].position.y-=5;
            if(State.Rectangles[i][0].position.y<0)
                State.Rectangles[i][0].position.y=0;
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.y+=5;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.y+=5;
            }
            break;
        default:
            break;
    }
}

void MoveVampires(Game State, int Width,int Height, int i, int count){
    int z2=GetRandomValue(1,8);     //1=move right, 2=move left, 3=move up, 4=move down, 5=diagonal top right, 6=diagonal bottom right, 7=diagonal bottom left, 8=diagonal top left
    int TerrainCount = sizeof(State.Terrains);
    switch(z2){
        case 1:
            State.Rectangles[i][1].position.x+=5;
            if(State.Rectangles[i][1].position.x>Width-21)
                State.Rectangles[i][1].position.x=Width-21;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x-=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x-=5;
            }
            break;
        case 2:
            State.Rectangles[i][1].position.x-=5;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x+=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x+=5;
            }
            break;
        case 3:
            State.Rectangles[i][1].position.y+=5;
            if(State.Rectangles[i][1].position.y>Height-21)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.y-=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x-=5;
            }
            break;
        case 4:
            State.Rectangles[i][1].position.y-=5;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.y+=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
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
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x-=5;
                State.Rectangles[i][1].position.y-=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.y-=5;
                State.Rectangles[i][1].position.x-=5;
            }
            break;
        case 6:
            State.Rectangles[i][1].position.x+=5;
            State.Rectangles[i][1].position.y-=5;
            if(State.Rectangles[i][1].position.x>Width-21)
                State.Rectangles[i][1].position.x=Width-21;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x-=5;
                State.Rectangles[i][1].position.y+=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.y+=5;
                State.Rectangles[i][1].position.x-=5;
            }
            break;
        case 7:
            State.Rectangles[i][1].position.x-=5;
            State.Rectangles[i][1].position.y-=5;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x+=5;
                State.Rectangles[i][1].position.y+=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.y+=5;
                State.Rectangles[i][1].position.x+=5;
            }
            break;
        case 8:
            State.Rectangles[i][1].position.x-=5;
            State.Rectangles[i][1].position.y+=5;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(State.Rectangles[i][1].position.y>Height-21)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x+=5;
                State.Rectangles[i][1].position.y-=5;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x+=10;
                State.Rectangles[i][1].position.y-=10;
            }
            break;
        default:
            break;
    }
}
Vector2 UpdateAvatar(Game State, int Width,int Height){  
    if (IsKeyDown(KEY_RIGHT)){
        State.avatar.z.x +=5;
        if(State.avatar.z.x>Width-21)State.avatar.z.x -=5;
    }
    if (IsKeyDown(KEY_LEFT)){
        State.avatar.z.x -= 5;
        if(State.avatar.z.x<0)State.avatar.z.x +=5;
    }
    if (IsKeyDown(KEY_UP)){
        State.avatar.z.y -= 5;
        if(State.avatar.z.y<0)State.avatar.z.y +=5;
    }
    if (IsKeyDown(KEY_DOWN)){
        State.avatar.z.y += 5;
        if(State.avatar.z.y>Height-21)State.avatar.z.y -=5;
    }
    return State.avatar.z;
}

void UpdateEntities(Game State,int Width, int Height){
    int count=(Width*Height)/(20*21*21);
    int TerrainCount = sizeof(State.Terrains);
    for(int i=0;i<TerrainCount;i++){

        DrawTextureRec(State.Terrains[i].texture,{0.0f, 0.0f, 21.0f, 21.0f},State.Terrains[i].TerPos,WHITE);

    }
    for(int i=0;i<count;i++){
        MoveWerewolves(State, Width, Height, i, count);
        MoveVampires(State, Width, Height, i, count);
        //MoveAvatar
        DrawTextureRec(State.avatar.texture, {0.0f, 0.0f, 21.0f, 21.0f}, State.avatar.z, WHITE);
        if(State.werewolf[i].get_health()>0){
            DrawTextureRec(State.Rectangles[i][0].texture, State.Rectangles[i][0].source, State.Rectangles[i][0].position, State.Rectangles[i][0].tint);
        }
        if(State.vampire[i].get_health()>0){
            DrawTextureRec(State.Rectangles[i][1].texture, State.Rectangles[i][1].source, State.Rectangles[i][1].position, State.Rectangles[i][1].tint);
        }
    }
}

void PauseGame(Game State, int Width, int Height, bool* pause,bool* FirstTime){
    DrawText("Game Paused",(Width/2)-70,Height/2,30,WHITE);
    DrawText("If you want to Continue Press [ENTER]/[P]",5,10,Width/36,WHITE);
    DrawText("If you want to Exit Press [X]/[ESCAPE]",5,45,Width/36,WHITE);
    DrawText("If you want to Restart Press [R]",5,85,Width/36,WHITE);
    if(IsKeyPressed(KEY_ENTER))*pause = false;
    if(IsKeyPressed(KEY_R)){
        *pause = false;
        *FirstTime = true;
        int count=(Width*Height)/(20*21*21);
        for(int i=0; i<count; i++){
            State.vampire[i].set_health(10);
            State.werewolf[i].set_health(10);
        }
    }    
    if(IsKeyPressed(KEY_X)){
        EndDrawing(); 
        CloseWindow();  
    }
}

void CreateWindow(int Width, int Height, const char* Team){
    int time=0;
    bool pause = false;
    bool FirstTime=true;
    Game State(Width, Height);
    InitWindow(Width, Height, "Werewolves vs Vampires");
    SetTargetFPS(60);
    Texture2D WerewolfTexture, VampireTexture, AvatarTexture, TreeTexture, LakeTexture;
    Textures temp=LoadTextures(Team);
    WerewolfTexture=temp.T1;
    VampireTexture=temp.T2;
    AvatarTexture=temp.T3;
    TreeTexture = temp.T4;
    LakeTexture=temp.T5;
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        if(FirstTime==true){
            State.Terrains = LoadTerrain(Width,Height,TreeTexture,LakeTexture);
            State.Rectangles=LoadEntites(Width, Height, WerewolfTexture, VampireTexture);
            State.avatar=LoadAvatar(Width, Height, AvatarTexture, Team);
            FirstTime=false;
            int count=(Width*Height)/(20*21*21);
        }
        if(IsKeyPressed(KEY_P)){
            pause = !pause;
        }
        if(!pause){
            DayNightCycle(&time, Width, Height);
            UpdateEntities(State, Width, Height);
            State.avatar.set_pos(UpdateAvatar(State,Width,Height));
            DrawTextureRec(State.avatar.texture, {0.0f, 0.0f, 21.0f, 21.0f}, State.avatar.z, WHITE);
        }else{
            PauseGame(State, Width, Height, &pause,&FirstTime);    
        }
        EndDrawing();
    }
    CloseWindow();
    DeallocateMem(State, (Width*Height)/(20*21*21));
}
