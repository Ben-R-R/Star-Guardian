#ifndef UTILS_H
#define UTILS_H


// we have this because the math pow function takes 
// doubles as arguments, and we don't need to waste that 
// many clock cycles. 
inline int UTIL_square(int value){
	return value * value;
}

inline bool UTIL_rectContainsPoint(SDL_Rect &rect, int x, int y){
	return (
		(x >= rect.x) 
		&& (x < (rect.x + rect.w))
		&& (y >= rect.y) 
		&& (y < (rect.y + rect.h))
		);
}

inline bool UTIL_rectColision(SDL_Rect &rectA,SDL_Rect &rectB){
	return (
		((rectB.x + rectB.w) > (rectA.x))
		&&
		((rectA.x + rectA.w) > (rectB.x))
		&&
		((rectB.y + rectB.h) > (rectA.y))
		&&
		((rectA.y + rectA.h) > (rectB.y))
		);
}

// uses the x and y values in the SDL_rectangles as the center of the 
// circles
inline bool UTIL_circleColision(SDL_Rect &coordA, int radA, SDL_Rect &coordB, int radB){
	
	return (UTIL_square(coordA.x - coordB.x) + UTIL_square(coordA.y - coordB.y)) > (UTIL_square(radB) + UTIL_square(radA));
}

#endif