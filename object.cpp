#include "object.hpp"

std::vector<float> SCENE_BASE_OBJECT::getIllumination(
    std::vector<float> L,
    std::vector<float> N,
    std::vector<float> V,
    std::vector<float> R
){
    return (L*N)*surface.diffuse_coefficient+(V*R)*surface.specular_coefficient;
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

template <typename T>
std::vector<T> operator + (std::vector<T> const& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < left.size(); i++) {
            res[i] = left[i] + right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
std::vector<T> operator - (std::vector<T> const& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < left.size(); i++) {
            res[i] = left[i] - right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
std::vector<T> operator / (std::vector<T> const& left, T const& right) {
    std::vector<T> res(left.size());
    for (unsigned int i = 0; i < left.size(); i++) {
        res[i] = left[i] / right;
    }

    return res;
}

template <typename T>
std::vector<T> normalise (std::vector<T> const& vec) {
    std::vector<T> res(vec.size());
    T norm = 0;
    for (unsigned int i = 0; i < vec.size(); i++) {
        norm = sqrt(norm*norm + vec[i]*vec[i]);
    }
    res = vec / norm;
    return res;
}

template <typename T>
T operator * (std::vector<T> const& left, std::vector<T> const& right) {
    T res = 0;
    if (left.size() == right.size()) {
        res+= left[0] * right[0];
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
std::vector<float> CrossProduct(std::vector<T> const& a, std::vector<T> const& b) {
  std::vector<T> r (a.size());
  r[0] = a[1]*b[2]-a[2]*b[1];
  r[1] = a[2]*b[0]-a[0]*b[2];
  r[2] = a[0]*b[1]-a[1]*b[0];
  return r;
}

std::vector<float> PLAN_OBJECT::getNormal(){
    return norm;
}

std::vector<float> PLAN_OBJECT::getIntersection(RAY L, int &code){
    code=0;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    if (D*norm!=0) {
      float param=(1/(D*norm))*(center-S)*norm;
      return S+param*D;
    }else {
      code=-1;
      return S;
    }
}


std::vector<float> TRIANGLE_OBJECT::getNormal(){
    return CrossProduct((puntodos-puntouno),(puntotres-puntouno));
}

std::vector<float> TRIANGLE_OBJECT::getIntersection(RAY L, int &code){
    code=0;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    std::vector<float> norm;
    norm=this->getNormal();
    if (D*norm!=0) {
      float param=(1/(D*norm))*(center-S)*norm;
      std::vector<float> intertemp=S+param*D;
      float a , b , c;
      a=CrossProduct((puntodos-puntouno),(intertemp-puntouno))*CrossProduct((intertemp-puntouno),(puntotres-puntouno));
      b=CrossProduct((puntouno-puntodos),(intertemp-puntodos))*CrossProduct((intertemp-puntodos),(puntotres-puntodos));
      c=CrossProduct((puntouno-puntotres),(intertemp-puntotres))*CrossProduct((intertemp-puntotres),(puntodos-puntotres));
      if (a>=0 && b>=0 && c>=0) {
        return intertemp;
      } else {
        code=-1;
        return S;
      }
    }else {
      code=-1;
      return S;
    }
}
