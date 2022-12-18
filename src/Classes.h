#pragma once
#include <iostream>
#include <string.h>
#include <ctime>
#include <limits>
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "implementation.h"

using namespace std;

#define INF std::numeric_limits<float>::infinity()

class Position{
    private:
        float x;
        float y;
    public:
        Position(){}
        Position(float x1, float y1):x(x1), y(y1){}
        //Position(Position z):x(z.x), y(z.y){}
        void set_x(float x1){
            x=x1;
        }
        void set_y(float y1){
            y=y1;
        }
        float get_x() const {
            return x;
        }
        float get_y() const {
            return y;
        }
};

class Rec{
    public:
        Texture2D texture;
        Rectangle source;
        Vector2 position;
        Color tint;
/*    public:
        Texture2D get_texture(){
            return texture;
        }
        Rectangle get_rect(){
            return source;
        }
        Vector2 get_pos(){
            return position;
        }
        Color get_tint(){
            return tint;
        }
        float get_x(){
            return position.x;
        }
        float get_y(){
            return position.y;
        }
        */
};

class Textures{
    public:
        Texture2D T1;
        Texture2D T2;
        Texture2D T3;
        Texture2D T4;
        Texture2D T5;
};

class Potion{
    private:
        Position position;
    public:
        Potion(){}
        Potion(Position z):position(z){}
        Position get_pos(){
            return position;
        }
};

class Entity{
    protected:
        string name;
        int PotionCount;
    public:
        string get_name(){
            return name;
        }
        int get_pot(){
            return PotionCount;
        }
        void usepotion(){
            PotionCount--;
        }
};

class Avatar: public Entity{
    public:
        const char* Team;
        Texture2D texture;
        Vector2 z;
    public:
        Avatar(){
            name="Avatar";
            PotionCount=1;
        }
        string get_team(){
            return Team;
        }
        void set_team(const char* T){
            Team=T;
        }
        Texture2D get_texture(){
            return texture;
        }
        void set_texture(Texture2D T){
            texture=T;
        }
        Vector2 get_pos(){
            return z;
        }
        void set_pos(Vector2 z1){
            z=z1;
        }
};

class Werewolf: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:
        Werewolf(){
            name="Werewolf";
            PotionCount=GetRandomValue(0,2);
            Health=10;
            Damage=GetRandomValue(1,3);
            Defense=GetRandomValue(1,2);
        }
        int get_health(){
            return Health;
        }
        int get_damage(){
            return Damage;
        }
        int get_defense(){
            return Defense;
        }
        void healup(){
            Health++;
        }
        void set_health(int x){
            Health=x;
        }
};

class Vampire: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:
        Vampire(){
            name="Vampire";
            PotionCount=GetRandomValue(0,2);
            Health=10;
            Damage=GetRandomValue(1,3);
            Defense=GetRandomValue(1,2);
        }
        int get_health(){
            return Health;
        }
        int get_damage(){
            return Damage;
        }
        int get_defense(){
            return Defense;
        }
        void healup(){
            Health++;
        }
        void set_health(int x){
            Health=x;
        }
};

class Terrain{
    public:
        Texture2D texture;
        Vector2 TerPos;
        Rectangle Recta;
        Color tint;
        Terrain(){
            tint = WHITE;
        }
        Color GetCol(){return tint;}
        void SetCol(Color code){tint = code;}
        Vector2 get_pos(){
            return TerPos;
        }
        void set_pos(Vector2 z1){
            TerPos=z1;
        }
};


typedef Terrain Lake;
typedef Terrain Tree;

class Game{
    public:
        Rec** Rectangles;
        Avatar avatar;
        Werewolf* werewolf;
        Vampire* vampire;
        Potion potion;
        Terrain *Terrains;
        //int* WereCount;
        //int* VampCount;
    public:
        Game(int Width, int Height){
            int count=(Width*Height)/(20*21*21);
            Vampire* V=new Vampire[count];
            Werewolf* W=new Werewolf[count];
            this->vampire=V;
            this->werewolf=W;
            //*WereCount=*VampCount=count;
        }
        Game(){}
};
