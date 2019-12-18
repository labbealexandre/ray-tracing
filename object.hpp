#include <vector>
#include <iostream>
#include "surface.hpp"

class SCENE_BASE_OBJECT {
    private:
        std::vector<float> center;
        OBJECT_BASE_SURFACE surface;

    public:

        // TODO Now
        std::vector<int> getIllumination(std::vector<float> L, std::vector<float> N, std::vector<float> V);

        // TODO Later for recursive points
        std::vector<float> getReflectedRayDirection(std::vector<float> V, std::vector<float> N);
        std::vector<float> getRefractedRay(std::vector<float> V, std::vector<float> N);
};

class SPHERE_OBJECT : public SCENE_BASE_OBJECT{
    public:

        std::vector<float> getNormal(std::vector<float>);
        std::vector<float> getIntersection(std::vector<float>);
};