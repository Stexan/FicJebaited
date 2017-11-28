#include "FicPoint.h"

FicPoint::FicPoint(){
    x = 0;
    y = 0;
}

FicPoint::FicPoint(double xCoord, double yCoord){
    x = xCoord;
    y = yCoord;
}

double FicPoint::getX(){
    return x;
}

double FicPoint::getY(){
    return y;
}

