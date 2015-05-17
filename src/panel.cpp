#include "panel.h"
Panel::Panel(){
	for(int i=0;i<5;i++){
		x[i]=190+160*i;
	}
	wid=110,height=680;
	circleDis=40;
	targetEle = -1;
	askfloor = -1;
}

void Panel::draw(){
	ofEnableAlphaBlending();
	ofSetColor(255,0,0,60);                     // red, 50% transparent
	for(int i=0;i<5;i++){
		ofRect(x[i],8,wid,height);
	}
           ofDisableAlphaBlending();

	myfont.loadFont("Carre.ttf", 15);
	ofEnableAlphaBlending();

            ofSetColor(40,122,135,180);
            for(int k=0;k<5;k++){
                 for(int i=1;i<11;i++){
		ofCircle(x[k]+30,260+40*i,15);
		ofCircle(x[k]+85,260+40*i,15);
	     }
            }

            for(int k=0;k<5;k++){
                 for(int i=1;i<11;i++){
		sprintf(leftString,"%d",i);
		sprintf(rightString,"%d",i+10);
		ofSetColor(255,251,240,90);
		myfont.drawString(leftString,  x[k]+25,  265+40*i);
		myfont.drawString(rightString,  x[k]+80,  265+40*i);
	     }
            }
            
            for(int i=0;i<20;i++){
            	sprintf(words,"%d",20-i);
                        ofSetColor(40,122,135,180);
            	myfont.drawString(words,30,23+35*i);
            }
}

void Panel::Signal(){
	ofEnableAlphaBlending();

	for(int i=0;i<5;i++){
                        ofSetHexColor(0xFFFF99);

		ofTriangle(x[i]+30,175,x[i]+10,202,x[i]+50,202);
		ofTriangle(x[i]+65,175,x[i]+105,175,x[i]+85,202);
	}
	ofDisableAlphaBlending();
}
int Panel::pressed(int x,int y){
	for(int k=1;k<11;k++){
		for(int i=0;i<5;i++){
		float dis1=ofDist(x,y,190+160*i+30,260+40*k);
		if(dis1<15){
			//innerReq[i].push(k-1);
			targetEle = i;
			askfloor = k-1;
			return (k-1);
		}
		float dis2=ofDist(x,y,190+160*i+85,260+40*k);
		if(dis2<15){
			//innerReq[i].push(k+9);
			targetEle = i;
			askfloor = k+9;
			return (k+9);
		}
	            }  
	}
}

