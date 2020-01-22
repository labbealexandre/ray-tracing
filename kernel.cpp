#include "kernel.hpp"

std::vector<std::vector<int>> run(
    CAMERA &camera,
    std::vector<SPHERE_OBJECT> &spheres,
    std::vector<PLAN_OBJECT> &plans,
    std::vector<LIGHT_SOURCE> &sources
) {
    std::vector<std::vector<int>> colors;

    std::vector<RAY> rays = camera.traceRays();
    std::cout << "Rays traced " << rays.size() << std::endl;
    int code;
    std::vector<float> P, N, L, R, V;
    std::vector<int> I(3, 0);
    
    for (auto it = rays.begin(); it != rays.end(); ++it) {
        RAY &ray = *it;

        for (auto sit = spheres.begin(); sit != spheres.end(); ++sit) {

            SPHERE_OBJECT &sphere = *sit;
            P = sphere.getIntersection(ray, code);
            V = ray.direction;
            std::vector<int> color(3, 0);

            if (code) {
                
                N = sphere.getNormal(P);
                for (auto lit = sources.begin(); lit!= sources.end(); ++lit) {
                    LIGHT_SOURCE &source = *lit;
                    
                    L = source.getIncidentRay(P);
                    R = source.getReflectedRay(P, N);
                    I = source.illumination*sphere.getIllumination(L, N, V, R);
                    
                    std::vector<float> test = sphere.getIllumination(L, N, V, R);

                    // TODO : do an average
                    ray.colors = I;
                }
                color = ray.colors;
            }
            colors.push_back(color);
        }
        for (auto pit = plans.begin(); pit != plans.end(); ++pit) {

            PLAN_OBJECT &plan = *pit;
            P = plan.getIntersection(ray, code);
            V = ray.direction;
            std::vector<int> color(3, 0);

            if (code) {
                
                N = plan.getNormal();
                for (auto lit = sources.begin(); lit!= sources.end(); ++lit) {
                    LIGHT_SOURCE &source = *lit;
                    
                    L = source.getIncidentRay(P);
                    R = source.getReflectedRay(P, N);
                    I = source.illumination*plan.getIllumination(L, N, V, R);
                    
                    std::vector<float> test = plan.getIllumination(L, N, V, R);

                    // TODO : do an average
                    ray.colors = I;
                }
                color = ray.colors;
            }
            colors.push_back(color);
        }
    }

    std::cout << "the pixels are computed" << std::endl;

    return colors;
}

std::vector<int> operator * (const std::vector<int>& left, const std::vector<float>& right) {
    std::vector<int> res;

    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < right.size(); i++) {
            float result = left[i]*right[i];
            res.push_back((int)result);
        }
    } else {
        // TODO : handle error
    }
    return res;
}