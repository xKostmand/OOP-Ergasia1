#include "Functions.h"

bool CheckCollisionsRectangles(Vector2 v1, Vector2 v2){         //almost the same as a raylib function that deals with collision checking(if a rectangle is inside or outside another rectangle)
    bool collision=false;
    if(v1.x<v2.x+21 && v1.x+21>v2.x && v1.y<v2.y+21 && v1.y+21>v2.y)
        collision=true;
    return collision;
}

bool CheckCollisionTerrain(Game State,int number, int type,int TreeNum){        //check if a given entity is colliding with either terrain(trees, water) or the potion)
    for(int j = 0 ; j < TreeNum ; j++){
        if(CheckCollisionsRectangles(State.Rectangles[number][type].get_pos(),State.Terrains[j].GetPos()))
            return true;
        if(CheckCollisionsRectangles(State.Rectangles[number][type].get_pos(),State.potion.get_pos()))
            return true;
    }
    return false;    
}

bool CheckAvatarCollisions(Game State, int count){
    for(int i=0;i<count;i++){       //check the user's collisions for the entities and the terrain
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

int CheckCollisions(Game State, int number, int count, int type, int CheckWithOther, int Spawning){     //checks collisions for entities(werewolves, vampires)
    for(int i=0;i<count;i++){                                                                           //and manages what happens after the collision(heal teammate, damage other)
        if(i!=number){
            if(type==0){
                if(CheckCollisionsRectangles(State.Rectangles[number][0].get_pos(), State.Rectangles[i][0].get_pos())){
                    if(!Spawning){      //flag that checks if entities are spawning in the window or not
                        HealTeammate(State, number, i, type);   //if type: 0=werewolf, 1=vampire
                    }                                           //for example, if type=0, werewolf[number], heals werewolf[i]
                    return 1;
                }
                if(CheckWithOther==1){
                    if(CheckCollisionsRectangles(State.Rectangles[number][0].get_pos(), State.Rectangles[i][1].get_pos())){
                        if(!Spawning){
                            Damage(State, number, i, State.werewolf->get_num(), State.vampire->get_num());      //werewolf[number] damages vampire[i] or the opposite, it depends from their damage stat
                        }                                                                                       //get_num gives how many entities from the specified team are alive
                        return 2;                                                                               //same goes for the rest of the function
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
        if(State.werewolf[i].get_health()!=10){
            int temp=GetRandomValue(0,1);
            if(temp==0){
                return;
            }else{
                if(State.werewolf[number].get_pot()!=0){        //one entity uses its potion(if he still has one)
                    State.werewolf[number].usepotion();         //other entity heals up 1 HP
                    State.werewolf[i].healup();
                }
            }
        }else if(State.werewolf[number].get_health()!=10){
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
        if(State.vampire[i].get_health()!=10){
            int temp=GetRandomValue(0,1);
            if(temp==0){
                return;
            }else{
                if(State.vampire[number].get_pot()!=0){
                    State.vampire[number].usepotion();
                    State.vampire[i].healup();
                }
            }
        }else if(State.vampire[number].get_health()!=10){
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

void AOE_HEAL(int Width,int Height,Game State,int type){        //this function heals all alive entities from the users team
    int count=(Width*Height)/(20*21*21);
    if(type == 0){
        for(int i = 0;i<count ;i++){
            if(State.werewolf[i].get_health()>0){
                State.werewolf[i].add_health(3);
            }
        }
    }
    else{
        for(int i = 0;i<count ;i++){
            if(State.vampire[i].get_health()>0){
                State.vampire[i].add_health(3);
            }
        }
    }
    
}

void Damage(Game State, int number, int i, int* WereCount, int* VampCount){             //function that deals with damaging which depends from the damage stat of each entity
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

void DayNightCycle(int* time, int Width, int Height){           //Updates the day-night cycle of the game and draws it ingame
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
