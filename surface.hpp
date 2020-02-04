#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <iostream>

class OBJECT_BASE_SURFACE {

    public:
        std::vector<float> transmission_coefficient;
        std::vector<float> ambiant_coefficient;
        std::vector<float> reflexion_coefficient;
        std::vector<float> diffuse_coefficient;
        std::vector<float> specular_coefficient;

        // void getColors(
        //     std::vector<int>& incident,
        //     std::vector<int>& reflected,
        //     std::vector<int>& transmitted,
        //     std::vector<int>& absorbed
        // );

        void print();

        /** Constructors */
        OBJECT_BASE_SURFACE() {
            for (int i = 0; i < 3; i++) {
                reflexion_coefficient.push_back(1);
                transmission_coefficient.push_back(0);
                diffuse_coefficient.push_back(1);
                specular_coefficient.push_back(0);
            }
        }

        OBJECT_BASE_SURFACE(
            std::vector<float> &a,
            std::vector<float> &r,
            std::vector<float> &t,
            std::vector<float> &d,
            std::vector<float> &s)
        {
            ambiant_coefficient = a;
            reflexion_coefficient = r;
            transmission_coefficient = t;
            diffuse_coefficient = d;
            specular_coefficient = s;

            // for (int i = 0; i < 3; i++) {
            //     std::cout << fid_coefficient[i] << std::endl;
            // }
        }

        /** Destructor */
        ~OBJECT_BASE_SURFACE(){}
};

std::vector<int> multiply(std::vector<float>&, std::vector<int>&);

#endif