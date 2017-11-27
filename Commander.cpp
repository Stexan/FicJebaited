#include "Commander.h"
#include <tuple>
#include <iostream>
#include <cassert>

using namespace std;

bool isLowerLeft(FicPoint myPosition, FicPoint enemyPosition){
    return myPosition.first > enemyPosition.first && myPosition.second > enemyPosition.second;
}
bool isLowerRight(FicPoint myPosition, FicPoint enemyPosition){
    return myPosition.first < enemyPosition.first && myPosition.second > enemyPosition.second;
}
bool isUpperLeft(FicPoint myPosition,FicPoint enemyPosition){
    return myPosition.first > enemyPosition.first && myPosition.second < enemyPosition.second;
}
bool isUpperRight(FicPoint myPosition,FicPoint enemyPosition){
    return myPosition.first < enemyPosition.first && myPosition.second < enemyPosition.second;
}

void Commander::findDirection(FicPoint oldC, FicPoint newC){

  int threshold = 2;
  
  if (newC.getX() - oldC.getX() > threshold){
    if (newC.getY() - oldC.getY() > threshold){
      direction = "DreaptaJos";
    }else if (newC.getY() - oldC.getY() < -threshold){
      direction = "DreaptaSus";
    }else{
      direction = "Dreapta";
    }
  }else if (newC.getX() - oldC.getX() < -threshold){
    if (newC.getY() - oldC.getY() > threshold){
      direction = "StangaJos";
    }else if (newC.getY() - oldC.getY() < -threshold){
      direction = "StangaSus";
    }else{
      direction = "Stanga";
    }
  }else{
    if (newC.getY() - oldC.getY() > threshold){
      direction = "Jos";
    }else if (newC.getY() - oldC.getY() < -threshold){
      direction = "Sus";
    }else{
      direction = "";
    }
      
    assert("reached end of getDirection");
  }

}

void Commander::go(FicPoint myPosition, FicPoint enemyPosition){

  /*if (isLowerLeft(myPosition, enemyPosition)){
    cout<<"Lower Left";
  }else if (isLowerRight(myPosition, enemyPosition)){
      cout<<"Lower Right";
  }else if (isUpperLeft(myPosition, enemyPosition)){
      cout<<"Upper Left";
  }else if (isUpperRight(myPosition, enemyPosition)){
      cout<<"Upper Right";
  }*/

}

void Commander::calcDirectionLine(FicPoint leftTop, FicPoint leftBot, FicPoint rightTop, FicPoint rightBot) {
    
    if (direction == "") {
        return;
    }
    
    FicPoint firstPoint;
    FicPoint secondPoint;
    if (direction == "Dreapta"){
        firstPoint = rightTop;
        secondPoint = rightBot;
    }else if (direction == "DreaptaJos"){
        firstPoint = rightTop;
        secondPoint = rightBot;
    }else if (direction == "DreaptaSus"){
        firstPoint = rightTop;
        secondPoint = rightBot;
    }else if (direction == "Stanga"){
        firstPoint = leftTop;
        secondPoint = leftBot;
    }else if (direction == "StangaJos"){
        firstPoint = leftTop;
        secondPoint = leftBot;
    }else if (direction == "StangaSus"){
        firstPoint = leftTop;
        secondPoint = leftBot;
    }else if (direction == "Sus"){
        firstPoint = leftTop;
        secondPoint = rightTop;
    }else if (direction == "Jos"){
        firstPoint = leftBot;
        secondPoint = rightBot;
    }
    directionLine = FicLine(firstPoint, secondPoint);
    
}
void Commander::getEnemyPosi(FicPoint myPosition,FicPoint enemyPosition){
    
    if(isUpperLeft(myPosition,enemyPosition){
        cout<<"Enemy is Lower Right"<<endl;
    }
    if(isLowerLeft(myPosition,enemyPosition){
        cout<<"Enemy is Upper Right"<<endl;
    }
    if(isUpperRight(myPosition,enemyPosition){
        cout<<"Enemy is Lower Lef"<<endl;
       }
    if(isLowerRight(myPosition,enemyPosition){
        cout<<"Enemy is Upper Left"<<endl;
    }
}
                
FicPoint Commander::getLineCenter(){
    
    return FicPoint( ( directionLine.getFirst().getX() + directionLine.getSecond().getX() ) / 2, ( directionLine.getFirst().getY() + directionLine.getSecond().getY() ) / 2 );
}

string Commander::getDirection() {
    return direction;
}

bool Commander::hasDirection() {
    return (direction != "");
}
