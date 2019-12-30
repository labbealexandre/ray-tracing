#include <vector>

class LIGHT_SOURCE {
    
    private:
        std::vector<float> position;
        
    public:
        std::vector<float> getIncidentRay(std::vector<float>);
        std::vector<float> getReflectedRay(std::vector<float> P, std::vector<float> N);

        /** Constructors */
        LIGHT_SOURCE() {
            for(int i = 0; i < 3; i++) {
                position.push_back(0);
            }
        }

        LIGHT_SOURCE(float x, float y, float z) {
            position.push_back(x);
            position.push_back(y);
            position.push_back(z);
        }

        /** Destructor */
        ~LIGHT_SOURCE();
};