#include <tuple>

class Commander {
 public:
   void go(std::pair<double, double> myPosition, std::pair<double, double> enemyPosition);
   const char* getDirection(std::pair<double, double> oldC, std::pair<double, double> newC);
};
