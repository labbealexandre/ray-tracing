#include <vector>
#include "source.hpp"
#include "utils.hpp"

std::vector<float> LIGHT_SOURCE::getIncidentRay(std::vector<float> P) {
    return P - position;
}

std::vector<float> getReflectedRay(std::vector<float> P, std::vector<float> N) {
    return 2*(P*N)*N - P;
}