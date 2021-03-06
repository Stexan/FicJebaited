#include "Commander.h"
#include <tuple>
#include <iostream>
#include <cassert>
#include <math.h>

using namespace std;

bool isLowerLeft(FicPoint myPosition, FicPoint enemyPosition){
    return myPosition.getX() > enemyPosition.getX() && myPosition.getY() > enemyPosition.getY();
}
bool isLowerRight(FicPoint myPosition, FicPoint enemyPosition){
    return myPosition.getX() < enemyPosition.getX() && myPosition.getY() > enemyPosition.getY();
}
bool isUpperLeft(FicPoint myPosition,FicPoint enemyPosition){
    return myPosition.getX() > enemyPosition.getX() && myPosition.getY() < enemyPosition.getY();
}
bool isUpperRight(FicPoint myPosition,FicPoint enemyPosition){
    return myPosition.getX() < enemyPosition.getX() && myPosition.getY() < enemyPosition.getY();
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
void Commander::getEnemyPosition(FicPoint myPosition,FicPoint enemyPosition){

    if (isUpperLeft(myPosition,enemyPosition)){
        cout<<"Enemy is Lower Right"<<endl;
    }
    if (isLowerLeft(myPosition,enemyPosition)){
        cout<<"Enemy is Upper Right"<<endl;
    }
    if (isUpperRight(myPosition,enemyPosition)){
        cout<<"Enemy is Lower Lef"<<endl;
       }
    if (isLowerRight(myPosition,enemyPosition)){
        cout<<"Enemy is Upper Left"<<endl;
    }
}
FicPoint Commander::getLineCenter(){

    return FicPoint( ( directionLine.getFirst().getX() + directionLine.getSecond().getX() ) / 2, ( directionLine.getFirst().getY() + directionLine.getSecond().getY() ) / 2 );
}

//me x1, y1, enemy x2, y2
bool Commander::fitsEquation(FicPoint p1, FicPoint p2){

    
    //center of my forward direction - x0, y0
    /*
    double a = p1.getY() - p2.getY();
    double b = p2.getX() - p1.getX();
    double c = p2.getY() * p1.getX() - p1.getY() * p2.getX();
    cout<<"a: "<<a<<"\n";
    cout<<"b: "<<b<<"\n";
    cout<<"c: "<<c<<"\n";

    double m = -a/b;
    cout<<"m: "<<m<<"\n";

    if (m >= -thresh && m <= thresh) {
        return true;
    }
    */
    double thresh = 5;
    FicPoint center = this->getLineCenter();
    
    double x0 = center.getX(); double y0 = center.getY();
    double x1 = p1.getX(); double y1 = p1.getY();
    double x2 = p2.getX(); double y2 = p2.getY();
    
    double top = (x2 - x1) * (y1 - y0) - (x1 - x0) * (y2 - y1);
    double bot = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    
    double distance = top / bot;
    cout<<"distance: "<<distance<<"\n";
    
    if (distance >= -thresh && distance <= thresh) {
        return true;
    }
    return false;
}

bool Commander::isInBoundingBox(FicPoint botLeft, FicPoint botRight, FicPoint topLeft, FicPoint topRight, FicPoint robot){

    return (robot.getX() >= topLeft.getX() && robot.getX() <= topRight.getX()
            && robot.getY() >= topLeft.getY() && robot.getY() <= botLeft.getY());

}

string Commander::getDirection() {
    return direction;
}

bool Commander::hasDirection() {
    return (direction != "");
}
