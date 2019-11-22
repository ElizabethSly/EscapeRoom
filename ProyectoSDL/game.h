#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "mouse.h"
#include "Textura.h"
#include "puzzle.h"
#include "Room.h"

class Game{
public:
     Game();
     void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

     void handleEvents();
     void update();
     void render();

     void clean();

     SDL_Texture* loadTexture( std::string path );
     bool loadMedia();

     bool running(){return isRunning;}
private:
    Room* room1 = new Room(2);

    int roomActual;
    int vistaActual;

    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;



    string passPC1="";
    bool PC1=false;
};

Game::Game(){
    roomActual = 1;
    vistaActual = 1;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags=0;
    if(fullscreen){
        flags=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        std::cout<<"Subsystems Initialized"<<std::endl;
        window=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
        if(window){
            std::cout<<"window created"<<std::endl;
        }
        renderer=SDL_CreateRenderer(window,-1,0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            std::cout<<"renderer created!"<<std::endl;
        }
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) ){
            printf( "SDL_image no inicializó! SDL_image Error: %s\n", IMG_GetError() );
        }
        if(!loadMedia()){
            printf("Error al cargar la Media");
        }
        isRunning=true;
    }else{isRunning=false;}
}

void Game::handleEvents(){
    int x, y;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning=false;
        break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState( &x, &y );

            room1->handleEvent(x, y);

        break;
        //mostrar coordenadas
        /*case SDL_MOUSEMOTION:
            SDL_GetMouseState( &x, &y );
            system("cls");
            std::cout << "x = " << x <<std::endl;
            std::cout << "y = " << y <<std::endl;
        break;*/
        //para puzzles que necesitan texto
        case SDL_TEXTINPUT:
            SDL_StartTextInput();
            switch(roomActual){
            case 2:
                if(PC1==false){
                    if(event.type==SDL_TEXTINPUT || event.type==SDL_KEYDOWN){
                        if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_BACKSPACE && passPC1.length()>0){
                            passPC1=passPC1.substr(0,passPC1.length()-1);
                            }
                            else if(event.type==SDL_TEXTINPUT){
                                passPC1+=event.text.text;
                                std::cout<<passPC1<<std::endl;
                            }

                    }
                //passPC1+=event.text.text;
                PC1=puzzlePC1(passPC1);
                cout<<PC1;
                    }
                }
            default:
            break;
        SDL_StopTextInput();
    }
}

void Game::update(){

}

void Game::render(){
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );

    room1->render(renderer);


    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Game Cleaned"<<std::endl;
}

bool Game::loadMedia(){
	//Loading success flag
	bool success = true;

	if(!room1->paredes[0].loadFromFile("Room1.png", renderer)){
        printf( "Failed to load room1 texture!\n" );
		success = false;
	}
	if(!room1->paredes[1].loadFromFile("Room2.png", renderer)){
        printf( "Failed to load room2 texture!\n" );
		success = false;
	}
    if(!room1->paredes[2].loadFromFile("Room3.png", renderer)){
        printf( "Failed to load room3 texture!\n" );
		success = false;
	}
	if(!room1->paredes[3].loadFromFile("Room4.png", renderer)){
        printf( "Failed to load room4 texture!\n" );
		success = false;
	}
    if(!room1->vistas[0].imagen.loadFromFile("Vista1.png", renderer)){
        printf( "Failed to load Vista1 texture!\n" );
		success = false;
	}else{
	    room1->vistas[0].pared = 1;
	    SDL_Rect cuadro={230,357,70,70};
	    room1->vistas[0].zona = cuadro;
	}
    if(!room1->vistas[1].imagen.loadFromFile("Vista2.png", renderer)){
        printf( "Failed to load Vista2 texture!\n" );
        success = false;
	}else{
	    room1->vistas[1].pared = 1;
	    SDL_Rect cuadro={415,280,65,50};
	    room1->vistas[1].zona = cuadro;
	}
	return success;
}

#endif // GAME_H_INCLUDED
