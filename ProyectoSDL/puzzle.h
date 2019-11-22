#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>

using namespace std;
//todos los puzzles van aca?

bool puzzlePC1(string password){
    //cambiar a texto de SDL por pantalla?
    cin>>password;
    if(password.compare("abcdf")==0){
        return true;
    }else
    {return false;}
}

#endif // PUZZLE_H_INCLUDED
