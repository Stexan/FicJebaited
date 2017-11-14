#include "Commander.h"
#include <tuple>
#include <iostream>

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
