#ifndef RAY_HPP
#define RAY_HPP

#include <vector>
class RAY {
    public:
        std::vector<float> origin;
        std::vector<float> direction;
        std::vector<int> colors;

        RAY() {
            origin = {0,0, 0};
            direction = {0, 0, 0};
            colors = {0, 0, 0}; 
        }

        RAY(std::vector<float> O, std::vector<float> U) {
            origin = O;
            direction = U;  //direction needs to be normalized!
            colors = {0, 0, 0};
        }

        ~RAY(){}
};

#endif