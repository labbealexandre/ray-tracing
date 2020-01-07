#include "kernel.hpp"

void run(
    CAMERA &camera,
    std::vector<SPHERE_OBJECT> &spheres,
    std::vector<LIGHT_SOURCE> &sources
) {
    std::vector<RAY> rays = camera.traceRays();
    for (auto it = rays.begin(); it != rays.end(); ++it) {
        RAY ray = *it;
        for (auto sit = spheres.begin(); sit != spheres.end(); ++it) {
            // TODO getIntersect
        }
    }
}