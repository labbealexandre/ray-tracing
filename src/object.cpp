#include "object.hpp"

using namespace std;

vector<float> SceneBaseObject::getIllumination(
    const vector<float>& P,
    const vector<float>& L,
    const vector<float>& N,
    const vector<float>& V,
    const vector<float>& R,
    int specular
){
    float s;
    if (V*R > 0) s = V*R;
    else s = 0;

    auto I = (float)pow(s, specular)*surface.specular_coefficient+
              abs((L*N))*surface.diffuse_coefficient*this->getColor(P);

    capCoefs(I);

    return I;
}

vector<float> SceneBaseObject::getNormal(vector<float> P){
    vector<float> N;
    return N;
}

vector<float> SceneBaseObject::getIntersection(Ray L, int &code){
    vector<float> I;
    return I;
}

vector<float> SceneBaseObject::getColor(const vector<float> &P) {
  return this->surface.colors;
}

bool SceneBaseObject::isItLit(vector<float> P, vector<float> positionLight, vector<SceneBaseObject*> &scene){
  int code;
  vector<float> current_P;
  float min_d = sqrt((P-positionLight)*(P-positionLight));
  float epsilon = 1.0;
  Ray ray=Ray(positionLight,normalise(P-positionLight));
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
  cout << "center ";
  for (int i = 0; i < 3; i++) 
    cout << center[i] << " ";
  cout << endl;
  surface.print();
}

int SceneBaseObject::type() {
  return 0;
}

void SceneBaseObject::name() {
  cout << "I am a simple object" << endl;
}

vector<float> SceneBaseObject::getReflectedRayDirection(vector<float> V, vector<float> P) {
  vector<float> N = this->getNormal(P);
  return normalise(V - 2*(V*N)*N);
}

vector<float> SceneBaseObject::getRefractedRayDirection(vector<float> V, vector<float> P, int& code) {
  vector<float> N = this->getNormal(P);
  
  code = 0;
  vector<float> res;

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

vector<float> Sphere::getNormal(vector<float> P){
    return normalise(P-center);
}

vector<float> Sphere::getIntersection(Ray L, int &code){
    code=1;
    vector<float> S=L.origin;
    vector<float> D=L.direction;
    vector<float> V=S-center;
    float t;
    float epsilon = 1e-02;

    if (sqrt(V*V)>=radius+epsilon){
      if (V*D<-sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
        t=-(V*D)-sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
        return S+t*D;
      }
      if (V*D<sqrt(pow(V*D,2)-(V*V-pow(radius,2)))) {
        t=-(V*D)+sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
        return S+t*D;
      }
    }
    else
    {
      float u,v;
      u=-(V*D)-sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
      v=-(V*D)+sqrt(pow(V*D,2)-(V*V-pow(radius,2)));
      if (u>-epsilon) return S+u*D;
      if (v>-epsilon) return S+v*D;  
    }

    code = 0;
    return S;
}


void Sphere::print(){
  SceneBaseObject::print();
  cout << "radius " << radius << endl;
}

void Sphere::name(){
  cout << "I am a sphere" << endl;
}

int Sphere::type() {
  return 1;
}

vector<float> Plan::getNormal(){
    return normal;
}

vector<float> Plan::getNormal(vector<float> P){
    return normal;
}

vector<float> Plan::getIntersection(Ray L, int &code) {
    code=1;
    vector<float> S=L.origin;
    vector<float> D=L.direction;
    if (D*normal<0) {
      float param=(1/(D*normal))*(center-S)*normal;
      return S+param*D;
    }else {
      code=0;
      return S;
    }
}

vector<float> Plan::getColor(const vector<float> &P) {
  
  vector<float> U = P-surface.texture.center;

  vector<float> X = surface.texture.direction;
  float x = fmod(U*X, surface.texture.width);
  if (x < 0) x += surface.texture.width;
  int n_x = (int)surface.texture.n*x/surface.texture.width;

  vector<float> Y = CrossProduct(normal, X);
  float y = fmod(U*Y, surface.texture.height);
  if (y < 0) y += surface.texture.height;
  int n_y = (int)surface.texture.m*y/surface.texture.height;

  int d = n_x*surface.texture.m+n_y;

  vector<float>* p_color = surface.texture.p_colors->data() + d;

  return *p_color;
}

void Plan::print(){
  SceneBaseObject::print();
  cout << "normal ";
  for (int i = 0; i < 3; i++)
    cout << normal[i] << " ";
  cout << endl;
}

void Plan::name(){
  cout << "I am a plan" << endl;
}

int Plan::type() {
  return 2;
}

vector<float> Triangle::getNormal(){
    // return CrossProduct((B-A),(C-A));
    return normal;
}

vector<float> Triangle::getNormal(vector<float> P){
    // return CrossProduct((B-A),(C-A));
    return normal;
}

vector<float> Triangle::getIntersection(Ray L, int &code){
    code=1;
    vector<float> S=L.origin;
    vector<float> D=L.direction;
    vector<float> normal;
    normal=this->getNormal();
    if (D*normal!=0) {
      float param=(1/(D*normal))*(center-S)*normal;
      vector<float> intertemp=S+param*D;
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
  cout << "I am a triangle" << endl;
}

int Triangle::type() {
  return 3;
}