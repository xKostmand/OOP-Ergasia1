#include <iostream>
#include "Classes.h"

using namespace std;

int main(void){
    int WindowWidth=0, WindowHeight=0;
    cout << "How big do you want the window to be: ";
    cin >> WindowWidth;
    cin >> WindowHeight;
    CreateWindow(WindowWidth, WindowHeight);
}