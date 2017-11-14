#include "Commander.h"
#include <tuple>
#include <iostream>
#include <cassert>

using namespace std;

bool isLowerLeft(pair<double, double> myPosition, pair<double, double> enemyPosition){
  return myPosition.first > enemyPosition.first && myPosition.second > enemyPosition.second;
}
bool isLowerRight(pair<double, double> myPosition, pair<double, double> enemyPosition){
  return myPosition.first < enemyPosition.first && myPosition.second > enemyPosition.second;
}
bool isUpperLeft(pair<double, double> myPosition, pair<double, double> enemyPosition){
  return myPosition.first > enemyPosition.first && myPosition.second < enemyPosition.second;
}
bool isUpperRight(pair<double, double> myPosition,pair<double, double> enemyPosition){
  return myPosition.first < enemyPosition.first && myPosition.second < enemyPosition.second;
}

const char* Commander::getDirection(pair<double, double> oldC, pair<double, double> newC){

  int threshold = 2;
  if (newC.first - oldC.first > threshold){
    if (newC.second - oldC.second > threshold){
      return "DreaptaJos";
    }else if (newC.second - oldC.second < -threshold){
      return "DreaptaSus";
    }else{
      return "Dreapta";
    }
  }else if (newC.first - oldC.first < -threshold){
    if (newC.second - oldC.second > threshold){
      return "StangaJos";
    }else if (newC.second - oldC.second < -threshold){
      return "StangaSus";
    }else{
      return "Stanga";
    }
  }else{
    if (newC.second - oldC.second > threshold){
      return "Jos";
    }else if (newC.second - oldC.second < -threshold){
      return "Sus";
    }else{
      return "Static";
    }
    assert("reached end of getDirection");
  }

}

void Commander::go(pair<double, double> myPosition, pair<double, double> enemyPosition){

  if (isLowerLeft(myPosition, enemyPosition)){
    cout<<"Lower Left";
  }else if (isLowerRight(myPosition, enemyPosition)){
      cout<<"Lower Right";
  }else if (isUpperLeft(myPosition, enemyPosition)){
      cout<<"Upper Left";
  }else if (isUpperRight(myPosition, enemyPosition)){
      cout<<"Upper Right";
  }

}
