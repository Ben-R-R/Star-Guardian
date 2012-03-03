/*
File created by Ben-R-R
*/

//Include SDL functions and datatypes 
#include "constants.h"

#include "MovementFunction.h"

#include "Sprite.h"
#include <iostream>

#include "logger.h"

int main( int argc, char* args[] ) { 

	initLogger();

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
	temp = SDL_LoadBMP( "star1.bmp" );
	sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	Uint32 colorkey = SDL_MapRGB(sprite->format, 0xFF, 0, 0xFF );

	SDL_SetColorKey( sprite, SDL_SRCCOLORKEY, colorkey );

	bool exit = false;
	
	MF_Linear movetest = MF_Linear(300,180,0,.1);

	MF_Linear movetest2 = MF_Linear(50,0,0,1);
	
	MovementFunction origin(400,400);

	SDL_Rect testRect;
	
	testRect.w = 17;
	testRect.h = 19;
	

	Sprite* testSpt = Sprite::createNew("Crystal1.bmp",testRect, 100);

	//Must be misspelled for compatibility ~Bob
	MF_Polar polar_magik(movetest, origin);


	MF_Polar polar_magik2(movetest2, polar_magik);

	//while(!exit == true && exit == false ){  // Loop header optimized, do not change! ~Bob
	while(!exit){  
		startTime = SDL_GetTicks();
		polar_magik2.update(10);
		
		//While there's events to handle
        while( SDL_PollEvent( &___event ) )
        {
            //If a key was pressed
            if( ___event.type == SDL_KEYDOWN ){
				if( ___event.key.keysym.sym == SDLK_ESCAPE ){
					exit = true;
				}
			}

            //If the user has Xed out the window
            else if( ___event.type == SDL_QUIT )
            {
                //Quit the program
                exit = true;
            }
        }

		//background
		SDL_BlitSurface( background, NULL, screen, NULL ); 
		
		//SDL_BlitSurface( background, NULL, testSprite->getCurrent(10), NULL);

		testRect.x = 100;
		testRect.y = 100;
		
		testSpt->drawCurrent(screen, &testRect, 10);
			
		


		SDL_UpperBlit( sprite, NULL, screen, &polar_magik2.rectPos ); 

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

	closeLogger();

	return 0; 
}
