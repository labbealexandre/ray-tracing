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

std::vector<int> loadColors(tinyxml2::XMLHandle &hColors) {
    std::vector<int> colors;
    for (tinyxml2::XMLElement* color = hColors.FirstChildElement().ToElement();
        color != NULL; color = color->NextSiblingElement()) {

        std::string text(color->GetText());
        colors.push_back(std::stoi(text));
    }
    return colors;
}

OBJECT_BASE_SURFACE loadSurface(tinyxml2::XMLHandle &hSurface) {
    std::vector<std::vector<float>> array;

    tinyxml2::XMLHandle hCoefs = hSurface.FirstChildElement();
    for (int i = 0; i < 4; i++) {
        std::vector<float> coefs = loadCoords(hCoefs);
        array.push_back(coefs);

        if (i < 3)
        hCoefs = hCoefs.NextSiblingElement();
    }

    OBJECT_BASE_SURFACE surface(array[0], array[1], array[2], array[3]);
    return surface;
}

void loadFile(  std::string file, std::vector<LIGHT_SOURCE*>& sources,
                std::vector<SCENE_BASE_OBJECT*>& scene, int& specular,
                std::vector<int>& ambiant) {
    tinyxml2::XMLDocument doc;
	doc.LoadFile(file.data());

    tinyxml2::XMLHandle hDoc(&doc);
    tinyxml2::XMLElement* pElem;
    tinyxml2::XMLHandle hRoot(0), hObject(0);

    pElem=hDoc.FirstChildElement().ToElement();

    hRoot=tinyxml2::XMLHandle(pElem);

    for (tinyxml2::XMLElement* elem = hRoot.FirstChildElement().ToElement();
        elem != NULL; elem = elem->NextSiblingElement()) {
        
        std::string title(elem->Value());
        hObject=tinyxml2::XMLHandle(elem);

        if (title.compare("params") == 0) {
            tinyxml2::XMLHandle hSpecular = hObject.FirstChildElement();
            specular = std::stoi(hSpecular.ToElement()->GetText());

            tinyxml2::XMLHandle hColors = hSpecular.NextSiblingElement();
            ambiant = loadColors(hColors);

        } else if (title.compare("source") == 0) {
            tinyxml2::XMLHandle hCenter = hObject.FirstChildElement();
            std::vector<float> center = loadCoords(hCenter);

            tinyxml2::XMLHandle hColors = hCenter.NextSiblingElement();
            std::vector<int> colors = loadColors(hColors);

            LIGHT_SOURCE* source = new LIGHT_SOURCE(center, colors);
            sources.push_back(source);

        } else if (title.compare("sphere") == 0) {
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
            // std::cout << plan->getNormal() << std::cout;
            scene.push_back(plan);
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        std::cout << "You need 2 arguments : xml source file and tga target image" << std::endl;
        return -1;
    }

    std::string file(argv[1]);
    std::string target(argv[2]);

    std::vector<LIGHT_SOURCE*> sources;
    std::vector<SCENE_BASE_OBJECT*> scene;
    int specular;
    std::vector<int> ambiant;

    loadFile(file, sources, scene, specular, ambiant);

    const float W = 10;
    const float H = 10;
    const float focal = 5;
    const int n = 500;
    const int m = 500;
    std::vector<float> c_center = {0, 0, 0};
    CAMERA camera(c_center, W, H, focal, n, m);

    std::vector<std::vector<int>> colors = run(camera, scene, sources, specular, ambiant);

    savePicture(target.data(), n, m, colors);

    return 0;
}