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
            return true;
    }
    return false;    
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

void Damage(Game State, int number, int i, int* WereCount, int* VampCount){
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
                            Damage(State, number, i, &(State.WereCount), &(State.VampCount));
                        }
                        return 2;
                    }
                }
            }else if(type==1){
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].position, State.Rectangles[i][0].position)){
                        if(!Spawning){
                            Damage(State, i, number, &(State.WereCount), &(State.VampCount));
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
                            Damage(State, number, i, &(State.WereCount), &(State.VampCount));
                        }
                        return 2;
                    }
                }else if(type==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].position, State.Rectangles[i][0].position)){
                        if(!Spawning){
                            Damage(State, i, number, &(State.WereCount), &(State.VampCount));
                        }
                        return 2;
                    }
                }
            }
        }
    }
    if(CheckCollisionsRectangles(State.Rectangles[number][type].position, State.avatar.get_pos())){
        return 4;
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
    int LakeCount;
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
    T = new Terrain[total];
    for(int i=0;i<TreeCount;i++){
        T[i].texture = TreeTex;
        T[i].set_pos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});

        DrawTextureRec(T[i].texture,T[i].Recta,T[i].TerPos,WHITE);  
    }
    for(int i=TreeCount;i<total;i++){
        T[i].texture = LakeTex;
        T[i].set_pos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});

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


bool CheckAvatarCollisions(Game State, int count){
    for(int i=0;i<count;i++){
        if(CheckCollisionsRectangles(State.avatar.get_pos(), State.Rectangles[i][0].position) || CheckCollisionsRectangles(State.avatar.get_pos(), State.Rectangles[i][1].position))
            return true;
    }
    int TerrainCount = sizeof(State.Terrains);
    for(int i=0;i<TerrainCount;i++){
        if(CheckCollisionsRectangles(State.avatar.get_pos(), State.Terrains[i].get_pos())){
            return true;
        }
    }
    return false;
}

Vector2 UpdateAvatar(Game State, int Width,int Height){
    int count=(Width*Height)/(20*21*21);
    if (IsKeyDown(KEY_D)){
        State.avatar.z.x +=4;
        if(State.avatar.z.x>Width-21)
            State.avatar.z.x -=4;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.x -=4;
        }
    }
    if (IsKeyDown(KEY_A)){
        State.avatar.z.x -=4;
        if(State.avatar.z.x<0)
            State.avatar.z.x +=4;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.x +=4;
        }
    }
    if (IsKeyDown(KEY_W)){
        State.avatar.z.y -= 4;
        if(State.avatar.z.y<0)
            State.avatar.z.y +=4;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.y +=4;
        }
    }
    if (IsKeyDown(KEY_S)){
        State.avatar.z.y += 4;
        if(State.avatar.z.y>Height-21)
            State.avatar.z.y -=4;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.y -=4;
        }
    }
    return State.avatar.z;
}

void UpdateEntities(Game State, int Width, int Height, int* WereCount, int* VampCount){
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
        }else if(State.werewolf[i].isDead==false){
            (*WereCount)--;
            State.werewolf[i].isDead=true;
        }
        if(State.vampire[i].get_health()>0){
            DrawTextureRec(State.Rectangles[i][1].texture, State.Rectangles[i][1].source, State.Rectangles[i][1].position, State.Rectangles[i][1].tint);
        }else if(State.vampire[i].isDead==false){
            (*VampCount)--;
            State.vampire[i].isDead=true;
        }
    }
}

void PauseGame(Game State, int Width, int Height, bool* pause,bool* FirstTime,Music music){
    string werecount = to_string((int)State.WereCount);
    string vampcount = to_string((int)State.VampCount);
    const char* vCount = vampcount.c_str();
    const char* wCount = werecount.c_str();
    DrawText("Game Paused",(Width/2)-(Width*0.13),Height/2,Width/25,RED);
    DrawText("If you want to Continue Press [ENTER]/[P]\nIf you want to Exit Press [X]/[ESCAPE]\nIf you want to Restart Press [R]",5,10,Width/36,WHITE);
    DrawText(wCount,0.25*Width,0.96*Height,Width/36,GOLD);
    DrawText("Werewolves left: ",0.012*Width,0.96*Height,Width/36,GOLD);
    DrawText(vCount,0.95*Width,0.96*Height,Width/36,PURPLE);
    DrawText("Vampires left: ",0.75*Width,0.96*Height,Width/36,PURPLE);
    if(IsKeyPressed(KEY_ENTER))*pause = false;
    if(IsKeyPressed(KEY_R)){
        *pause = false;
        *FirstTime = true;
        StopMusicStream(music);
        PlayMusicStream(music);
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

float VolumeCheck(float volume){
    if(IsKeyPressed(KEY_DOWN))volume = volume - 0.01;
    if(IsKeyPressed(KEY_UP))volume = volume + 0.01;

    return volume;
}

void EndGame(int Height,int Width,string winner){
    int pos = 0;int var = 0;
    if(winner == "Werewolves"){pos = (Width/2)-Width*0.25;var = 0.24*Width;}
    else{pos = (Width/2)-Width*0.2;var = 0.19*Width;}
    const char* Winners = winner.c_str();
    DrawText("Game is over !",(Width/2)-Width*0.13,Height/2,Width/25,RAYWHITE);
    DrawText(Winners,pos,Height/2-Height*0.1,Width/25,GOLD);
    DrawText("have Won !",pos+var,Height/2-Height*0.1,Width/25,GOLD);
}

void CreateWindow(int Width, int Height, const char* Team){
    int time=0;float volume = 0.08;
    bool pause = false;
    bool FirstTime=true;
    Game State(Width, Height);
    InitWindow(Width, Height, "Werewolves vs Vampires");
    SetTargetFPS(60);
    Texture2D WerewolfTexture, VampireTexture, AvatarTexture, TreeTexture, LakeTexture;
    Textures temp=LoadTextures(Team);
    InitAudioDevice();      // Initialize audio device
    Music music = LoadMusicStream("assets/Music.wav");         // Load WAV audio file
    WerewolfTexture=temp.T1;
    VampireTexture=temp.T2;
    AvatarTexture=temp.T3;
    TreeTexture = temp.T4;
    LakeTexture=temp.T5;
    PlayMusicStream(music);
    SetMasterVolume(volume);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        if(!IsMusicStreamPlaying(music)){
            PlayMusicStream(music);
        }
        if(FirstTime==true){
            State.Terrains = LoadTerrain(Width,Height,TreeTexture,LakeTexture);
            State.Rectangles=LoadEntites(Width, Height, WerewolfTexture, VampireTexture);
            State.avatar=LoadAvatar(Width, Height, AvatarTexture, Team);
            FirstTime=false;
            int count=(Width*Height)/(20*21*21);
        }
        if(IsKeyPressed(KEY_P) && State.VampCount>0 & State.WereCount>0){
            pause = !pause;
        }
        if(!pause){            
            UpdateMusicStream(music); SetMasterVolume(volume);
            if(State.VampCount<=0 || State.WereCount<=0 || IsKeyDown(KEY_NINE)){
                if(State.VampCount > State.WereCount){
                    EndGame(Height,Width,"Vampires");
                    StopMusicStream(music);
                }else{
                    EndGame(Height,Width,"Werewolves"); 
                    StopMusicStream(music); 
                }      
            }else{
                ResumeMusicStream(music);
                DayNightCycle(&time, Width, Height);
                UpdateEntities(State, Width, Height, &(State.WereCount), &(State.VampCount));
                State.avatar.set_pos(UpdateAvatar(State,Width,Height));
                DrawTextureRec(State.avatar.texture, {0.0f, 0.0f, 21.0f, 21.0f}, State.avatar.z, WHITE);
            }
        }else{
            PauseMusicStream(music);
            PauseGame(State, Width, Height, &pause,&FirstTime,music);    
        }
        volume = VolumeCheck(volume);
        EndDrawing();
    }
    UnloadMusicStream(music);   // Unload music stream buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
    CloseAudioDevice(); 
    CloseWindow();
    DeallocateMem(State, (Width*Height)/(20*21*21));
}
