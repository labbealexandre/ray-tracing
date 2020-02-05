#include "object.hpp"

std::vector<float> SCENE_BASE_OBJECT::getIllumination(
    const std::vector<float>& P,
    const std::vector<float>& L,
    const std::vector<float>& N,
    const std::vector<float>& V,
    const std::vector<float>& R,
    int specular
){
    float s;
    if (V*R > 0) s = V*R;
    else s = 0;
    
    auto I = std::abs((L*N))*prod(surface.diffuse_coefficient, this->getColor(P)) +
              (float)pow(s, specular)*surface.specular_coefficient;
            
    capCoefs(I);
    return I;
}

std::vector<float> SCENE_BASE_OBJECT::getNormal(std::vector<float> P){
    std::vector<float> N;
    return N;
}

std::vector<float> SCENE_BASE_OBJECT::getIntersection(RAY L, int &code){
    std::vector<float> I;
    return I;
}

std::vector<float> SCENE_BASE_OBJECT::getColor(const std::vector<float> &P) {
  std::vector<float> res(3, 1);
  return res;
}

bool SCENE_BASE_OBJECT::isItLit(std::vector<float> P, std::vector<float> positionLight){
  return (this->getNormal(P)*(P-positionLight))<0;
}

void SCENE_BASE_OBJECT::print() {
  std::cout << "center ";
  for (int i = 0; i < 3; i++) 
    std::cout << center[i] << " ";
  std::cout << std::endl;
  surface.print();
}

void SCENE_BASE_OBJECT::name() {
  std::cout << "I am a simple object" << std::endl;
}

std::vector<float> SCENE_BASE_OBJECT::getReflectedRayDirection(std::vector<float> V, std::vector<float> N) {
  return normalise(V - 2*(V*N)*N);
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


void SPHERE_OBJECT::print(){
  SCENE_BASE_OBJECT::print();
  std::cout << "radius " << radius << std::endl;
}

void SPHERE_OBJECT::name(){
  std::cout << "I am a sphere" << std::endl;
}

std::vector<float> PLAN_OBJECT::getNormal(){
    return normal;
}

std::vector<float> PLAN_OBJECT::getNormal(std::vector<float> P){
    return normal;
}

std::vector<float> PLAN_OBJECT::getIntersection(RAY L, int &code) {
    code=1;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    if (D*normal<0) {
      float param=(1/(D*normal))*(center-S)*normal;
      return S+param*D;
    }else {
      code=0;
      return S;
    }
}

std::vector<float> PLAN_OBJECT::getColor(const std::vector<float> &P) {
  
  std::vector<float> U = P-surface.texture.center;

  std::vector<float> X = surface.texture.direction;
  float x = std::fmod(U*X, surface.texture.width);
  if (x < 0) x += surface.texture.width;

  std::vector<float> Y = CrossProduct(normal, X);
  float y = std::fmod(U*Y, surface.texture.height);
  if (y < 0) y += surface.texture.height;

  std::vector<std::vector<float>> colors = *surface.texture.p_colors;

  return colors[(int)x*surface.texture.height+(int)y];
}

void PLAN_OBJECT::print(){
  SCENE_BASE_OBJECT::print();
  std::cout << "normal ";
  for (int i = 0; i < 3; i++)
    std::cout << normal[i] << " ";
  std::cout << std::endl;
}

void PLAN_OBJECT::name(){
  std::cout << "I am a plan" << std::endl;
}

std::vector<float> TRIANGLE_OBJECT::getNormal(){
    return CrossProduct((puntodos-puntouno),(puntotres-puntouno));
}

std::vector<float> TRIANGLE_OBJECT::getNormal(std::vector<float> P){
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

void TRIANGLE_OBJECT::print(){
  SCENE_BASE_OBJECT::print();
}

void TRIANGLE_OBJECT::name(){
  std::cout << "I am a triangle" << std::endl;
}