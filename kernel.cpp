#include "kernel.hpp"

void run(
    CAMERA &camera,
    std::vector<SPHERE_OBJECT> &spheres,
    std::vector<LIGHT_SOURCE> &sources

) {
    std::vector<RAY> rays = camera.traceRays();
    int code;
    std::vector<float> P, N, L, R, V;
    std::vector<int> I;
    for (auto it = rays.begin(); it != rays.end(); ++it) {
        RAY &ray = *it;
        for (auto sit = spheres.begin(); sit != spheres.end(); ++it) {
            SPHERE_OBJECT &sphere = *sit;
            P = sphere.getIntersection(ray, code);
            V = ray.direction;
            if (code) {
                N = sphere.getNormal(P);
                for (auto lit = sources.begin(); lit!= sources.end(); ++lit) {
                    LIGHT_SOURCE &source = *lit;
                    L = source.getIncidentRay(P);
                    R = source.getReflectedRay(P, N);
                    I = source.illumination*sphere.getIllumination(L, N, V, R);

                    // TODO : do an average
                    ray.colors = I;
                }
            }

        }
    }
    // TODO : call the displayer
}

std::vector<int> operator * (const std::vector<int>& left, const std::vector<float>& right) {
    std::vector<int> res;
    if (left.size() == right.size()) {
        for (unsigned int i; i < right.size(); i++) {
            res.push_back((int)left[i]*right[i]);
        }
    } else {
        // TODO : handle error
    }
    return res;
}