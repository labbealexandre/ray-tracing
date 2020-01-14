#include "camera.hpp"

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
            rays.push_back(ray);
        }
    }
    return rays;
}

template <typename T>
std::vector<T> operator / (std::vector<T> const& left, T const& right) {
    std::vector<T> res(left.size());
    for (unsigned int i = 0; i < left.size(); i++) {
        res[i] = left[i] / right;
    }

    return res;
}

template <typename T>
std::vector<T> normalise (std::vector<T> const& vec) {
    std::vector<T> res(vec.size());
    T norm = 0;
    for (unsigned int i = 0; i < vec.size(); i++) {
        norm = sqrt(norm*norm + vec[i]*vec[i]);
    }
    res = vec / norm;
    return res;
}