#include "button.h"

Button::Button(){
	x1=70;
	x2=100;
	gap=35;

}
void Button::draw(){
	for(int i=0;i<20;i++){
	    ofSetHexColor(0x3399FF);
	    ofCircle(x1,15+gap*i,10);
	    ofCircle(x2,15+gap*i,10);
	    ofSetHexColor(0xFFFF99);
	    ofTriangle(x1+9,20+gap*i,x1-9,20+gap*i,x1,5+gap*i);
	    ofTriangle(x2+9,10+gap*i,x2-9,10+gap*i,x2,25+gap*i);
	}
}

int Button::pressed(int x,int y){
	for(int i=0;i<20;i++){
		float distance1=ofDist(x1,15+gap*i,x,y);
		if(distance1<10){
			hearReq.push(19-i);
			return i;

		}
		float distance2=ofDist(x2,15+gap*i,x,y);
		if(distance2<10){
			hearReq.push(-1*(19-i));
			return 20+i;
		}
	}
}

