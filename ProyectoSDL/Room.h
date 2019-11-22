#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

struct vista
{
    Textura imagen;
    int pared;
    SDL_Rect zona;
};

class Room
{
public:
    Room(int cantidadVistas);
    ~Room();

    void handleEvent(int x, int y);
    void render(SDL_Renderer* gRenderer);

    void moverDerecha();
    void moverIzquierda();

    Textura paredes[4];
    vector<vista> vistas;

private:
    int paredActual;
    int vistaActual;
    bool estaEnVista;


};

Room::Room(int cantidadVistas = 0){
    paredActual = 1;
    estaEnVista = false;
    vistas.resize(cantidadVistas);
}

Room::~Room(){
}

void Room::handleEvent(int x, int y){
    if(!estaEnVista){
        if(x>749 && x<801){
            moverDerecha();
        }
        if(x>0 && x<51){
            moverIzquierda();
        }
        for (int i=0; i<vistas.size(); i++){
            if(x>vistas[i].zona.x && x<vistas[i].zona.x+vistas[i].zona.w && y>vistas[i].zona.y && y<vistas[i].zona.y+vistas[i].zona.h){
                estaEnVista = true;
                vistaActual = i+1;
                return;
            }
        }
    }
    else{
        if(x>0 && x<111 && y>0 && y <40){
            estaEnVista = false;
        }
    }

}

void Room::render(SDL_Renderer* renderer){
    if(!estaEnVista){
        switch(paredActual){
        case 1:
            paredes[0].render(0,0,renderer);
            break;
        case 2:
            paredes[1].render(0,0,renderer);
            break;
        case 3:
            paredes[2].render(0,0,renderer);
            break;
        case 4:
            paredes[3].render(0,0,renderer);
            break;
        }
    }
    else{
        switch(vistaActual){
        case 1:
            vistas[0].imagen.render(0,0,renderer);
            break;
        case 2:
            vistas[1].imagen.render(0,0,renderer);
            break;
        }
    }
}

void Room::moverDerecha(){
    paredActual++;
    if(paredActual>4)paredActual=1;
}
void Room::moverIzquierda(){
    paredActual--;
    if(paredActual<1)paredActual=4;
}
#endif // ROOM_H_INCLUDED
