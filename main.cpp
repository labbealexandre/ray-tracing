#include <vector>
#include <string>
#include "kernel.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "source.hpp"
#include "surface.hpp"
#include "display.hpp"
#include "tinyxml2/tinyxml2.h"

std::vector<float> loadCoords(tinyxml2::XMLHandle &hCoords) {
    std::vector<float> coords;
    for (tinyxml2::XMLElement* coor = hCoords.FirstChildElement().ToElement();
        coor != NULL; coor = coor->NextSiblingElement()) {

        std::string text(coor->GetText());
        coords.push_back(std::stof(text));
    }
    return coords;
}

OBJECT_BASE_SURFACE loadSurface(tinyxml2::XMLHandle &hSurface) {
    std::vector<std::vector<float>> array;

    tinyxml2::XMLHandle hColors = hSurface.FirstChildElement();
    for (int i = 0; i < 4; i++) {
        std::vector<float> colors = loadCoords(hColors);
        array.push_back(colors);

        if (i < 3)
        hColors = hColors.NextSiblingElement();
    }

    OBJECT_BASE_SURFACE surface(array[0], array[1], array[2], array[3]);
    return surface;
}

std::vector<SCENE_BASE_OBJECT*> loadFile(std::string file) {
    tinyxml2::XMLDocument doc;
	doc.LoadFile(file.data());

    tinyxml2::XMLHandle hDoc(&doc);
    tinyxml2::XMLElement* pElem;
    tinyxml2::XMLHandle hRoot(0), hObject(0);

    std::vector<SCENE_BASE_OBJECT*> scene;

    pElem=hDoc.FirstChildElement().ToElement();

    hRoot=tinyxml2::XMLHandle(pElem);

    for (tinyxml2::XMLElement* elem = hRoot.FirstChildElement().ToElement();
        elem != NULL; elem = elem->NextSiblingElement()) {
        
        std::string title(elem->Value());
        hObject=tinyxml2::XMLHandle(elem);

        if (title.compare("sphere") == 0) {
            tinyxml2::XMLHandle hCenter = hObject.FirstChildElement();
            std::vector<float> center = loadCoords(hCenter);

            tinyxml2::XMLHandle hRadius = hCenter.NextSiblingElement();
            float radius = std::stof(hRadius.ToElement()->GetText());

            tinyxml2::XMLHandle hSurface = hRadius.NextSiblingElement();
            OBJECT_BASE_SURFACE surface = loadSurface(hSurface);

            SPHERE_OBJECT* sphere = new SPHERE_OBJECT(center, radius, surface);
            scene.push_back(sphere);

        } else if (title.compare("plan") == 0) {
            tinyxml2::XMLHandle hCenter = hObject.FirstChildElement();
            std::vector<float> center = loadCoords(hCenter);

            tinyxml2::XMLHandle hNormal = hCenter.NextSiblingElement();
            std::vector<float> normal = loadCoords(hNormal);

            tinyxml2::XMLHandle hSurface = hNormal.NextSiblingElement();
            OBJECT_BASE_SURFACE surface = loadSurface(hSurface);

            PLAN_OBJECT* plan = new PLAN_OBJECT(center, normal, surface);
            scene.push_back(plan);
        }
    }
    return scene;
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        std::cout << "You need 2 arguments : xml source file and tga target image" << std::endl;
        return -1;
    }

    std::string file(argv[1]);
    std::string target(argv[2]);

    std::vector<LIGHT_SOURCE> sources;

    auto scene = loadFile(file);

    std::vector<float> l_center = {0, 0, 100};
    std::vector<int> color = {255, 255, 255};
    LIGHT_SOURCE source(l_center, color);
    sources.push_back(source);

    const float W = 10;
    const float H = 10;
    const float focal = 5;
    const int n = 500;
    const int m = 500; 
    std::vector<float> c_center = {0, 0, 0};
    CAMERA camera(c_center, W, H, focal, n, m);

    std::vector<std::vector<int>> colors = run(camera, scene, sources);

    savePicture(target.data(), n, m, colors);

    return 0;
}