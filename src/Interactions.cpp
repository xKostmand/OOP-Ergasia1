#include "Functions.h"

bool CheckCollisionsRectangles(Vector2 v1, Vector2 v2){
    bool collision=false;
    if(v1.x<v2.x+21 && v1.x+21>v2.x && v1.y<v2.y+21 && v1.y+21>v2.y)
        collision=true;
    return collision;
}

bool CheckCollisionTerrain(Game State,int number, int type,int TreeNum){
    for(int j = 0 ; j < TreeNum ; j++){
        if(CheckCollisionsRectangles(State.Rectangles[number][type].get_pos(),State.Terrains[j].GetPos()))
            return true;
        if(CheckCollisionsRectangles(State.Rectangles[number][type].get_pos(),State.potion.get_pos()))
            return true;
    }
    return false;    
}

bool CheckAvatarCollisions(Game State, int count){
    for(int i=0;i<count;i++){
        if(CheckCollisionsRectangles(State.avatar.get_pos(), State.Rectangles[i][0].get_pos()) || CheckCollisionsRectangles(State.avatar.get_pos(), State.Rectangles[i][1].get_pos()))
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

int CheckCollisions(Game State, int number, int count, int type, int CheckWithOther, int Spawning){
    for(int i=0;i<count;i++){
        if(i!=number){
            if(type==0){
                if(CheckCollisionsRectangles(State.Rectangles[number][0].get_pos(), State.Rectangles[i][0].get_pos())){
                    if(!Spawning){
                        HealTeammate(State, number, i, type);
                    }
                    return 1;
                }
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][0].get_pos(), State.Rectangles[i][1].get_pos())){
                        if(!Spawning){
                            Damage(State, number, i, State.werewolf->get_num(), State.vampire->get_num());
                        }
                        return 2;
                    }
                }
            }else if(type==1){
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].get_pos(), State.Rectangles[i][0].get_pos())){
                        if(!Spawning){
                            Damage(State, i, number, State.werewolf->get_num(), State.vampire->get_num());
                        }
                        return 2;
                    }
                }
                if(CheckCollisionsRectangles(State.Rectangles[number][1].get_pos(), State.Rectangles[i][1].get_pos())){
                    if(!Spawning){
                        HealTeammate(State, number, i, type);
                    }
                    return 3;
                }
            }
        }else{
            if(CheckWithOther==1){
                if(type==0){
                    if(CheckCollisionsRectangles(State.Rectangles[number][0].get_pos(), State.Rectangles[i][1].get_pos())){
                        if(!Spawning){
                            Damage(State, number, i, State.werewolf->get_num(), State.vampire->get_num());
                        }
                        return 2;
                    }
                }else if(type==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][1].get_pos(), State.Rectangles[i][0].get_pos())){
                        if(!Spawning){
                            Damage(State, i, number, State.werewolf->get_num(), State.vampire->get_num());
                        }
                        return 2;
                    }
                }
            }
        }
    }
    if(CheckCollisionsRectangles(State.Rectangles[number][type].get_pos(), State.avatar.get_pos())){
        return 4;
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

void AOE_HEAL(int Width,int Height,Game State,int type){
    int count=(Width*Height)/(20*21*21);
    if(type == 0){
        for(int i = 0;i<count ;i++){
            if(State.werewolf[i].get_health()>0){
                State.werewolf[i].set_health(3);
            }
        }
    }
    else{
        for(int i = 0;i<count ;i++){
            if(State.vampire[i].get_health()>0){
                State.vampire[i].set_health(3);
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
            State.Rectangles[i][1].setpos({INF, INF});
        }
    }else if(State.werewolf[number].get_damage() < State.vampire[i].get_damage()){
        int Damage=State.vampire[i].get_damage() - State.werewolf[number].get_defense();
        if(Damage<0){
            Damage=0;
        }
        State.werewolf[number].set_health(State.werewolf[number].get_health() - Damage);
        if(State.werewolf[number].get_health() <= 0){
            State.Rectangles[number][0].setpos({INF/2, INF/2});
        }
    }else{
        int Damage1=State.werewolf[number].get_damage() - State.vampire[i].get_defense();
        if(Damage1<0){
            Damage1=0;
        }
        State.vampire[i].set_health(State.vampire[i].get_health() - Damage1);
        if(State.vampire[i].get_health() <= 0){
            State.Rectangles[i][1].setpos({INF, INF});
        }
        int Damage2=State.vampire[i].get_damage() - State.werewolf[number].get_defense();
        if(Damage2<0){
            Damage2=0;
        }
        State.werewolf[number].set_health(State.werewolf[number].get_health() - Damage2);
        if(State.werewolf[number].get_health() <= 0){
            State.Rectangles[number][0].setpos({INF/2, INF/2});
        }
    }
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
