#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <iostream>
#include "texture.hpp"

class Surface {

    public:
        Texture texture;
        float transmission_coefficient;
        float reflexion_coefficient;
        float diffuse_coefficient;
        float specular_coefficient;

        void print();

        /** Constructors */
        Surface() {
            reflexion_coefficient = 1;
            transmission_coefficient = 0;
            diffuse_coefficient = 1;
            specular_coefficient = 0;
        }

        Surface(
            Texture T,
            float &r,
            float &t,
            float &d,
            float &s)
        {
            texture = T;
            reflexion_coefficient = r;
            transmission_coefficient = t;
            diffuse_coefficient = d;
            specular_coefficient = s;
        }

        /** Destructor */
        ~Surface(){}
};

std::vector<int> multiply(std::vector<float>&, std::vector<int>&);

#endif