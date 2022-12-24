#pragma once
#include <iostream>
#include <string.h>
#include <ctime>
#include <limits>
#include "../include/raylib.h"
#include "../include/raymath.h"

using namespace std;

#define INF std::numeric_limits<float>::infinity()

//This is a class created to save up space/time in other Classes(It is similar to Vector2)
//We implement methods to set and get the x,y values from the private part of the class.
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

//This is a class containing all the necessary information for our Rectangle entities with Textures
//It stores the image,Rectangle{x,y,width,height},Position(Vector2) and Color drawn.
//We implement once again the methods for accessing the private parts of the class Rec.
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

//This class stores our Image Textures of each entity
class Textures{
    public:
        Texture2D T1;
        Texture2D T2;
        Texture2D T3;
        Texture2D T4;
        Texture2D T5;
        Texture2D T6;
};

/*The potion class contains a default constractor , the private informations and
of course the methods in order to access them
The bool variable Existance ensures that the Potion entity exists in the Game 
It gets initialized as true in the LoadPotion section and we set it to false when
our avatar collects the potion from the map(When he collided with it)*/
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

/*The Entity class contains the private informations and the methods in order to access them
The variable PotionCount refers to the Potions that Both Werewolves and Vampires have and they
use on their allies. The Number refers to the number of Werewolves/Vampires existing in each frame
in our Game.*/
class Entity{
    protected:
        string name;
        int PotionCount;
        int Number;
    public:
        int* potisource(){
            //The Potion source refers to the position of the variable Potion Count and 
            //we use it to access and change the PotionCounter of our Entity -> avatar.
            //Similar to usepotion but with pointers because we want to modify it in a different function.
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
        void set_num(int num){
            Number=num;
        }
        
};

/*Class avatar contains the position,Team name and Texture of our avatar
The informations are private and can be accessed with our methods*/
class Avatar: public Entity{
    private:
        const char* Team;
        Texture2D texture;
        Vector2 z;

    public:
        //Default Constructor for the Class Avatar
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

/*Class Werewolf contains the Health,Damage and Defense of each Werewolf
The informations are private and can be accessed with our methods.We also have 
a public bool variable isDead to keep track of the dead Entities both for Werewolves and
Vampires*/
class Werewolf: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:
        bool isDead;
        //Default Constructor randomizing the Damage and defense of our entities
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
        void add_health(int x){
            Health=Health + x;
        }
        void set_health(int x){
            Health=x;
        }
        //returns the position of the Number variable so we can modify and display it in different Functions
        int* get_num(){
            return &Number;
        }
};

/*Class Vampire contains the Health,Damage and Defense of each Werewolf
The informations are private and can be accessed with our methods.We also have 
a public bool variable isDead to keep track of the dead Entities both for Werewolves and
Vampires*/
class Vampire: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:
        bool isDead;
        //Default Constructor randomizing the Damage and defense of our entities
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
        void add_health(int x){
            Health=Health + x;
        }
        void set_health(int x){
            Health=x;
        }
        //returns the position of the Number variable so we can modify and display it in different Functions
        int* get_num(){
            return &Number;
        }
};

/*Class terrain contains private informations Texture(image),Position and Color for our Terrains.Of course 
we have our Default Constructor and the methods to access everything.
*/
class Terrain{
    private:
        Texture2D texture;
        Vector2 TerPos;
        Color tint;
    public:
        Terrain(){
            tint = WHITE;
        }
        Color GetCol(){
            return tint;
        }
        Texture GetTex(){
            return texture;
        }
        void SetTex(Texture2D tex){
            texture = tex;
        }
        void SetCol(Color code){
            tint = code;
        }
        Vector2 GetPos(){
            return TerPos;
        }
        void SetPos(Vector2 z1){
            TerPos=z1;
        }
};

/*The Class Game is the most important one , here we store everything we need for our game.
Rectangles is a "Matrix" containing both Werewolves and Vampires in the form of Recs.With the Rectangles
we can access and change the position etc. of the entities.*/
//werewolf/vampire are "tables" containing the health etc of each entity so our code is more readable and easier to understand and change
class Game{
    public:
        Rec** Rectangles;
        Avatar avatar;
        Werewolf* werewolf;
        Vampire* vampire;
        Potion potion;
        Terrain *Terrains;
        float Speed; //speed of our game meaning the pixels which the entities move(max 10)
        int Time; //Time of the day used in the Avatar Healing
    public:
    //Secondary constructor with specific Width and Height used in the beginning of Create Window
        Game(int Width, int Height){
            int count=(Width*Height)/(20*21*21);
            Vampire* V=new Vampire[count];
            Werewolf* W=new Werewolf[count];
            this->vampire=V;
            this->werewolf=W;
            Time = 0;
            Speed = 5.0;
        }
        //Default Constructor for the Game class
        Game(){}
};
