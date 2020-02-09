#include "camera.hpp"

std::vector<RAY> Camera::traceRays() {
    std::vector<RAY> rays;
    std::vector<float> direction;
    std::vector<float> pixel_pos;
    for (int k = 0; k < 3; k++)
    {
        pixel_pos.push_back(0);
        direction.push_back(0);
    }
    RAY ray(pixel_pos, direction);
    for (int i = 0; i < pixels_per_row; i++) {
        for (int j = 0; j < pixels_per_column; j++) {  
            rays.push_back(ray);}
    }
    int nb_taches;
    # pragma omp parallel private(nb_taches) 
    {
        nb_taches=omp_get_num_threads();
        #pragma omp for schedule( static , pixels_per_row/nb_taches) nowait
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
                rays[i*pixels_per_column+j]=ray;
            }
        }
    }
    return rays;
}