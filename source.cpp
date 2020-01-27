#include "source.hpp"

std::vector<float> LIGHT_SOURCE::getIncidentRay(std::vector<float> P) {
    return normalise(this->position - P);
}

std::vector<float> LIGHT_SOURCE::getReflectedRay(std::vector<float> P, std::vector<float> N) {
    return normalise(2*((P - position)*N)*N - (P - position));
}