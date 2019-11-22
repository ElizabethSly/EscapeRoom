#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

class Textura
{
	public:
		//Initializes variables
		Textura();

		//Deallocates memory
		~Textura();

		//Loads image at specified path
		bool loadFromFile( std::string path, SDL_Renderer* gRenderer );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Renderer* gRenderer);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		/*void setClip(int x, int y, int w, int h);
		SDL_Rect getClip();
		int getCantidadClips();
		int getClipActual();
		void setClipActual(int);
		void setCantidadClips(int);
        */
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;

		/*
		//Clip
		SDL_Rect SpriteClip;
		int cantidadClips;
		int clipActual;
		*/
};

Textura::Textura()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	/*
	SpriteClip.h=0;
	cantidadClips = 1;
	clipActual = 1;
	*/
}

Textura::~Textura()
{
	//Deallocate
	free();
}

bool Textura::loadFromFile( std::string path, SDL_Renderer* gRenderer )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 123, 198, 255 ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Textura::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Textura::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Textura::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void Textura::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Textura::render( int x, int y, SDL_Renderer* gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	/*if( cantidadClips > 1 )
	{
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	}*/

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, &renderQuad, &renderQuad );
}

int Textura::getWidth()
{
	return mWidth;
}

int Textura::getHeight()
{
	return mHeight;
}

/*
void Textura::setClip(int x, int y, int w, int h){
    SpriteClip.x = x;
    SpriteClip.y = y;
    SpriteClip.w = w;
    SpriteClip.h = h;
}

SDL_Rect Textura::getClip(){
    return SpriteClip;
}

int Textura::getCantidadClips(){
    return cantidadClips;
}
int Textura::getClipActual(){
    return clipActual;
}
void Textura::setClipActual(int cantidad){
    clipActual = cantidad;
}
void Textura::setCantidadClips(int cantidad){
    cantidadClips = cantidad;
}
*/
#endif // TEXTURA_H_INCLUDED
