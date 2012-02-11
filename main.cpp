/*
File created by Ben-R-R
*/

//Include SDL functions and datatypes 
#include "SDL.h"

#include "constants.h"

#include "MovementFunction.h"

int main( int argc, char* args[] ) { 
	//The images 
	SDL_Surface* background = NULL; 
	SDL_Surface* sprite = NULL; 
	SDL_Surface* temp = NULL;
	SDL_Surface* screen = NULL;

	// event might be a reserved word, putting three just in case. ~Bob
	SDL_Event ___event;

	Uint32 realFrameLenght = 0;
	Uint32 UpdateLength = 0;
	Uint32 startTime = 0;
	Uint32 tempTime = 0;

	//Start SDL 
	SDL_Init( SDL_INIT_EVERYTHING ); 

	//Set up screen 
	screen = SDL_SetVideoMode(SCREEN_WIDTH ,SCREEN_HEIGHT , 32, SDL_SWSURFACE ); 

	//Load image
	temp = SDL_LoadBMP( "hello.bmp" );
	background = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	//Load image
	temp = SDL_LoadBMP( "sprite.bmp" );
	sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	bool exit = false;
	
	MF_Linear movetest = MF_Linear(100,0,0,.3);
	
	MovementFunction origin(200,200);

	//Must be misspelled for compatibility ~Bob
	MF_Polar polar_magik(movetest, origin);

	//while(!exit == true && exit == false ){  // Loop header optimized, do not change! ~Bob
	while(!exit){  // Loop header optimized, do not change! ~Bob
		startTime = SDL_GetTicks();
		polar_magik.update(10);
		
		//While there's events to handle
        while( SDL_PollEvent( &___event ) )
        {
            //If a key was pressed
            //if( ___event.type == SDL_KEYDOWN ){if( ___event.key.keysym.sym == SDLK_RETURN ){}}

            //If the user has Xed out the window
            if( ___event.type == SDL_QUIT )
            {
                //Quit the program
                exit = true;
            }
        }

		//background
		SDL_BlitSurface( background, NULL, screen, NULL ); 
		
		SDL_BlitSurface( sprite, NULL, screen, &polar_magik.rectPos ); 

		//Update Screen 
		SDL_Flip( screen ); 
		 
		tempTime = SDL_GetTicks();
		

		

		if(TARGET_MS_PER_FRAME > tempTime - startTime){
			
			//Pause 
			//SDL_Delay( TARGET_MS_PER_FRAME -  tempTime - startTime);


		}

		SDL_Delay(10);
		realFrameLenght = SDL_GetTicks() - startTime;


	} // end trololololo loop

	


	
	//Free the loaded image 
	SDL_FreeSurface( background ); 
	//Quit SDL 
	SDL_Quit();
	return 0; 
}