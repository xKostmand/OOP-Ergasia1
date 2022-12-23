#pragma once
#include <iostream>
#include <string.h>
#include <ctime>
#include <limits>
#include "../include/raylib.h"
#include "../include/raymath.h"

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
    private:
        Texture2D texture;
        Rectangle source;
        Vector2 position;
        Color tint;
    public:
        Rec(Texture2D T, Rectangle R, Vector2 P, Color Ti){
            texture=T;
            source=R;
            position=P;
            tint=Ti;
        }
        Rec(){}
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
        void setpos(Vector2 pos){
            position=pos;
        }
        void setx(float x1){
            position.x=position.x + x1;
        }
        void sety(float y1){
            position.y=position.y + y1;
        }
        void setx(int x1){
            position.x=x1;
        }
        void sety(int y1){
            position.y=y1;
        }
};

class Textures{
    public:
        Texture2D T1;
        Texture2D T2;
        Texture2D T3;
        Texture2D T4;
        Texture2D T5;
        Texture2D T6;
};

class Potion{
    private:
        Position position;
        Texture2D texture;
        bool Existance;
    public:
        Potion(){}
        Potion(Position z):position(z){}
        Vector2 get_pos(){
            Vector2 pos;
            pos.x = position.get_x();
            pos.y = position.get_y();
            return pos;
        }
        void set_PotEx(bool ex){
            Existance = ex;
        }
        bool* DoesPotExist(){
            return &Existance;
        }
        void set_pos(Vector2 pos){
            position.set_x(pos.x);
            position.set_y(pos.y);
        }
        void set_Tex(Texture2D tex){
            texture = tex;
        }
        Texture2D get_Tex(){
            return texture;
        }
};

class Entity{
    protected:
        string name;
        int PotionCount;
        int Number;
    public:
        int* potisource(){
            return &PotionCount;
        }
        string get_name(){
            return name;
        }
        void set_pot(int count){
            PotionCount = count;
        }
        int get_pot(){
            return PotionCount;
        }
        void usepotion(){
            PotionCount--;
        }
        
};

class Avatar: public Entity{
    private:
        const char* Team;
        Texture2D texture;
        Vector2 z;

    public:
        Avatar(){
            name="Avatar";
            PotionCount = 1;
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
        bool isDead;
        Werewolf(){
            name="Werewolf";
            PotionCount=GetRandomValue(0,2);
            Health=10;
            Damage=GetRandomValue(1,3);
            Defense=GetRandomValue(1,2);
            isDead=false;
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
            Health=Health + x;
        }
        int* get_num(){return &Number;}
};

class Vampire: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:
        bool isDead;
        Vampire(){
            name="Vampire";
            PotionCount=GetRandomValue(0,2);
            Health=10;
            Damage=GetRandomValue(1,3);
            Defense=GetRandomValue(1,2);
            isDead=false;
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
            Health=Health + x;
        }
        int* get_num(){return &Number;}
};

class Terrain{
    private:
        Texture2D texture;
        Vector2 TerPos;
        Color tint;
    public:    
        Rectangle Recta;
        Terrain(){
            tint = WHITE;
        }
        Color GetCol(){return tint;}
        Texture GetTex(){return texture;}
        void SetTex(Texture2D tex){texture = tex;}
        void SetCol(Color code){tint = code;}
        Vector2 GetPos(){
            return TerPos;
        }
        void SetPos(Vector2 z1){
            TerPos=z1;
        }
};


class Game{
    public:
        Rec** Rectangles;
        Avatar avatar;
        Werewolf* werewolf;
        Vampire* vampire;
        Potion potion;
        Terrain *Terrains;
        float Speed;
        int Time;
    public:
        Game(int Width, int Height){
            int count=(Width*Height)/(20*21*21);
            Vampire* V=new Vampire[count];
            Werewolf* W=new Werewolf[count];
            this->vampire=V;
            this->werewolf=W;
            Time = 0;
            Speed = 5.0;
        }
        Game(){}
};
