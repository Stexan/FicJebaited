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
    
 private:
    std::string direction;
    FicLine directionLine;
    
};
