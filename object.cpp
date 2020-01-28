#include "object.hpp"

std::vector<float> SCENE_BASE_OBJECT::getIllumination(
    std::vector<float> L,
    std::vector<float> N,
    std::vector<float> V,
    std::vector<float> R
){
    auto I = std::abs((L*N))*surface.diffuse_coefficient+std::abs((V*R))*surface.specular_coefficient;
    for (int i = 0; i < 3; i++) {
      if(I[i] > 1)
      I[i]=1;
    }
    return I;
}

std::vector<float> SPHERE_OBJECT::getNormal(std::vector<float> P){
    std::vector<float> N;
    return normalise(P-center);
}

std::vector<float> SPHERE_OBJECT::getIntersection(RAY L, int &code){
    code=1;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    std::vector<float> V=S-center;
    float t;
    if (pow(V*D,2)>(V*V-pow(radius,2))) {
      if (V*D<-sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
        t=-(V*D)-sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
        return S+t*D;
      } else if (V*D<sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
        t=-(V*D)+sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
        return S+t*D;
      }
    }
    code=0;
    return S;
}

std::vector<float> PLAN_OBJECT::getNormal(){
    return normal;
}

std::vector<float> PLAN_OBJECT::getIntersection(RAY L, int &code){
    code=1;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    if (D*normal!=0) {
      float param=(1/(D*normal))*(center-S)*normal;
      return S+param*D;
    }else {
      code=0;
      return S;
    }
}


std::vector<float> TRIANGLE_OBJECT::getNormal(){
    return CrossProduct((puntodos-puntouno),(puntotres-puntouno));
}

std::vector<float> TRIANGLE_OBJECT::getIntersection(RAY L, int &code){
    code=1;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    std::vector<float> normal;
    normal=this->getNormal();
    if (D*normal!=0) {
      float param=(1/(D*normal))*(center-S)*normal;
      std::vector<float> intertemp=S+param*D;
      float a , b , c;
      a=CrossProduct((puntodos-puntouno),(intertemp-puntouno))*CrossProduct((intertemp-puntouno),(puntotres-puntouno));
      b=CrossProduct((puntouno-puntodos),(intertemp-puntodos))*CrossProduct((intertemp-puntodos),(puntotres-puntodos));
      c=CrossProduct((puntouno-puntotres),(intertemp-puntotres))*CrossProduct((intertemp-puntotres),(puntodos-puntotres));
      if (a>=0 && b>=0 && c>=0) {
        return intertemp;
      } else {
        code=0;
        return S;
      }
    }else {
      code=0;
      return S;
    }
}
