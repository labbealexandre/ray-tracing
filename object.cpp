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