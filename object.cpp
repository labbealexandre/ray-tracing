#include <vector>
#include "source.hpp"
#include "utils.hpp"
#include "object.hpp"
#include <math.h>

std::vector<int> getIllumination(std::vector<float> L, std::vector<float> N, std::vector<float> V, ){
    return surface.diffuse_coefficient*(L*N)+surface.specular_coefficient*(V*getReflectedRay(L,N))
}

std::vector<float> getNormal(std::vector<float> P){
        std::vector<float> N;
    N=(P-centre)/radius;
}

std::vector<float> getIntersection(RAY L, int &code){
    code=0
    std::vector<float> S=L->origin;
    std::vector<float> D=L->direction;
    std::vector<float> V=S-center;
    float t;
    if (pow(V*D,2)>(V*V-pow(radius,2))) {
      if (V*D<-sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
        t=-V*D-sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
        return S+t*D
      } else if (V*D<sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
        t=-V*D+sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
        return S+t*D
      }
    }else {
      code=-1
      return S;
    }
}
