#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <vector>
#include <iostream>
#include "utils.hpp"

class LightSource {

    private:
        std::vector<float> position;

    public:
        std::vector<int> illumination;

        std::vector<float> getPosition();
        std::vector<float> getIncidentRay(std::vector<float> P);
        std::vector<float> getReflectedRay(std::vector<float> P, std::vector<float> N);

        /** Constructors */
        LightSource() {
            for(int i = 0; i < 3; i++) {
                position.push_back(0);
                illumination.push_back(255);
            }
        }

        LightSource(std::vector<float> P, std::vector<int> I) {
            position = P;
            illumination = I;
        }

        /** Destructor */
        ~LightSource(){}
};

#endif
