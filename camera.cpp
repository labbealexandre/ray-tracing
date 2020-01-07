#include <vector>
#include "camera.hpp"

std::vector<std::vector<float>> CAMERA::traceRays() {
    std::vector<std::vector<float>> rays;
    for (int i = 0; i < pixel_per_row; i++) {
        for (int j = 0; j < pixel_per_row; j++) {
            std::vector<float> ray;
            ray.push_back(focal);
            ray.push_back(focal + (i-pixel_per_row/2)*width/pixel_per_row);
            ray.push_back(focal + (j-pixel_per_row/2)*width/pixel_per_row);

            // TODO : normalize ray
            rays.push_back(ray);
        }
    }
    return rays;
}