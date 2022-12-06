#include "Classes.h"

using namespace std;

//argv[1]=WindowWidth
//argv[2]=WindowHeight
//argv[3]=Team which user supports. Vampires or Werewolves

//good map size could be 750x750. Entity could be 21x21 pixels(20 pixels=sprite, 1 pixel for collision checking). (750*750/15)/(21*21)=85 entities per team

int main(int argc, char** argv){
    try{
        if(argc!=4){
            throw argc;
        }
        if(strcmp(argv[3], "Vampires") && strcmp(argv[3], "vampires") && strcmp(argv[3], "Werewolves") && strcmp(argv[3], "werewolves")){
            throw argv[3];
        }
        if(atoi(argv[1])<500 || atoi(argv[1])>1500 || atoi(argv[2])<500 || atoi(argv[2])>1500){
            Position x(atof(argv[1]), atof(argv[2]));
            throw x;
        }
    }
    catch(int argc){
        cout << "\nProgram needs to have exactly 4 arguements, you gave " << argc << ".\nExiting...\n\n";
        return -1;
    }
    catch(char* chr){
        cout << "\nWrong team selection. Choose either Werewolves or Vampires.\nExiting...\n\n";
        return -1;
    }
    catch(Position x){
        cout << "\nIncorrect map size. Map should be bigger than 500 and less than 1500 pixels.\nYou gave: " << x.get_x() << " x " << x. get_y() << "\nExiting...\n\n";
        return -1;
    }
    int WindowWidth=atoi(argv[1]), WindowHeight=atoi(argv[2]);
    CreateWindow(WindowWidth, WindowHeight);
    return 0;
}
