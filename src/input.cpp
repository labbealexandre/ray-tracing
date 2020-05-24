#include "../src/input.hpp"

using namespace std;

vector<float> center;
float radius;
Surface surface;
float n1; float n2;
Sphere* sphere;

void loadInputs(int& specular, vector<float>& ambiant, Camera& camera, vector<LightSource*>& sources, vector<SceneBaseObject*>& scene, int& n, int& m) {
  center.clear();
  center.push_back(500);
  center.push_back(0);
  center.push_back(0);
  radius = 200;
  surface = Surface();
  n1 = 0; n2 = 0;
  delete sphere;
  sphere = new Sphere(center, radius, surface, n1, n2);
  scene.push_back(sphere);

}