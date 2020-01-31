#include "kernel.hpp"

std::vector<std::vector<int>> run(
    CAMERA &camera,
    std::vector<SCENE_BASE_OBJECT*> &scene,
    std::vector<LIGHT_SOURCE> &sources
) {
    std::vector<std::vector<int>> colors;

    std::vector<RAY> rays = camera.traceRays();
    std::cout << "Rays traced " << rays.size() << std::endl;
    int code;
    std::vector<float> P, N, L, R, V;
    std::vector<int> I(3, 0);

    for (auto ray : rays) {
        std::vector<int> color(3, 0);

        for (auto object : scene) {
            P = object->getIntersection(ray, code);
            V = ray.direction;
            
            if (code) {
                N = object->getNormal(P);

                bool isLit;
                std::vector<float> posSource;

                for (auto source : sources) {
                    posSource=source.getPosition();
                    isLit=object->isItLit(P,posSource);
                    
                    if (isLit) {
                        L = source.getIncidentRay(P);
                        R = source.getReflectedRay(P, N);
                        I = source.illumination*object->getIllumination(L, N, V, R);

                        std::vector<float> test = object->getIllumination(L, N, V, R);
                        // TODO : do an average
                        ray.colors = I;
                  }
                }
                color = ray.colors;
            }
        }
        colors.push_back(color);
    }

    std::cout << "the pixels are computed" << std::endl;

    return colors;
}
