#include "gamecore.h"
#include "logger.h"
#include <list>

GameEnvironment* currentEnvironment;
SDL_Surface* screen;

std::list< SDL_Event* > * tempEventStore;

bool endGame;



int gameInitialize(){
	//Start SDL 
	if (! SDL_Init( SDL_INIT_EVERYTHING )){
		return 1;
	}
	
	//Set up screen 
	screen = SDL_SetVideoMode(SCREEN_WIDTH ,SCREEN_HEIGHT , 32, SDL_SWSURFACE ); 
	if(!screen){
		return 2;
	}
	tempEventStore = new std::list<SDL_Event * >();

#ifdef LOGGING_ENABLED 
	initLogger();
#endif

}


SDL_Event * currEvent;

inline void eventStuff(){
	//While there's events to handle
        while( SDL_PollEvent( currEvent) )
        {
            //If the user has X'ed out the window
            if( currEvent->type == SDL_QUIT )
            {
                //Quit the program
                endGame = true;

			} else if (currentEnvironment->usingEvents()) {
				// we do this so that any events received since the environment run()
				// call don't get lost. There shouldn't be too many events, so the 
				// overhead should be small
				tempEventStore->push_back(currEvent);
			} else {
				delete currEvent;
			}
        }
		// push any events back on the queue
		while(tempEventStore->size()){
			SDL_PushEvent(tempEventStore->front());
			tempEventStore->pop_front();
		}
}

void gameRun(GameEnvironment * firstEnvironment){
	if(!firstEnvironment->init()){
		return;
	}
	currentEnvironment = firstEnvironment;

	GameEnvironment* tempEnv;

	endGame = false;

	bool skipRender = false;

	Uint32 frameTime = 0;
	Uint32 startTime = 0;
	Uint32 renderTime = 0;

	while(!endGame){
		
		startTime = SDL_GetTicks();

		tempEnv = currentEnvironment->runTick(frameTime);
		
		renderTime += frameTime;

		if(!skipRender){
			currentEnvironment->render(renderTime, *screen);
			renderTime = 0;
		}

		if(tempEnv == NULL){
			endGame = true;
		} else {
			currentEnvironment = tempEnv;
		}
		
		eventStuff();
		

		frameTime = SDL_GetTicks() - startTime;
		
		if(frameTime < TARGET_MS_PER_FRAME){
			SDL_Delay(TARGET_MS_PER_FRAME - frameTime);
			skipRender = false;

		} else {
			// token delay to let the OS breathe 
			SDL_Delay(5);
			skipRender = true;

		}
		
		// account for SDL_Delay overhead.  
		frameTime = SDL_GetTicks() - startTime;

	}// end game loop

}

void gameClose(){
	delete currentEnvironment;
	delete tempEventStore;
	delete currEvent;
	SDL_Quit();
#ifdef LOGGING_ENABLED 
	closeLogger();
#endif
}