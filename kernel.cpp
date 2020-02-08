#include "kernel.hpp"

int total;
int iter = 0;
int last_p = 0;

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

    total = rays.size();

    // Adding the reflexions of lightsources

    std::vector<float> zer={0,0,0};
    for (auto object : scene){
        if(object->type()==2 && object->surface.reflexion_coefficient!=zer){
            object->name();
            std::vector<LIGHT_SOURCE*> newsources;
            std::vector<float> newcenter;
            std::vector<int> newcolors;
            std::vector<float> C=object->center;
            std::vector<float> N=object->getNormal(C);
            int i =0;
            for (auto source : sources) {
                std::cout << i << std::endl;
                i++;
                std::vector<float> S=source->getPosition();
                newcenter=S-2*((S-C)*N)*N;
                newcolors=source->illumination*object->surface.reflexion_coefficient;
                LIGHT_SOURCE* newsource = new LIGHT_SOURCE(newcenter, newcolors);
                newsources.push_back(newsource);
            }
            for (auto newsource : newsources) {
                sources.push_back(newsource);
            }
        }
    }

    for (auto ray : rays) {
        colors.push_back(getColors(ray, camera.position, scene, sources, specular, ambiant, 0));
    }

    std::cout << "the pixels are computed" << std::endl;

    return colors;
}

std::vector<int> getColors( RAY& ray, std::vector<float>& origin,
                            std::vector<SCENE_BASE_OBJECT*> &scene,
                            std::vector<LIGHT_SOURCE*> &sources,
                            int specular,
                            const std::vector<int> &ambiant,
                            int stack) {

    int code;
    SCENE_BASE_OBJECT* p_object;
    std::vector<float> P, current_P, N, L, R, V;
    std::vector<int> I(3, 0);
    float min_d = 0;
    bool reach = false;
    float epsilon = 1e-04;
    for (auto object : scene) {
        current_P = object->getIntersection(ray, code);
        if (code) {
            float d = sqrt((current_P-origin)*(current_P-origin));

            if (d > epsilon) {
                if ((!reach || d < min_d)) {
                    min_d = d;
                    p_object = object;
                    P = current_P;
                }
                reach = true;
            }
        }
    }

    if (reach) {

        N = p_object->getNormal(P);
        V = ray.direction;

        bool isLit;
        std::vector<float> posSource;

        for (auto source : sources) {
            posSource=source->getPosition();
            isLit=p_object->isItLit(P,posSource, scene);
            
            if (isLit) {
                L = source->getIncidentRay(P);
                R = source->getReflectedRay(P, N);
                I += source->illumination*p_object->getIllumination(P, L, N, V, R, specular);
                
            }
            I += ambiant*p_object->surface.ambiant_coefficient;
        }
        std::vector<float> zer={0,0,0};
        if (stack < 2 && p_object->surface.reflexion_coefficient!=zer) {
            std::vector<float> direction = p_object->getReflectedRayDirection(V, P);
            RAY reflectedRay(P, direction);
            std::vector<int> reflectedI = getColors(reflectedRay, P, scene, sources, specular, ambiant, stack+1)*
                                            p_object->surface.reflexion_coefficient;
            I+=reflectedI;
        }
    }

    if (stack == 0) {
        iter++;
        int p = (int)(100*(float)iter / total);
        if (p % 10 == 0 and p != last_p) {
            std::cout << p << "%" << std::endl;
            last_p = p;
        }
    }

    capColors(I);
    return I;
}
