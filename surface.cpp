#include "surface.hpp"

void OBJECT_BASE_SURFACE::getColors(
    std::vector<int>& incident,
    std::vector<int>& reflected,
    std::vector<int>& transmitted,
    std::vector<int>& absorbed)
{
    reflected = multiply(reflexion_coefficient, incident);
    transmitted = multiply(transmission_coefficient, incident);
    absorbed = multiply(absorption_coefficient, incident);
}

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

void OBJECT_BASE_SURFACE::print(){
    std::cout << "reflexion ";
    for (int i = 0; i < 3; i++)
        std::cout << reflexion_coefficient[i] << " ";
    std::cout << std::endl;
    std::cout << "transmission ";
    for (int i = 0; i < 3; i++)
        std::cout << transmission_coefficient[i] << " ";
    std::cout << std::endl;
    std::cout << "absorption ";
    for (int i = 0; i < 3; i++)
        std::cout << absorption_coefficient[i] << " ";
    std::cout << std::endl;
    std::cout << "diffuse ";
    for (int i = 0; i < 3; i++)
        std::cout << diffuse_coefficient[i] << " ";
    std::cout << std::endl;
    std::cout << "specular ";
    for (int i = 0; i < 3; i++)
        std::cout << specular_coefficient[i] << " ";
    std::cout << std::endl;
}