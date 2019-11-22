#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>

class cMouse
{
	public:
        cMouse();

		void setPosition( int x, int y );

		int handleEvent( SDL_Event* e );

	private:
		SDL_Point mPosition;

};

cMouse::cMouse()
{
	mPosition.x = 0;
	mPosition.y = 0;

}

void cMouse::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

int cMouse::handleEvent( SDL_Event* e )
{
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN )
	{
		int x, y;
		SDL_GetMouseState( &x, &y );

        switch( e->type )
        {
            case SDL_MOUSEBUTTONDOWN:
                if(x>225 && x<300 && y>330 && y<400){
                    return 0;
                }
            break;
            case SDL_MOUSEMOTION:
				system("cls");
				std::cout << "x = " << x <<std::endl;
				std::cout << "y = " << y <<std::endl;
            break;
        }
	}
}

#endif // MOUSE_H_INCLUDED
