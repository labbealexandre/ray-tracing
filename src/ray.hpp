#ifndef RAY_HPP
#define RAY_HPP

#include <vector>
class Ray {
    public:
        std::vector<float> origin;
        std::vector<float> direction;
        std::vector<int> colors;

        Ray() {
            origin = {0,0, 0};
            direction = {0, 0, 0};
            colors = {0, 0, 0}; 
        }

        Ray(std::vector<float> O, std::vector<float> U) {
            origin = O;
            direction = U; 
            colors = {0, 0, 0};
        }

        ~Ray(){}
};

#endif