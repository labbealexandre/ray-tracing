#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <vector>
#include "utils.hpp"

class LIGHT_SOURCE {

    private:
        std::vector<float> position;

    public:
        std::vector<int> illumination;

        std::vector<float> getPosition();
        std::vector<float> getIncidentRay(std::vector<float> P);
        std::vector<float> getReflectedRay(std::vector<float> P, std::vector<float> N);

        /** Constructors */
        LIGHT_SOURCE() {
            for(int i = 0; i < 3; i++) {
                position.push_back(0);
                illumination.push_back(255);
            }
        }

        LIGHT_SOURCE(std::vector<float> P, std::vector<int> I) {
            position = P;
            illumination = I;
        }

        /** Destructor */
        ~LIGHT_SOURCE(){}
};

#endif
