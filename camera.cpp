#include "camera.hpp"

std::vector<RAY> Camera::traceRays() {
    
    /** Initialisation of the rays data **/

    std::vector<float> direction{0, 0, 0};
    std::vector<float> pixel_pos{0, 0, 0};

    RAY ray(pixel_pos, direction);

    std::vector<RAY> rays(pixels_per_column* pixels_per_row, ray);

    for (int i = 0; i < pixels_per_row; i++) {
        for (int j = 0; j < pixels_per_column; j++) {  
            rays.push_back(ray);}
    }

    /** Paralization of the ray computation **/

    int nb_taches;
    # pragma omp parallel private(nb_taches) 
    {
        nb_taches=omp_get_num_threads();
        #pragma omp for schedule( static, pixels_per_row/nb_taches) nowait
        for (int i = 0; i < pixels_per_row; i++) {
            for (int j = 0; j < pixels_per_column; j++) {

                // the origins of the initial rays are the pixels of the camera
                // they have different directions to spread accross the scene
                // which all depends on the focal distance

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