#include "kernel.hpp"


std::vector<std::vector<int>> run(
    Camera &camera,
    std::vector<SceneBaseObject*> &scene,
    std::vector<LightSource*> &sources,
    int specular,
    std::vector<float> &ambiant
) {
    unsigned D,E,F,G;
    D=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    /** Tracing Rays **/
    std::vector<RAY> rays = camera.traceRays(); 

    E=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "traced " << rays.size() << " rays in : "<< ((float)(E - D))/1000 << " s" << std::endl;

    std::vector<float> P, N, L, R, V;
    std::vector<int> I(3, 0);

    /** Adding the reflexions of lightsources **/
    for (auto object : scene){
        if(object->type()==2 && object->surface.reflexion_coefficient!=0){
            object->name();
            std::vector<LightSource*> newsources;
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
                newcolors=object->surface.reflexion_coefficient*source->illumination;
                LightSource* newsource = new LightSource(newcenter, newcolors);
                newsources.push_back(newsource);
            }
            for (auto newsource : newsources) {
                sources.push_back(newsource);
            }
        }
    }
    
    F=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "reflected light sources generated in : "<< ((float)(F - E))/1000 << " s" << std::endl;

    /** Initialization to 0 of the computed colors **/
    std::vector<int> black{0, 0, 0};
    std::vector<std::vector<int>> colors(rays.size(), black);

    /** Paralization of the rays computing **/
    int nb_taches;
    # pragma omp parallel private(nb_taches) 
    {
        nb_taches=omp_get_num_threads();
        #pragma omp for schedule( static , camera.pixels_per_row/nb_taches) nowait
        for (int i = 0; i < camera.pixels_per_row; i++) {
            for (int j = 0; j < camera.pixels_per_column; j++) {
                RAY ray=rays[i*camera.pixels_per_column+j];
                colors[i*camera.pixels_per_column+j]=getColors(ray, camera.position, scene, sources, specular, ambiant, 0);
            }   
        }  
    }
    G=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "the pixels have been computed in " << ((float)(G - F))/1000 << "s" << std::endl;

    return colors;
}

std::vector<int> getColors( RAY& ray, std::vector<float>& origin,
                            std::vector<SceneBaseObject*> &scene,
                            std::vector<LightSource*> &sources,
                            int specular,
                            const std::vector<float> &ambiant,
                            int stack) {

    int code;
    SceneBaseObject* p_object;
    std::vector<float> P, current_P, N, L, R, V;
    std::vector<int> I(3, 0);
    float min_d = 0;
    bool reach = false;
    float epsilon = 1e-02;

    /** finding the pixel nearest to the camera **/
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

            I += 255*(p_object->surface.diffuse_coefficient*prod(ambiant, p_object->getColor(P)));
            
            if (isLit) {
                L = source->getIncidentRay(P);
                R = source->getReflectedRay(P, N);
                I += source->illumination*p_object->getIllumination(P, L, N, V, R, specular);
            }
        }

        /** Getting reflected rays **/
        if (stack < 3 && p_object->surface.reflexion_coefficient != 0) {
            std::vector<float> direction = p_object->getReflectedRayDirection(V, P);
            RAY reflectedRay(P, direction);

            /** Recursive call for the reflected ray **/
            std::vector<int> reflectedI = p_object->surface.reflexion_coefficient*
                                            getColors(reflectedRay, P, scene, sources, specular, ambiant, stack+1);
            I+=reflectedI;
        }

        /** getting refracted rays **/
        if (stack < 3 && p_object->surface.transmission_coefficient != 0 ) {
            int code;
            std::vector<float> direction = p_object->getRefractedRayDirection(V, P, code);
            if (code == 1) {
                RAY refractedRay(P, direction);

                /** Recursive call for the refracted ray **/
                std::vector<int> refractedI = p_object->surface.transmission_coefficient*
                                                getColors(refractedRay, P, scene, sources, specular, ambiant, stack+1); 
                I+=refractedI;
            }
        }
    }
        capColors(I);
    return I;
}
