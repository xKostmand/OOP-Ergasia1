#include "Functions.h"

//loads all of the required textures and stores them in the Textures class
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

//initializes all entities from both teams at a random location in their specified location(werewolves left, vampires right)
//Rec**: top row=for werewolves, bottom row=for vampires
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
        while(CheckCollisions(State, i, i, 0, 0, 1)){                       //if an entity spawns and its colliding with another entity, try and reposition it
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
//Initializes the terrain (Water/Trees) and stores them in a table with Terrains
Terrain* LoadTerrain(int Width,int Height,Texture2D TreeTex,Texture2D LakeTex, Vector2 PotPosition){
    Rectangle frameRec={0.0, 0.0, 21.0, 21.0};
    int TreeCount;
    int LakeCount;
    int total = 0;
    //For Heights < 750 we create a total of 4 Terrains(2 Lakes/2 Trees)
    //For Heights > 750 we create a total of 8 Terrains(4 Lakes/4 Trees)
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
    //for every member of the Terrain Table we set the Texture and we choose a 
    //random position Checking for Collision with the Potion every time
    //We skip the collision with each other using specific spacing for each Terrain Entity
    for(int i=0;i<TreeCount;i++){
        T[i].SetTex(TreeTex);
        T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        while(CheckCollisionsRectangles(PotPosition,T[i].GetPos())){
            T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        }
        DrawTextureRec(T[i].GetTex(),{0.0,0.0,21.0,21.0},T[i].GetPos(),WHITE);  
    }
    for(int i=TreeCount;i<total;i++){
        T[i].SetTex(LakeTex);
        T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        while(CheckCollisionsRectangles(PotPosition,T[i].GetPos())){
            T[i].SetPos({float(GetRandomValue(0.33*Width,0.55*Width)),float(Height/2-i*50)});
        }
        DrawTextureRec(T[i].GetTex(),{0.0,0.0,21.0,21.0},T[i].GetPos(),WHITE);
    }

    //We return the position of the table which we want in the Game Class
    return T;
}

//Initializes the Potion Entity (texture, position, Draw)
Potion LoadPotion(int Width,int Height,Texture2D PotionTex,Game State){     
    Rectangle frameRec={0.0f, 0.0f, 21.0f, 21.0f};
    int TerrainCount = sizeof(State.Terrains);
    Vector2 SpritePosition={float(GetRandomValue(0.33*Width,0.55*Width)),float(GetRandomValue(0,Height/3+50))};
    //We create a temporary Potion Variable that we later return and store in the Game Class
    Potion P;
    P.set_Tex(PotionTex);
    P.set_pos(SpritePosition);
    P.set_PotEx(true);
    DrawTextureRec(PotionTex, frameRec, SpritePosition, WHITE);
    return P;
}
//Initializes the Avatar Entity (Texture,start position, Draw)
Avatar LoadAvatar(int Width, int Height, Texture2D AvatarTexture, const char* Team){
    Rectangle frameRec={0.0f, 0.0f, 21.0f, 21.0f};
    Vector2 SpritePosition={float(Width/2), float(0.9*Height)};
    //We create a temporary Potion Variable that we later return and store in the Game Class
    Avatar A;
    A.set_team(Team);
    A.set_texture(AvatarTexture);
    A.set_pos(SpritePosition);
    DrawTextureRec(AvatarTexture, frameRec, SpritePosition, WHITE);
    return A;
}
