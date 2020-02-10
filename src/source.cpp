#include "source.hpp"

using namespace std;

vector<float> LightSource::getIncidentRay(vector<float> P) {
  return normalise(this->position - P);
}

vector<float> LightSource::getReflectedRay(vector<float> P, vector<float> N) {
  return normalise(2*((P - this->position)*N)*N - (P - this->position));
}

vector<float> LightSource::getPosition() {
  return this->position;
}


