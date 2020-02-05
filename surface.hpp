#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <iostream>
#include "texture.hpp"

class OBJECT_BASE_SURFACE {

    public:
        TEXTURE texture;
        std::vector<float> transmission_coefficient;
        std::vector<float> ambiant_coefficient;
        std::vector<float> reflexion_coefficient;
        std::vector<float> diffuse_coefficient;
        std::vector<float> specular_coefficient;

        void print();

        /** Constructors */
        OBJECT_BASE_SURFACE() {
            for (int i = 0; i < 3; i++) {
                ambiant_coefficient.push_back(1);
                reflexion_coefficient.push_back(1);
                transmission_coefficient.push_back(0);
                diffuse_coefficient.push_back(1);
                specular_coefficient.push_back(0);
            }
        }

        OBJECT_BASE_SURFACE(
            TEXTURE T,
            std::vector<float> &a,
            std::vector<float> &r,
            std::vector<float> &t,
            std::vector<float> &d,
            std::vector<float> &s)
        {
            texture = T;
            ambiant_coefficient = a;
            reflexion_coefficient = r;
            transmission_coefficient = t;
            diffuse_coefficient = d;
            specular_coefficient = s;
        }

        /** Destructor */
        ~OBJECT_BASE_SURFACE(){}
};

std::vector<int> multiply(std::vector<float>&, std::vector<int>&);

#endif