#pragma once
#include <string>

using namespace std;

class Position{
    private:
        float x;
        float y;
    public:
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

class Potion{
    private:
        Position position;
};

class Entity{
    protected:
        string name;    
        Position position;
        int PotionCount;
        //int speed;  ?
    public:

};

class Avatar: public Entity{
    private:
        string Team;
};

class Werewolf: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:

};

class Vampire: public Entity{
    private:
        int Health;
        int Damage;
        int Defense;
    public:

};

class Terrain{
    private:
        Position position;
    public:
        Terrain(Position z):position(z){}   //Initialize using Terrain var({x1, x2});
};

typedef Terrain Earth;
typedef Terrain Water;
typedef Terrain Tree;
