#include <vector>

class LIGHT_SOURCE {
    
    private:
        std::vector<float> position;
        
    public:
        std::vector<float> getIncidentRay(std::vector<float>);
        std::vector<float> getReflectedRay(std::vector<float> P, std::vector<float> N);
};