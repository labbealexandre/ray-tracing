#include "camera.hpp"

using namespace std;

vector<Ray> Camera::traceRays() {
    
    /** Initialisation of the rays data **/

    vector<float> direction{0, 0, 0};
    vector<float> pixel_pos{0, 0, 0};

    Ray ray(pixel_pos, direction);

    vector<Ray> rays(pixels_per_column* pixels_per_row, ray);

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

                vector<float> direction;
                vector<float> pixel_pos;
                pixel_pos.push_back(position[0]);
                pixel_pos.push_back(position[1] + (i-pixels_per_row/2)*width/pixels_per_row);
                pixel_pos.push_back(position[2] + (j-pixels_per_column/2)*height/pixels_per_column);

                direction.push_back(focal);
                direction.push_back((i-pixels_per_row/2)*width/pixels_per_row);
                direction.push_back((j-pixels_per_column/2)*height/pixels_per_column);
                direction = normalise(direction);

                Ray ray(pixel_pos, direction);
                rays[i*pixels_per_column+j]=ray;
            }
        }
    }
    return rays;
}