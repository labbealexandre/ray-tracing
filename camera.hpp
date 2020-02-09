#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <iostream>
#include "ray.hpp"
#include "utils.hpp"

class Camera {
    private:
        
        float focal;
        int pixels_per_row;
        int pixels_per_column;

    public:
        std::vector<float> position;
        float width;
        float height;

        std::vector<RAY> traceRays();

        Camera() {
            for (int i = 0; i < 3; i++) {
                position.push_back(0);
            }
            width = 50;
            height = 50;
            focal = 10;
        }

        Camera(std::vector<float> &P, float W, float H, float F, int p_r, int p_c) {
            position = P;
            width = W;
            height = H;
            focal = F;
            pixels_per_row = p_r;
            pixels_per_column = p_c;
        }

        /** Destructor */
        ~Camera(){}
    
};

#endif