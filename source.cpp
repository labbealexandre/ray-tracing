#include "source.hpp"

std::vector<float> LightSource::getIncidentRay(std::vector<float> P) {
  return normalise(this->position - P);
}

std::vector<float> LightSource::getReflectedRay(std::vector<float> P, std::vector<float> N) {
  return normalise(2*((P - this->position)*N)*N - (P - this->position));
}

std::vector<float> LightSource::getPosition() {
  return this->position;
}


