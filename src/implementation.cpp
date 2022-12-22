#include "Classes.h"

Textures LoadTextures(const char* Team){
    const char *Werewolves="assets/Images/Werewolves.png";
    const char *Vampires="assets/Images/Vampires.png";
    const char *Avatar1="assets/Images/AvatarVamp.png";
    const char *Avatar2="assets/Images/AvatarWere.png";
    const char *Tree ="assets/Images/Tree.png";
    const char *Lake ="assets/Images/Lake.png";
    const char *Potion = "assets/Images/Potion.png";
    const char *A;
    Texture2D WerewolfSprite=LoadTexture(Werewolves);
    Texture2D VampireSprite=LoadTexture(Vampires);
    Texture2D TreeSprite = LoadTexture(Tree);
    Texture2D LakeSprite = LoadTexture(Lake);
    Texture2D PotionSprite = LoadTexture(Potion);
    if(!strcmp(Team, "Werewolves")){
        A=Avatar2;
    }else{
        A=Avatar1;
    }
    Texture2D AvatarSprite=LoadTexture(A);
    return {WerewolfSprite, VampireSprite,AvatarSprite,TreeSprite,LakeSprite,PotionSprite};
}

bool CheckCollisionsRectangles(Vector2 v1, Vector2 v2){
    bool collision=false;
    if(v1.x<v2.x+21 && v1.x+21>v2.x && v1.y<v2.y+21 && v1.y+21>v2.y)
        collision=true;
    return collision;
}

bool CheckCollisionTerrain(Game State,int number, int type,int TreeNum){
    for(int j = 0 ; j < TreeNum ; j++){
        if(CheckCollisionsRectangles(State.Rectangles[number][type].position,State.Terrains[j].GetPos()))
            return true;
        if(CheckCollisionsRectangles(State.Rectangles[number][type].position,State.potion.get_pos()))
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
                            Damage(State, number, i, State.werewolf->get_num(), State.vampire->get_num());
                        }
                        return 2;
                    }
                }
            }else if(type==1){
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].position, State.Rectangles[i][0].position)){
                        if(!Spawning){
                            Damage(State, i, number, State.werewolf->get_num(), State.vampire->get_num());
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
                            Damage(State, number, i, State.werewolf->get_num(), State.vampire->get_num());
                        }
                        return 2;
                    }
                }else if(type==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].position, State.Rectangles[i][0].position)){
                        if(!Spawning){
                            Damage(State, i, number, State.werewolf->get_num(), State.vampire->get_num());
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

Terrain* LoadTerrain(int Width,int Height,Texture2D TreeTex,Texture2D LakeTex, Vector2 PotPosition){
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
    T = new Terrain[total+1];
    for(int i=0;i<TreeCount;i++){
        T[i].SetTex(TreeTex);
        T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        while(CheckCollisionsRectangles(PotPosition,T[i].GetPos())){
            T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        }
        DrawTextureRec(T[i].GetTex(),T[i].Recta,T[i].GetPos(),WHITE);  
    }
    for(int i=TreeCount;i<total;i++){
        T[i].SetTex(LakeTex);
        T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        while(CheckCollisionsRectangles(PotPosition,T[i].GetPos())){
            T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        }
        DrawTextureRec(T[i].GetTex(),T[i].Recta,T[i].GetPos(),WHITE);
    }


    return T;
}

Potion LoadPotion(int Width,int Height,Texture2D PotionTex,Game State){
    Rectangle frameRec={0.0f, 0.0f, 21.0f, 21.0f};
    int TerrainCount = sizeof(State.Terrains);
    Vector2 SpritePosition={float(GetRandomValue(0.33*Width,0.55*Width)),float(GetRandomValue(0,Height/3+50))};
    Potion P;
    P.set_Tex(PotionTex);
    P.set_pos(SpritePosition);
    P.set_PotEx(true);
    DrawTextureRec(PotionTex, frameRec, SpritePosition, WHITE);
    return P;
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
    int TerrainCount = sizeof(State.Terrains);
    switch(z1){
        case 1:
            State.Rectangles[i][0].position.x+=State.Speed;
            if(State.Rectangles[i][0].position.x>Width-21 && State.Rectangles[i][0].position.x<Width+100)
                State.Rectangles[i][0].position.x=Width-21;
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.x-=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.x-=State.Speed;
            }
            break;
        case 2:
            State.Rectangles[i][0].position.x-=State.Speed;
            if(State.Rectangles[i][0].position.x<0)
                State.Rectangles[i][0].position.x=0;
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.x+=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.x+=State.Speed;
            }
            break;
        case 3:
            State.Rectangles[i][0].position.y+=State.Speed;
            if(State.Rectangles[i][0].position.y>Height-21 && State.Rectangles[i][0].position.y<Width+100)
                State.Rectangles[i][0].position.y=Height-21;
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.y-=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.y-=State.Speed;
            }
            break;
        case 4:
            State.Rectangles[i][0].position.y-=State.Speed;
            if(State.Rectangles[i][0].position.y<0)
                State.Rectangles[i][0].position.y=0;
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].position.y+=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].position.y+=State.Speed;
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
            State.Rectangles[i][1].position.x+=State.Speed;
            if(State.Rectangles[i][1].position.x>Width-21 && State.Rectangles[i][1].position.x<Width+100)
                State.Rectangles[i][1].position.x=Width-21;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x-=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x-=State.Speed;
            }
            break;
        case 2:
            State.Rectangles[i][1].position.x-=State.Speed;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x+=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x+=State.Speed;
            }
            break;
        case 3:
            State.Rectangles[i][1].position.y+=State.Speed;
            if(State.Rectangles[i][1].position.y>Height-21 && State.Rectangles[i][1].position.y<Width+100)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.y-=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x-=State.Speed;
            }
            break;
        case 4:
            State.Rectangles[i][1].position.y-=State.Speed;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.y+=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.y+=State.Speed;
            }
            break;
        case 5:
            State.Rectangles[i][1].position.x+=State.Speed;
            State.Rectangles[i][1].position.y+=State.Speed;
            if(State.Rectangles[i][1].position.x>Width-21 && State.Rectangles[i][1].position.x<Width+100)
                State.Rectangles[i][1].position.x=Width-21;
            if(State.Rectangles[i][1].position.y>Height-21 && State.Rectangles[i][1].position.y<Width+100)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x-=State.Speed;
                State.Rectangles[i][1].position.y-=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.y-=State.Speed;
                State.Rectangles[i][1].position.x-=State.Speed;
            }
            break;
        case 6:
            State.Rectangles[i][1].position.x+=State.Speed;
            State.Rectangles[i][1].position.y-=State.Speed;
            if(State.Rectangles[i][1].position.x>Width-21 && State.Rectangles[i][1].position.x<Width+100)
                State.Rectangles[i][1].position.x=Width-21;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x-=State.Speed;
                State.Rectangles[i][1].position.y+=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.y+=State.Speed;
                State.Rectangles[i][1].position.x-=State.Speed;
            }
            break;
        case 7:
            State.Rectangles[i][1].position.x-=State.Speed;
            State.Rectangles[i][1].position.y-=State.Speed;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(State.Rectangles[i][1].position.y<0)
                State.Rectangles[i][1].position.y=0;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x+=State.Speed;
                State.Rectangles[i][1].position.y+=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.y+=State.Speed;
                State.Rectangles[i][1].position.x+=State.Speed;
            }
            break;
        case 8:
            State.Rectangles[i][1].position.x-=State.Speed;
            State.Rectangles[i][1].position.y+=State.Speed;
            if(State.Rectangles[i][1].position.x<0)
                State.Rectangles[i][1].position.x=0;
            if(State.Rectangles[i][1].position.y>Height-21 && State.Rectangles[i][1].position.y<Width+100)
                State.Rectangles[i][1].position.y=Height-21;
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].position.x+=State.Speed;
                State.Rectangles[i][1].position.y-=State.Speed;
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].position.x+=State.Speed*2;
                State.Rectangles[i][1].position.y-=State.Speed*2;
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
        if(CheckCollisionsRectangles(State.avatar.get_pos(), State.Terrains[i].GetPos())){
            return true;
        }
    }
    return false;
}

void AOE_HEAL(int Width,int Height,Game State,int type){
    int count=(Width*Height)/(20*21*21);
    if(type == 0){
        for(int i = 0;i<count ;i++){
            if(State.werewolf[i].get_health()>0){
                State.werewolf[i].set_health(10);
            }
        }
    }
    else{
        for(int i = 0;i<count ;i++){
            if(State.vampire[i].get_health()>0){
                State.vampire[i].set_health(10);
            }
        }
    }
    
}

Vector2 UpdateAvatar(Game State, int Width,int Height,int* PotCount,float* Speed,Sound Heal){
    int count=(Width*Height)/(20*21*21);
    int type ;
    if (IsKeyDown(KEY_D)){
        State.avatar.z.x +=State.Speed/2;
        if(State.avatar.z.x>Width-21)
            State.avatar.z.x -=State.Speed/2;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.x -=State.Speed/2;
        }
    }
    if (IsKeyDown(KEY_A)){
        State.avatar.z.x -=State.Speed/2;
        if(State.avatar.z.x<0)
            State.avatar.z.x +=State.Speed/2;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.x +=State.Speed/2;
        }
    }
    if (IsKeyDown(KEY_W)){
        State.avatar.z.y -= State.Speed/2;
        if(State.avatar.z.y<0)
            State.avatar.z.y +=State.Speed/2;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.y +=State.Speed/2;
        }
    }
    if (IsKeyDown(KEY_S)){
        State.avatar.z.y += State.Speed/2;
        if(State.avatar.z.y>Height-21)
            State.avatar.z.y -=State.Speed/2;
        if(CheckAvatarCollisions(State,count)){
            State.avatar.z.y -=State.Speed/2;
        }
    }
    if(IsKeyPressed(KEY_H) && *PotCount>0){
        if(State.avatar.get_team() == "Werewolves")
            type = 0;
        else
            type = 1;    
        //heal and lower the Avatar's potion counter
        if(State.Time>150 && State.Time<301 && type == 0){    
            AOE_HEAL(Width,Height,State,type);
            SetSoundVolume(Heal , 3.5);
            PlaySound(Heal);
            *PotCount = *PotCount - 1;
        }
        else if(State.Time>0 && State.Time<151 && type == 1){
            AOE_HEAL(Width,Height,State,type);
            SetSoundVolume(Heal , 3.5);
            PlaySound(Heal);
            *PotCount = *PotCount - 1;
        }  
    }
    if(IsKeyPressed(KEY_PAGE_UP) && State.Speed < 9.5)
        *Speed += 1.0;
    if(IsKeyPressed(KEY_PAGE_DOWN) && State.Speed > 1.5)
        *Speed -= 1.0;

    return State.avatar.z;
}

void UpdateEntities(Game State, int Width, int Height, int* WereCount, int* VampCount,bool* PotionExistance,int* avatarsPot,Sound Pickup){
    int count=(Width*Height)/(20*21*21);
    int TerrainCount = sizeof(State.Terrains);
    for(int i=0;i<TerrainCount;i++){
        DrawTextureRec(State.Terrains[i].GetTex(),{0.0f, 0.0f, 21.0f, 21.0f},State.Terrains[i].GetPos(),WHITE);
    }
    for(int i=0;i<count;i++){
        MoveWerewolves(State, Width, Height, i, count);
        MoveVampires(State, Width, Height, i, count);
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
    if(!CheckCollisionsRectangles(State.avatar.z,State.potion.get_pos()) && *PotionExistance == true){
        DrawTextureRec(State.potion.get_Tex(), {0.0f, 0.0f, 21.0f, 21.0f}, State.potion.get_pos(), WHITE);
    }
    else{
        if(*avatarsPot == 1 && *PotionExistance == true){
            PlaySound(Pickup);
            *PotionExistance = false;
            *avatarsPot = 2;
        }else if(*avatarsPot == 0 && *PotionExistance == true){
            PlaySound(Pickup);
            *PotionExistance = false;
            *avatarsPot = 1;
        }
    }
 
}

void PauseGame(Game State, int Width, int Height, bool* pause,bool* FirstTime,Music music){
    string werecount = to_string((int)*State.werewolf->get_num());
    string vampcount = to_string((int)*State.vampire->get_num());
    string potionCount = to_string((int)State.avatar.get_pot());
    const char* wCount = werecount.c_str();
    const char* vCount = vampcount.c_str();
    const char* pCount = potionCount.c_str();
    DrawText("Game Paused",(Width/2)-(Width*0.13),Height/2,Width/25,RED);
    DrawText("If you want to Continue Press [ENTER]/[P]\nIf you want to Exit Press [X]/[ESCAPE]\nIf you want to Restart Press [R]",5,10,Width/36,WHITE);
    DrawText(wCount,0.25*Width,0.96*Height,Width/36,GOLD);
    DrawText("Werewolves left: ",0.012*Width,0.96*Height,Width/36,GOLD);
    DrawText(vCount,0.95*Width,0.96*Height,Width/36,PURPLE);
    DrawText("Vampires left: ",0.75*Width,0.96*Height,Width/36,PURPLE);
    DrawText("Potions Left: ",0.41*Width,0.96*Height,Width/36,RED);
    DrawText(pCount,0.6*Width,0.96*Height,Width/36,RED);
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
    if(IsKeyPressed(KEY_DOWN))volume-=0.01;
    if(IsKeyDown(KEY_DOWN))volume-=0.005;
    if(IsKeyDown(KEY_UP))volume +=0.005;
    if(IsKeyPressed(KEY_UP))volume+=0.01;
    if(IsKeyPressed(KEY_M))volume = 0.0;
    if(volume < 0.0)
        return 0.0;
    else        
        return volume;
}

void EndGame(int Height,int Width,string winner){
    int pos = 0;int var = 0;Color color = WHITE;
    if(winner == "Werewolves"){pos = (Width/2)-Width*0.25;var = 0.25*Width;color = GOLD;}
    else{pos = (Width/2)-Width*0.2;var = 0.2*Width;color = PURPLE;}
    const char* Winners = winner.c_str();
    DrawText("Game is over !",(Width/2)-Width*0.13,Height/2,Width/25,RAYWHITE);
    DrawText(Winners,pos,Height/2-Height*0.1,Width/25,color);
    DrawText("have Won !",pos+var,Height/2-Height*0.1,Width/25,color);
}

void CreateWindow(int Width, int Height, const char* Team){
    float volume = 0.01;
    bool pause = false;
    bool FirstTime=true;
    Game State(Width, Height);
    InitWindow(Width, Height, "Werewolves vs Vampires");
    SetTargetFPS(60);
    Texture2D WerewolfTexture, VampireTexture, AvatarTexture, TreeTexture, LakeTexture,PotionTexture;
    Textures temp=LoadTextures(Team);
    InitAudioDevice();      // Initialize audio device
    Music music = LoadMusicStream("assets/Sounds/Music.wav");         // Load WAV audio file
    Sound PotionSound = LoadSound("assets/Sounds/PotionPickup.wav");
    Sound HealSound = LoadSound("assets/Sounds/AOE_Heal.wav");
    WerewolfTexture=temp.T1;
    VampireTexture=temp.T2;
    AvatarTexture=temp.T3;
    TreeTexture = temp.T4;
    LakeTexture=temp.T5;
    PotionTexture = temp.T6;
    PlayMusicStream(music);
    SetMasterVolume(volume);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        volume = VolumeCheck(volume);
        if(!IsMusicStreamPlaying(music)){
            PlayMusicStream(music);
        }
        if(FirstTime==true){
            State.potion = LoadPotion(Width,Height,PotionTexture,State);
            State.Terrains = LoadTerrain(Width,Height,TreeTexture,LakeTexture,State.potion.get_pos());
            State.Rectangles=LoadEntites(Width, Height, WerewolfTexture, VampireTexture);
            State.avatar=LoadAvatar(Width, Height, AvatarTexture, Team);
            int count=(Width*Height)/(20*21*21);
            *State.vampire->get_num()=count;
            *State.werewolf->get_num()=count;
            for(int i=0;i<count;i++){
                State.werewolf[i].isDead=false;
                State.vampire[i].isDead=false;
            }
            FirstTime=false;
        }
        if(IsKeyPressed(KEY_P) && *State.vampire->get_num()>0 & *State.werewolf->get_num()>0){
            pause = !pause;
        }
        if(!pause){            
            UpdateMusicStream(music); SetMasterVolume(volume);
            if(*State.vampire->get_num()<=0 || *State.werewolf->get_num()<=0){
                if(*State.vampire->get_num() > *State.werewolf->get_num()){
                    EndGame(Height,Width,"Vampires");
                    StopMusicStream(music);
                }else{
                    EndGame(Height,Width,"Werewolves"); 
                    StopMusicStream(music); 
                }
                if(IsKeyPressed(KEY_R)){
                    FirstTime = true;
                    StopMusicStream(music);
                    PlayMusicStream(music);
                    int count=(Width*Height)/(20*21*21);
                    for(int i=0; i<count; i++){
                        State.vampire[i].set_health(10);
                        State.werewolf[i].set_health(10);
                    }
                }       
            }else{
                ResumeMusicStream(music);
                DayNightCycle(&State.Time, Width, Height);
                State.avatar.set_pos(UpdateAvatar(State,Width,Height,State.avatar.potisource(),&(State.Speed),HealSound));
                UpdateEntities(State, Width, Height, State.werewolf->get_num(), State.vampire->get_num(),State.potion.DoesPotExist(),State.avatar.potisource(),PotionSound);
                DrawTextureRec(State.avatar.texture, {0.0f, 0.0f, 21.0f, 21.0f}, State.avatar.z, WHITE);
            }
        }else{
            PauseMusicStream(music);
            PauseGame(State, Width, Height, &pause,&FirstTime,music);    
        }

        EndDrawing();
    }
    UnloadMusicStream(music);   // Unload music stream buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
    CloseAudioDevice(); 
    CloseWindow();
    DeallocateMem(State, (Width*Height)/(20*21*21));
}
