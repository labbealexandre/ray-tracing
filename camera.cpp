#include "camera.hpp"

std::vector<RAY> Camera::traceRays() {
    std::vector<RAY> rays;
    for (int i = 0; i < pixels_per_row; i++) {
        for (int j = 0; j < pixels_per_column; j++) {

            std::vector<float> direction;
            std::vector<float> pixel_pos;
            pixel_pos.push_back(position[0]);
            pixel_pos.push_back(position[1] + (i-pixels_per_row/2)*width/pixels_per_row);
            pixel_pos.push_back(position[2] + (j-pixels_per_column/2)*height/pixels_per_column);

            direction.push_back(focal);
            direction.push_back((i-pixels_per_row/2)*width/pixels_per_row);
            direction.push_back((j-pixels_per_column/2)*height/pixels_per_column);
            direction = normalise(direction);

            RAY ray(pixel_pos, direction);
            rays.push_back(ray);
        }
    }
    return rays;
}