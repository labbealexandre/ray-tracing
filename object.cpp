#include "object.hpp"

std::vector<float> SceneBaseObject::getIllumination(
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

std::vector<float> SceneBaseObject::getNormal(std::vector<float> P){
    std::vector<float> N;
    return N;
}

std::vector<float> SceneBaseObject::getIntersection(RAY L, int &code){
    std::vector<float> I;
    return I;
}

std::vector<float> SceneBaseObject::getColor(const std::vector<float> &P) {
  std::vector<float> res(3, 1);
  return res;
}

bool SceneBaseObject::isItLit(std::vector<float> P, std::vector<float> positionLight, std::vector<SceneBaseObject*> &scene){
  int code;
  std::vector<float> current_P;
  float min_d = sqrt((P-positionLight)*(P-positionLight));
  float epsilon = 1.0;
  RAY ray=RAY(positionLight,normalise(P-positionLight));
  for (auto object : scene) {
    current_P = object->getIntersection(ray, code);
    if (code) {
      float d = sqrt((current_P-positionLight)*(current_P-positionLight));
      if (d < min_d-epsilon) {
        return false;
      }
    }
  }
  return (this->getNormal(P)*(P-positionLight))<0;
}

void SceneBaseObject::print() {
  std::cout << "center ";
  for (int i = 0; i < 3; i++) 
    std::cout << center[i] << " ";
  std::cout << std::endl;
  surface.print();
}

int SceneBaseObject::type() {
  return 0;
}

void SceneBaseObject::name() {
  std::cout << "I am a simple object" << std::endl;
}

std::vector<float> SceneBaseObject::getReflectedRayDirection(std::vector<float> V, std::vector<float> P) {
  std::vector<float> N = this->getNormal(P);
  return normalise(V - 2*(V*N)*N);
}

std::vector<float> SceneBaseObject::getRefractedRayDirection(std::vector<float> V, std::vector<float> P, int& code) {
  std::vector<float> N = this->getNormal(P);
  
  code = 0;
  std::vector<float> res;

  if (V*N < 0) {

    float cosTheta1 = (float)(-1)*normalise(V)*normalise(N);
    float squareCosTheta1 = pow(cosTheta1, 2);

    if (1 - squareCosTheta1 < n2/n1) {
      code = 1;

      float c = sqrt(1 - (1-squareCosTheta1)*pow(n1,2)/pow(n2,2));
      code = 1;
      res = (n1/n2)*V + (cosTheta1*n1/n2 - c)*N;
    }
  }

  return res;
}

std::vector<float> Sphere::getNormal(std::vector<float> P){
    std::vector<float> N;
    return normalise(P-center);
}

std::vector<float> Sphere::getIntersection(RAY L, int &code){
    code=1;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    std::vector<float> V=S-center;
    float t;
    if (V*V > pow(radius, 2)) {
      if (pow(V*D,2)>(V*V-pow(radius,2))) {
        if (V*D<-sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
          t=-(V*D)-sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
          if (t > 0) return S+t*D;
        }
        if (V*D<sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
          t=-(V*D)+sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
          if (t > 0) return S+t*D;
        }
      }
    }
    code = 0;
    return S;
}


void Sphere::print(){
  SceneBaseObject::print();
  std::cout << "radius " << radius << std::endl;
}

void Sphere::name(){
  std::cout << "I am a sphere" << std::endl;
}

int Sphere::type() {
  return 1;
}

std::vector<float> Plan::getNormal(){
    return normal;
}

std::vector<float> Plan::getNormal(std::vector<float> P){
    return normal;
}

std::vector<float> Plan::getIntersection(RAY L, int &code) {
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

std::vector<float> Plan::getColor(const std::vector<float> &P) {
  
  std::vector<float> U = P-surface.texture.center;

  std::vector<float> X = surface.texture.direction;
  float x = std::fmod(U*X, surface.texture.width);
  if (x < 0) x += surface.texture.width;
  int n_x = (int)surface.texture.n*x/surface.texture.width;

  std::vector<float> Y = CrossProduct(normal, X);
  float y = std::fmod(U*Y, surface.texture.height);
  if (y < 0) y += surface.texture.height;
  int n_y = (int)surface.texture.m*y/surface.texture.height;

  int d = n_x*surface.texture.m+n_y;

  std::vector<float>* p_color = surface.texture.p_colors->data() + d;

  return *p_color;
}

void Plan::print(){
  SceneBaseObject::print();
  std::cout << "normal ";
  for (int i = 0; i < 3; i++)
    std::cout << normal[i] << " ";
  std::cout << std::endl;
}

void Plan::name(){
  std::cout << "I am a plan" << std::endl;
}

int Plan::type() {
  return 2;
}

std::vector<float> Triangle::getNormal(){
    // return CrossProduct((B-A),(C-A));
    return normal;
}

std::vector<float> Triangle::getNormal(std::vector<float> P){
    // return CrossProduct((B-A),(C-A));
    return normal;
}

std::vector<float> Triangle::getIntersection(RAY L, int &code){
    code=1;
    std::vector<float> S=L.origin;
    std::vector<float> D=L.direction;
    std::vector<float> normal;
    normal=this->getNormal();
    if (D*normal!=0) {
      float param=(1/(D*normal))*(center-S)*normal;
      std::vector<float> intertemp=S+param*D;
      float a , b , c;
      a=CrossProduct((B-A),(intertemp-A))*CrossProduct((intertemp-A),(C-A));
      b=CrossProduct((A-B),(intertemp-B))*CrossProduct((intertemp-B),(C-B));
      c=CrossProduct((A-C),(intertemp-C))*CrossProduct((intertemp-C),(B-C));
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

void Triangle::print(){
  SceneBaseObject::print();
}

void Triangle::name(){
  std::cout << "I am a triangle" << std::endl;
}

int Triangle::type() {
  return 3;
}