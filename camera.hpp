#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include "ray.hpp"
#include "utils.hpp"

class CAMERA {
    private:
        std::vector<float> position;
        float focal;
        int pixel_per_row;
        int pixel_per_column;
        std::vector<int> color;

    public:

        float width;
        float height;

        std::vector<RAY> traceRays();

        CAMERA() {
            for (int i = 0; i < 3; i++) {
                position.push_back(0);
                color.push_back(255);
            }
            width = 50;
            height = 50;
            focal = 10;
        }

        CAMERA(std::vector<float> &P, float W, float H, float F, std::vector<int> &C) {
            position = P;
            width = W;
            height = H;
            focal = F;
            color = C;
        }

        /** Destructor */
        ~CAMERA(){}
    
};

#endif