#include "surface.hpp"

using namespace std;

vector<int> multiply(vector<float> &coef, vector<int> &colors) {
    vector<int> res;
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
    cout << reflexion_coefficient << " ";
    cout << transmission_coefficient << " ";
    cout << diffuse_coefficient << " ";
    cout << specular_coefficient << " ";
}