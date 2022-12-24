#include "Functions.h"

void MoveWerewolves(Game State, int Width,int Height, int i, int count){        //moves a werewolf entity using the GetRandomValue(int x, int y) functions that returns a int number in [x,y]
    int z1=GetRandomValue(1,4);     //1=move right, 2=move left, 3=move up, 4=move down
    int TerrainCount = sizeof(State.Terrains);
    switch(z1){
        case 1:
            State.Rectangles[i][0].setx(State.Speed);
            if(State.Rectangles[i][0].get_x()>Width-21 && State.Rectangles[i][0].get_x()<Width+100)
                State.Rectangles[i][0].setx(Width - 21);
            if(CheckCollisions(State,i,count,0,1,0)){               //if by moving it collided with somehting "rewind" its movement and continue
                State.Rectangles[i][0].setx(-State.Speed);          //same in other cases and with vampires(just with more cases)
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].setx(-State.Speed);
            }
            break;
        case 2:
            State.Rectangles[i][0].setx(-State.Speed);
            if(State.Rectangles[i][0].get_x()<0)
                State.Rectangles[i][0].setx(0);
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].setx(State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].setx(State.Speed);
            }
            break;
        case 3:
            State.Rectangles[i][0].sety(State.Speed);
            if(State.Rectangles[i][0].get_y()>Height-21 && State.Rectangles[i][0].get_y()<Width+100)
                State.Rectangles[i][0].sety(Height - 21);
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].sety(-State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].sety(-State.Speed);
            }
            break;
        case 4:
            State.Rectangles[i][0].sety(-State.Speed);
            if(State.Rectangles[i][0].get_y()<0)
                State.Rectangles[i][0].sety(0);
            if(CheckCollisions(State,i,count,0,1,0)){
                State.Rectangles[i][0].sety(State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,0,TerrainCount)){
                State.Rectangles[i][0].sety(State.Speed);
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
            State.Rectangles[i][1].setx(State.Speed);
            if(State.Rectangles[i][1].get_x()>Width-21 && State.Rectangles[i][1].get_x()<Width+100)
                State.Rectangles[i][1].setx(Width - 21);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].setx(-State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].setx(-State.Speed);
            }
            break;
        case 2:
            State.Rectangles[i][1].setx(-State.Speed);
            if(State.Rectangles[i][1].get_x()<0)
                State.Rectangles[i][1].setx(0);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].setx(State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].setx(State.Speed);
            }
            break;
        case 3:
            State.Rectangles[i][1].sety(State.Speed);
            if(State.Rectangles[i][1].get_y()>Height-21 && State.Rectangles[i][1].get_y()<Width+100)
                State.Rectangles[i][1].sety(Height - 21);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].sety(-State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].sety(-State.Speed);
            }
            break;
        case 4:
            State.Rectangles[i][1].sety(-State.Speed);
            if(State.Rectangles[i][1].get_y()<0)
                State.Rectangles[i][1].sety(0);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].sety(State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].sety(State.Speed);
            }
            break;
        case 5:
            State.Rectangles[i][1].setx(State.Speed);
            State.Rectangles[i][1].sety(State.Speed);
            if(State.Rectangles[i][1].get_x()>Width-21 && State.Rectangles[i][1].get_x()<Width+100)
                State.Rectangles[i][1].setx(Width-21);
            if(State.Rectangles[i][1].get_y()>Height-21 && State.Rectangles[i][1].get_y()<Width+100)
                State.Rectangles[i][1].sety(Height - 21);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].sety(-State.Speed);
                State.Rectangles[i][1].setx(-State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].sety(-State.Speed);
                State.Rectangles[i][1].setx(-State.Speed);
            }
            break;
        case 6:
            State.Rectangles[i][1].setx(State.Speed);
            State.Rectangles[i][1].sety(-State.Speed);
            if(State.Rectangles[i][1].get_x()>Width-21 && State.Rectangles[i][1].get_x()<Width+100)
                State.Rectangles[i][1].setx(Width - 21);
            if(State.Rectangles[i][1].get_y()<0)
                State.Rectangles[i][1].sety(0);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].setx(-State.Speed);
                State.Rectangles[i][1].sety(State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].sety(State.Speed);
                State.Rectangles[i][1].setx(-State.Speed);
            }
            break;
        case 7:
            State.Rectangles[i][1].setx(-State.Speed);
            State.Rectangles[i][1].sety(-State.Speed);
            if(State.Rectangles[i][1].get_x()<0)
                State.Rectangles[i][1].setx(0);
            if(State.Rectangles[i][1].get_y()<0)
                State.Rectangles[i][1].sety(0);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].setx(State.Speed);
                State.Rectangles[i][1].sety(State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].sety(State.Speed);
                State.Rectangles[i][1].setx(State.Speed);
            }
            break;
        case 8:
            State.Rectangles[i][1].setx(-State.Speed);
            State.Rectangles[i][1].sety(State.Speed);
            if(State.Rectangles[i][1].get_x()<0)
                State.Rectangles[i][1].setx(0);
            if(State.Rectangles[i][1].get_y()>Height-21 && State.Rectangles[i][1].get_y()<Width+100)
                State.Rectangles[i][1].sety(Height - 21);
            if(CheckCollisions(State,i,count,1,1,0)){
                State.Rectangles[i][1].setx(State.Speed);
                State.Rectangles[i][1].sety(-State.Speed);
            }
            else if(CheckCollisionTerrain(State,i,1,TerrainCount)){
                State.Rectangles[i][1].setx(State.Speed);
                State.Rectangles[i][1].sety(-State.Speed);
            }
            break;
        default:
            break;
    }
}

Vector2 UpdateAvatar(Game State, int Width,int Height,int* PotCount,float* Speed,Sound Heal){       //controls all avatar features(movement, heal team)
    int count=(Width*Height)/(20*21*21);
    int type;
    float avatarSpeed = (*Speed)*0.8;

    if (IsKeyDown(KEY_D)){
        State.avatar.set_pos({State.avatar.get_pos().x+avatarSpeed,State.avatar.get_pos().y});
        if(State.avatar.get_pos().x>Width-21)
            State.avatar.set_pos({State.avatar.get_pos().x-avatarSpeed,State.avatar.get_pos().y});
        if(CheckAvatarCollisions(State,count)){
            State.avatar.set_pos({State.avatar.get_pos().x-avatarSpeed,State.avatar.get_pos().y});
        }
    }
    if (IsKeyDown(KEY_A)){
        State.avatar.set_pos({State.avatar.get_pos().x-avatarSpeed,State.avatar.get_pos().y});
        if(State.avatar.get_pos().x<0)
            State.avatar.set_pos({State.avatar.get_pos().x+avatarSpeed,State.avatar.get_pos().y});
        if(CheckAvatarCollisions(State,count)){
            State.avatar.set_pos({State.avatar.get_pos().x+avatarSpeed,State.avatar.get_pos().y});
        }
    }
    if (IsKeyDown(KEY_W)){
        State.avatar.set_pos({State.avatar.get_pos().x,State.avatar.get_pos().y-avatarSpeed});
        if(State.avatar.get_pos().y<0)
            State.avatar.set_pos({State.avatar.get_pos().x,State.avatar.get_pos().y+avatarSpeed});
        if(CheckAvatarCollisions(State,count)){
            State.avatar.set_pos({State.avatar.get_pos().x,State.avatar.get_pos().y+avatarSpeed});
        }
    }
    if (IsKeyDown(KEY_S)){
        State.avatar.set_pos({State.avatar.get_pos().x,State.avatar.get_pos().y+avatarSpeed});
        if(State.avatar.get_pos().y>Height-21)
            State.avatar.set_pos({State.avatar.get_pos().x,State.avatar.get_pos().y-avatarSpeed});
        if(CheckAvatarCollisions(State,count)){
            State.avatar.set_pos({State.avatar.get_pos().x,State.avatar.get_pos().y-avatarSpeed});
        }
    }
    if(IsKeyPressed(KEY_H) && *PotCount>0){
        if(State.avatar.get_team() == "Werewolves")
            type = 0;
        else
            type = 1;    
        //heal and lower the Avatar's potion counter
        if(State.Time>150 && State.Time<301 && type == 0){    //heal avatar's team only if its the correct time
            AOE_HEAL(Width,Height,State,type);                //0-150=day, 151-300=night
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
    if(IsKeyPressed(KEY_PAGE_UP) && State.Speed < 9.5)          //by pressing these buttons it increases/decreases the speed in which the entities move
        *Speed += 1.0;
    if(IsKeyPressed(KEY_PAGE_DOWN) && State.Speed > 1.5)
        *Speed -= 1.0;

    return State.avatar.get_pos();
}

void UpdateEntities(Game State, int Width, int Height, int* WereCount, int* VampCount,bool* PotionExistance,int* avatarsPot,Sound Pickup){      //updates ALL entites and draws them in our window
    int count=(Width*Height)/(20*21*21);
    int TerrainCount = sizeof(State.Terrains);
    for(int i=0;i<TerrainCount;i++){
        DrawTextureRec(State.Terrains[i].GetTex(),{0.0f, 0.0f, 21.0f, 21.0f},State.Terrains[i].GetPos(),WHITE);     //raylib function which draws in our window
    }                                                                                                               //using the specified texture, rectangle from the asset, position and color
    for(int i=0;i<count;i++){
        MoveWerewolves(State, Width, Height, i, count);
        MoveVampires(State, Width, Height, i, count);
        DrawTextureRec(State.avatar.get_texture(), {0.0f, 0.0f, 21.0f, 21.0f}, State.avatar.get_pos(), WHITE);
        if(State.werewolf[i].get_health()>0){
            DrawTextureRec(State.Rectangles[i][0].get_texture(), State.Rectangles[i][0].get_rect(), State.Rectangles[i][0].get_pos(), State.Rectangles[i][0].get_tint());       //only draw entities if their hp is >0
        }else if(State.werewolf[i].isDead==false){
            (*WereCount)--;
            State.werewolf[i].isDead=true;
        }
        if(State.vampire[i].get_health()>0){
            DrawTextureRec(State.Rectangles[i][1].get_texture(), State.Rectangles[i][1].get_rect(), State.Rectangles[i][1].get_pos(), State.Rectangles[i][1].get_tint());
        }else if(State.vampire[i].isDead==false){
            (*VampCount)--;
            State.vampire[i].isDead=true;
        }
    }
    if(!CheckCollisionsRectangles(State.avatar.get_pos(),State.potion.get_pos()) && *PotionExistance == true){      //only draw potion if avatar hasnt picked it up
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
