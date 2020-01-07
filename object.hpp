#include <vector>
#include <iostream>
#include "surface.hpp"
#include "source.hpp"
#include "utils.hpp"

class SCENE_BASE_OBJECT {
    private:
        std::vector<float> center;
        OBJECT_BASE_SURFACE surface;

    public:

        // TOTEST Now
        std::vector<int> getIllumination(std::vector<float> L, std::vector<float> N, std::vector<float> V);

        // TODO Later for recursive points
        std::vector<float> getReflectedRayDirection(std::vector<float> V, std::vector<float> N);
        std::vector<float> getRefractedRay(std::vector<float> V, std::vector<float> N);
        /** Constructors */
        SCENE_BASE_OBJECT() {
            for(int i = 0; i < 3; i++) {
                center.push_back(0);
            }
        }

        /** Destructor */
        ~SCENE_BASE_OBJECT();
};

class SPHERE_OBJECT : public SCENE_BASE_OBJECT{
    private:
      float radius;
    public:

        std::vector<float> getNormal(std::vector<float> P);
        std::vector<float> getIntersection(std::vector<float> source);

        /** Constructors */
        SPHERE_OBJECT(std::vector<float> centre, float r) {
          center=centre;
          radius=r;
        }

        /** Destructor */
        ~SPHERE_OBJECT();

};
