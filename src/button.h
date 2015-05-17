#ifndef button_h
#define button_h
 
#include "ofMain.h"
#include <queue>
class Button{
public:
	Button();
	void draw();        //draw the button
	int pressed(int x,int y);    //receive the button request and know which floor is required
	queue<int>hearReq;    //  +:upwards      -:downwards

private:
	int x1;       //the x postion of the left one with upwards triangle
	int x2;       //the x postion of the right one with downwards triangle
	int gap;    //the distance of y of each button
};

#endif