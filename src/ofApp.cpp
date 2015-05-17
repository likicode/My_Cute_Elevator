#include "ofApp.h"
#include "ele.h"
//int y=0;
int y=680;
int pos = 0;
int flag=0;
int Ele_num = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    	myfont.loadFont("Carre.ttf", 15);

      /*********************** start the elevator thread ********/
        for(int i = 0; i<5;i++)
        {
          theEle.push_back(new Ele());
          theEle[i]->startThread(true, false);
          theEle[i]->id = i;
        }

}

//--------------------------------------------------------------
void ofApp::update(){

/********************  judge the elevator state simultaneously     ***********/
          for(int i =0;i<5;i++)
            {
                 theEle[i]->Judgement();
            }
  }

//--------------------------------------------------------------
void ofApp::draw(){
             
        	theButton.draw();   
          	thePanel.draw();
            thePanel.Signal();
            for(int i =0;i<5;i++) {
                  theEle[i]->drawEle(0,theEle[i]->currentTarget ,i);
            }
       
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

      theButton.pressed(x,y);
      thePanel.pressed(x,y);
      int eleid = thePanel.targetEle;   // know which ele has received the request
      if(thePanel.askfloor>=0 && eleid >=0){
                 theEle[eleid]->taskProcess(thePanel.askfloor);       //let the very elevator to task new request
      }
      if(!theButton.hearReq.empty()){
              shortest();                                                                 //handle the outside request on button 
      }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void  ofApp::shortest(){
     int asked=theButton.hearReq.front();    //handle the first request on button
     int floorDis = 0;        //the distance between the current floor and the asked floor
     int choice = 0;  //the final picked elevator
     
     /**************************   handle the situation that the request is upward  *******/
      if(asked>0){     
        for(int i=0;i<5;i++){
            int floorDis=abs(asked-theEle[0]->getFloor());
            int  currentFloor=theEle[i]->getFloor();
            if((theEle[i]->direction==1&&asked>currentFloor)||  theEle[i]->state==1 || (theEle[i]->direction==-1&&asked<currentFloor)  )
            {
                 int way=abs(asked-currentFloor);
                 if(way<=floorDis){
                  floorDis=way;
                  choice= i;
                 }
             }
             else{
              choice=rand()%5;
             }
        }
     }


     /**************************   handle the situation that the request is downward  *******/
     else if(asked<0){
      for(int i=0;i<5;i++){
         int floorDis=abs(theEle[0]->getFloor()+asked);
         int currentFloor=theEle[i]->getFloor();
         if((theEle[i]->direction==-1&&abs(asked)<currentFloor)||theEle[i]->state==1|| (theEle[i]->direction==1&&abs(asked)>currentFloor))
         {
              int way=abs(asked+currentFloor);
              if(way<=floorDis){
                   floorDis=way;
                    choice= i;
            }
         }
         else{
          choice=rand()%5;
         }
      }
     }


     /***********************************  deliver to the ele to process   ****************************************/
     int ask=abs(asked);
     theEle[choice]->taskProcess(ask);

     theButton.hearReq.pop();
  }


