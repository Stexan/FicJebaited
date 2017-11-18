#include "FicPoint.h"

class FicLine {
public:
    FicLine();
    FicLine(FicPoint firstCoord, FicPoint secondCoord);
    
    FicPoint getFirst();
    FicPoint getSecond();
private:
    FicPoint first;
    FicPoint second;
};
