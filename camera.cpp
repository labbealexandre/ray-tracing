#include <vector>
#include "camera.hpp"
#include "utils.hpp"

std::vector<RAY> CAMERA::traceRays() {
    std::vector<RAY> rays;
    for (int i = 0; i < pixel_per_row; i++) {
        for (int j = 0; j < pixel_per_row; j++) {

            std::vector<float> direction;
            direction.push_back(focal);
            direction.push_back(focal + (i-pixel_per_row/2)*width/pixel_per_row);
            direction.push_back(focal + (j-pixel_per_row/2)*width/pixel_per_row);
            direction = normalise(direction);

            RAY ray(position, direction, color);
            // TODO : normalize direction
            rays.push_back(ray);
        }
    }
    return rays;
}