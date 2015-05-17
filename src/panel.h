#ifndef panel_h
#define panel_h
 
#include "ofMain.h"

class Panel{
public:
	ofTrueTypeFont(myfont);
	Panel();
	void draw();                            //draw the panel background
	void Signal();                           //the upward and downward triangles on the elevator
	int pressed(int x,int y);             //return which floor is requested
	int askfloor;
            int targetEle;
private:
	int x[5];                                   //stands for the x position of the panel
	int wid,height;                         //the size of panel
	int circleDis;                            //the distance between each circle
            char leftString [20];
            char rightString[20];
            char words[20];
           
};

#endif