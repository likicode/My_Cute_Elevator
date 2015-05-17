#include "ele.h"
#include <pthread.h>
Ele::Ele(){
	for(int i=0;i<5;i++){
		x[i]=190+160*i;
	}
	wid=110;
	ground=680;
	y = 680;
	direction=0;
	state = stop;  
	currentTarget = 0;   //the y of target floor
	id = 0; 
	sort = false;
}

void Ele::drawEle(int flag,int m,int i){
	ofEnableAlphaBlending();
	ofSetColor(51,153,51,90);
	ofFill();    
	m = 680-Eletask.front()*35;

	/*******************  draw the current floor    ****************************/
	myfont.loadFont("Carre.ttf", 25);
	int get=getFloor();
	sprintf(word,"%d",get+1);
	ofSetColor(213,15,37,90);
	myfont.drawString(word,x[i]+50,100);
            /********************  control the elevator running method *******************************/
	if (state == running)
	{    		
		if (y < m &&y<680)
		{
			y++;
			direction=-1;	
			ofSetColor(20,100,20,90);                                          //draw the downward sign
			ofTriangle(x[i]+65,175,x[i]+105,175,x[i]+85,202);

		}
		else if (y>m)
		{
			y--;
			direction=1;	
			ofSetColor(20,100,20,90);                                          //draw the upward sign
			ofTriangle(x[i]+30,175,x[i]+10,202,x[i]+50,202);
		}
		else if(y == m)
		{
			y = m;
			direction=0;
			sleep(2000);	
			Eletask.pop();
			state = idle;
		}
		else if(y>=680)
		{
			y = 680;
		}
		else if(y<=0)
		{
			y = 0;
		}
		ofRect(x[i],y,110,20);		
		ofDisableAlphaBlending();
           }
          else  if (state == idle)
           {
           	     ofSetColor(20,20,100,90);
                  ofRect(x[i],y,110,20);
                  ofDisableAlphaBlending();
           }
}

int Ele::getFloor(){
	return (680-y)/35;
}

void Ele::threadedFunction() {
        if(isThreadRunning()) {
        	state = idle;
        }
        else
        {
        	state = stop;
        }

}

void Ele::Judgement()
{
	if(!Eletask.empty())
	{
		if (state == idle && sort)                        //after excute the taskProcess which provide with a nearest currentTask
		{
			int currentTask=Eletask.front();
	           		state = running;
	            	currentTarget = 680-currentTask*35;
		}
	}
}

void Ele::taskProcess(int ask){
	int sz[1000];
	sort = false;
	Eletask.push(ask);
	int now=getFloor();
	int k=0;
	while(!Eletask.empty()){
		sz[k]=Eletask.front();
		k++;
		Eletask.pop();
	}
	for(int i=0;i<k;i++){
      		  for(int j=i;j<k;j++){
            		if(abs(sz[i]-now)>abs(sz[j]-now)){
               			 int temp=sz[i];
               			 sz[i]=sz[j];
                			 sz[j]=temp;
          			  }
     		   }
   	 }
   	 for(int i=0;i<k;i++){
   	 	Eletask.push(sz[i]);
   	 }
   	 sort = true;
}






