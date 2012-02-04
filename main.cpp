/*
File created by Ben-R-R
*/

//Include SDL functions and datatypes 
#include "SDL.h"

int main( int argc, char* args[] ) { 
	//The images 
	SDL_Surface* background = NULL; 
	SDL_Surface* temp = NULL;
	SDL_Surface* screen = NULL;

	//Start SDL 
	SDL_Init( SDL_INIT_EVERYTHING ); 

	//Set up screen 
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE ); 

	//Load image
	temp = SDL_LoadBMP( "hello.bmp" );
	background = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	//Apply image to screen 
	SDL_BlitSurface( background, NULL, screen, NULL ); 

	//Update Screen 
	SDL_Flip( screen ); 

	//Pause 
	SDL_Delay( 5000 );
	//Free the loaded image 
	SDL_FreeSurface( background ); 
	//Quit SDL 
	SDL_Quit();
	return 0; 
}