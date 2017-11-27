#include <tuple>
#include <string>
#include "FicLine.h"

class Commander {
 public:
    bool hasDirection();
    std::string getDirection();
   
    void go(FicPoint myPosition, FicPoint enemyPosition);
    void findDirection(FicPoint oldC, FicPoint newC);
    void calcDirectionLine(FicPoint leftTop, FicPoint leftBot, FicPoint rightTop, FicPoint rightBot);
    FicPoint getLineCenter();
    void getEnemyPosition(FicPoint myPosition,FicPoint enemyPosition);
    bool fitsEquation(FicPoint p1, FicPoint p2);
    bool isInBoundingBox(FicPoint botLeft, FicPoint botRight, FicPoint topLeft, FicPoint topRight, FicPoint robot);
    
 private:
    std::string direction;
    FicLine directionLine;
    
};
