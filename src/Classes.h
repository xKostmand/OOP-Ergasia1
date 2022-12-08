#pragma once
#include <iostream>
#include <string.h>
#include <ctime>
#include "raylib.h"
#include "raymath.h"
#include "implementation.h"

using namespace std;

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
        Werewolf(int HP, int Dmg, int Def){
            Health=HP;
            Damage=Dmg;
            Defense=Def;
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
};

class Vampire: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:
        Vampire(int HP, int Dmg, int Def){
            Health=HP;
            Damage=Dmg;
            Defense=Def;
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
};

class Terrain{
    private:
        Position position;
    public:
        Terrain(Position z):position(z){}   //Initialize using Terrain var({x1, x2});
        Position get_pos(){
            return position;
        }
};

typedef Terrain Water;
typedef Terrain Tree;

class Game{
    public:
        Rec** Rectangles;
        Avatar avatar;
        Werewolf* werewolf;
        Vampire* vampire;
        Potion potion;
//        Water water[3];
//        Tree tree[3];
    public:
        Game(){}
/*        Game(Rec** R, Avatar A, Werewolf* W, Vampire* V, Potion P, Water Wa[3], Tree T[3]):Rectangles(R), avatar(A), werewolf(W), vampire(V), potion(P){
            for(int i=0;i<3;i++){
                water[i]=Wa[i];
                tree[i]=T[i];
            }
        }*/
};
