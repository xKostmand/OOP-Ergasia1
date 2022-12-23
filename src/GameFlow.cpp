#include "Functions.h"

void DeallocateMem(Game State, int count){
    for(int i=0; i<count; i++){
        delete [] State.Rectangles[i];
    }
    delete [] State.Rectangles;
    delete [] State.werewolf;
    delete [] State.vampire;
    delete [] State.Terrains;
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
    float volume = 0.04;
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
            State.vampire->set_num(count);
            State.werewolf->set_num(count);
            //*State.werewolf->get_num()=count;
            State.Speed=5.0;
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
                DrawTextureRec(State.avatar.get_texture(), {0.0f, 0.0f, 21.0f, 21.0f}, State.avatar.get_pos(), WHITE);
            }
        }else{
            PauseMusicStream(music);
            PauseGame(State, Width, Height, &pause,&FirstTime,music);    
        }

        EndDrawing();
    }
    UnloadSound(PotionSound);
    UnloadSound(HealSound);
    UnloadMusicStream(music);   // Unload music stream buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
    CloseWindow();
    DeallocateMem(State, (Width*Height)/(20*21*21));
}