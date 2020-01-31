#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <iostream>

class OBJECT_BASE_SURFACE {
    private:
        std::vector<float> reflexion_coefficient;
        std::vector<float> transmission_coefficient;
        std::vector<float> absorption_coefficient;
    public:
        std::vector<float> diffuse_coefficient;
        std::vector<float> specular_coefficient;

        void getColors(
            std::vector<int>& incident,
            std::vector<int>& reflected,
            std::vector<int>& transmitted,
            std::vector<int>& absorbed
        );

        void print();

        /** Constructors */
        OBJECT_BASE_SURFACE() {
            for (int i = 0; i < 3; i++) {
                reflexion_coefficient.push_back(1);
                transmission_coefficient.push_back(0);
                absorption_coefficient.push_back(0);
                diffuse_coefficient.push_back(1);
                specular_coefficient.push_back(0);
            }
        }

        OBJECT_BASE_SURFACE(
            std::vector<float> &r,
            std::vector<float> &t,
            std::vector<float> &d,
            std::vector<float> &s)
        {
            reflexion_coefficient = r;
            transmission_coefficient = t;
            for (int i = 0; i < 3; i++) {
                absorption_coefficient.push_back(1-r[i]-t[i]);
            }
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