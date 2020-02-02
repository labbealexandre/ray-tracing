#include "kernel.hpp"

std::vector<std::vector<int>> run(
    CAMERA &camera,
    std::vector<SCENE_BASE_OBJECT*> &scene,
    std::vector<LIGHT_SOURCE*> &sources,
    int specular,
    std::vector<int> &ambiant
) {
    std::vector<std::vector<int>> colors;

    std::vector<RAY> rays = camera.traceRays();
    std::cout << "Rays traced " << rays.size() << std::endl;
    std::vector<float> P, N, L, R, V;
    std::vector<int> I(3, 0);

    for (auto ray : rays) {
        colors.push_back(getColors(ray, camera.position, scene, sources, specular, ambiant));
    }

    std::cout << "the pixels are computed" << std::endl;

    return colors;
}

std::vector<int> getColors( RAY& ray, std::vector<float>& origin,
                            std::vector<SCENE_BASE_OBJECT*> &scene,
                            std::vector<LIGHT_SOURCE*> &sources,
                            int specular,
                            const std::vector<int> &ambiant) {
    int code;
    SCENE_BASE_OBJECT* p_object;
    std::vector<float> P, current_P, N, L, R, V;
    std::vector<int> I = ambiant;
    float min_d = 0;
    bool reach = false;

    for (auto object : scene) {
        current_P = object->getIntersection(ray, code);
        if (code) {
            float d = sqrt((current_P-origin)*(current_P-origin));
            if (!reach || d < min_d) {
                min_d = d;
                p_object = object;
                P = current_P;
            }
            reach = true;
        }
    }

    if (reach) {
        N = p_object->getNormal(P);
        V = ray.direction;

        bool isLit;
        std::vector<float> posSource;

        for (auto source : sources) {
            posSource=source->getPosition();
            isLit=p_object->isItLit(P,posSource);
            
            if (isLit) {
                L = source->getIncidentRay(P);
                R = source->getReflectedRay(P, N);
                I = source->illumination*p_object->getIllumination(L, N, V, R, specular);
            }
        }
    }

    return I;
}
