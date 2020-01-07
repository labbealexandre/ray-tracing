#include <vector>
#include "source.hpp"
#include "utils.hpp"
#include "object.hpp"

std::vector<int> getIllumination(std::vector<float> L, std::vector<float> N, std::vector<float> V, ){
    return surface.diffuse_coefficient*(L*N)+surface.specular_coefficient*(V*getReflectedRay(L,N))
}

std::vector<float> getNormal(std::vector<float> P){
        std::vector<float> N;
        N=(P-centre)/radius
}

std::vector<float> getIntersection(std::vector<float>){

}
