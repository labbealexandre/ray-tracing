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