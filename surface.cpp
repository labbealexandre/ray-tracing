#include "surface.hpp"

std::vector<int> multiply(std::vector<float> &coef, std::vector<int> &colors) {
    std::vector<int> res;
    if (coef.size() != colors.size()) {
        // TODO : handle error
    } else {
        for (int i = 0; i < 3; i++) {
            res.push_back((int)coef[i]*colors[i]);
        }
    }
    return res;
}

void Surface::print(){
    std::cout << reflexion_coefficient << " ";
    std::cout << transmission_coefficient << " ";
    std::cout << diffuse_coefficient << " ";
    std::cout << specular_coefficient << " ";
}