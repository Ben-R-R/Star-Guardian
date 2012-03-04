
#include "Sprite.h"

void Sprite::updateTimer(unsigned int fT){
	// check if either is zero
	if(frameTime * fT == 0){
		return;
	}

	elapsedTime += fT;
	if(elapsedTime > frameTime){
		elapsedTime = elapsedTime % frameTime;
		frameIndex++;
		frameIndex = frameIndex % frameSets[setIndex].size();
	}
}

void Sprite::drawCurrent(SDL_Surface *dest,SDL_Rect * location, unsigned int frameTime){

	updateTimer(frameTime);

	frameSize.x = (frameSets[setIndex][frameIndex] % w_F) * frameSize.w;
	frameSize.y = (frameSets[setIndex][frameIndex] / w_F) * frameSize.h;
	
	SDL_BlitSurface(spriteSheet, &frameSize, dest, location);
}

void Sprite::drawTile(SDL_Surface *dest, SDL_Rect * location, unsigned int frameNum){

	frameSize.x = ((frameNum) % w_F) * frameSize.w;
	frameSize.y = ((frameNum) / w_F) * frameSize.h;


	
	SDL_UpperBlit(spriteSheet, &frameSize, dest, location);
}

Sprite* Sprite::createNew(std::string file, const SDL_Rect &frameSize, int frameTime){
	SDL_Surface* temp = SDL_LoadBMP( file.c_str() );

	if(temp == 0){

	}
	
	SDL_Surface* image = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	return new Sprite(image, frameSize, frameTime);


}

Sprite::Sprite(SDL_Surface * image, const SDL_Rect &size, int fT):
frameSets(1)
{
	
	spriteSheet = image;
	frameSize = size;
	
	Uint32 colorkey = SDL_MapRGB(spriteSheet->format, 104, 144, 168 );

	SDL_SetColorKey( spriteSheet, SDL_SRCCOLORKEY, colorkey );

	int tempX = image->w / size.w;
	int tempY = image->h / size.h;

	
	w_W = tempX * size.w;
	h_H = tempY * size.h;

	w_F = tempX;
	h_F = tempY;

	frameIndex = 0;
	setIndex = 0;

	elapsedTime = 0;
	frameTime = fT;

	frameSets[0] = (std::vector<int>(tempX * tempY));

	for(unsigned int i = 0; i < frameSets[0].size(); i ++){
		frameSets[0][i] = i;
	}
}

Sprite::~Sprite(){
	SDL_FreeSurface(spriteSheet);
}

void Sprite::setSet(int set){
	setIndex = set;
}

void Sprite::setFrame(int frame){
	frameIndex = frame;
}

void Sprite::addSet(const std::vector<int> &setVec){
	frameSets.push_back(setVec);
}

