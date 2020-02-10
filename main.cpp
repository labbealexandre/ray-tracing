#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include "kernel.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "source.hpp"
#include "display.hpp"
#include "loadxml.hpp"

int main(int argc, char const *argv[])
{
    unsigned begin, A,B,C, end;
    begin=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
         

    if (argc != 3) {
        std::cout << "You need 2 arguments : xml source file and tga target image" << std::endl;
        return -1;
    }

    std::string file(argv[1]);
    std::string target(argv[2]);

    Camera camera;
    std::vector<LightSource*> sources;
    std::vector<SceneBaseObject*> scene;
    int specular;
    std::vector<float> ambiant;
    int n;
    int m;

    A=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    loadFile(file, specular, ambiant, camera, sources, scene, n, m);
    
    B=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "temps chargement de la scène: "<< ((float)(B - A))/1000 << "s" << std::endl;
    
    std::vector<std::vector<int>> colors = run(camera, scene, sources, specular, ambiant);
    
    C=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "temps calcul de l'image: "<< ((float)(C - B))/1000 << "s" << std::endl;

    savePicture(target.data(), n, m, colors);

    deleteTextures();
    for (auto source : sources) delete source;
    for (auto object : scene) delete object;
    
    end=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "temps sauvegarde: "<< ((float)(end - C))/1000 << "s" << std::endl;
    std::cout << "temps total: "<<((float)(end -begin))/1000 << "s" << std::endl;
    
    return 0;
}