#ifndef ele_h
#define ele_h
 #include <ofThread.h>
#include "ofMain.h"
//#include "panel.h"
#define idle 1
#define running 2
#define stop 0
class Ele:public ofThread{
public:
	ofTrueTypeFont(myfont);
	Ele();
	void drawEle(int flag,int m,int i );              //draw the elevator
	int getFloor();                                           //decide which floor it is on its y value
	void threadedFunction() ;                         //the function running in the thread
	queue<int>Eletask;                                  //the combination of the outer and inner requests
	void taskProcess(int asked);                      //get the outer request and find the resequence the response
	void Judgement();                                     //change the elevator state
	int id;                                                        //to name each thread
	int direction;                                             //1:up    0:idle    -1:downwards
	int state;                                                   //running  /  idle:has no request to run  /stop: end the thread
	int currentTarget;                                      //the y value of the current floor



	int x[5];
	int wid;
	int ground;
	int y;
	bool sort;
	char word[10];


};

#endif