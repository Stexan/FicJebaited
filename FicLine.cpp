#import "FicLine.h"

FicLine::FicLine(){
    first = FicPoint(0,0);
    second = FicPoint(0,0);
}

FicLine::FicLine(FicPoint firstCoord, FicPoint secondCoord){
    first = firstCoord;
    second = secondCoord;
}

FicPoint FicLine::getSecond(){
    return second;
}

FicPoint FicLine::getFirst(){
    return first;
}

