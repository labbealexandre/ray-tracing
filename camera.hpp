#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <iostream>
#include "ray.hpp"
#include "utils.hpp"

class CAMERA {
    private:
        std::vector<float> position;
        float focal;
        int pixels_per_row;
        int pixels_per_column;

    public:

        float width;
        float height;

        std::vector<RAY> traceRays();

        CAMERA() {
            for (int i = 0; i < 3; i++) {
                position.push_back(0);
            }
            width = 50;
            height = 50;
            focal = 10;
        }

        CAMERA(std::vector<float> &P, float W, float H, float F, int p_r, int p_c) {
            position = P;
            width = W;
            height = H;
            focal = F;
            pixels_per_row = p_r;
            pixels_per_column = p_c;
        }

        /** Destructor */
        ~CAMERA(){}
    
};

#endif