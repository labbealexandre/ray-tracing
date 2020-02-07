#include "loadxml.hpp"

std::vector<std::vector<std::vector<float>>*> colors_pointers;
std::vector<int> resolutions;
std::vector<std::string> paths;

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

TEXTURE loadTexture(tinyxml2::XMLHandle &hTexture) {
    tinyxml2::XMLHandle hPath = hTexture.FirstChildElement();
    std::string path = hPath.ToElement()->GetText();

    std::vector<std::vector<float>>* p_colors;
    int n, m;

    std::vector<std::string>::iterator it = std::find(paths.begin(), paths.end(), path);
    if (it != paths.cend()) {
        n = resolutions[2*std::distance(paths.begin(), it)];
        m = resolutions[2*std::distance(paths.begin(), it)+1];
        p_colors = colors_pointers[std::distance(paths.begin(), it)];
    } else {
        p_colors = loadPicture(path, n, m);
        paths.push_back(path);
        std::pair<int, int> pair;
        resolutions.push_back(n);
        resolutions.push_back(m);

        colors_pointers.push_back(p_colors);
    }

    tinyxml2::XMLHandle hCenter = hPath.NextSiblingElement();
    std::vector<float> center = loadCoords(hCenter);

    tinyxml2::XMLHandle hDirection = hCenter.NextSiblingElement();
    std::vector<float> direction = loadCoords(hDirection);

    tinyxml2::XMLHandle hWidth = hDirection.NextSiblingElement();
    float W = std::stof(hWidth.ToElement()->GetText());

    tinyxml2::XMLHandle hHeight = hWidth.NextSiblingElement();
    float H = std::stof(hHeight.ToElement()->GetText());

    TEXTURE texture(p_colors, center, direction, W, H, n, m);
    return texture;
}

OBJECT_BASE_SURFACE loadSurface(tinyxml2::XMLHandle &hSurface) {
    std::vector<std::vector<float>> array;

    tinyxml2::XMLHandle hTexture = hSurface.FirstChildElement();
    TEXTURE texture = loadTexture(hTexture);

    tinyxml2::XMLHandle hCoefs = hTexture.NextSiblingElement();
    for (int i = 0; i < 5; i++) {
        std::vector<float> coefs = loadCoords(hCoefs);
        array.push_back(coefs);

        if (i < 4)
        hCoefs = hCoefs.NextSiblingElement();
    }

    OBJECT_BASE_SURFACE surface(texture, array[0], array[1], array[2], array[3], array[4]);

    return surface;
}

void loadFile(  std::string file, int& specular, std::vector<int>& ambiant,
                CAMERA& camera, std::vector<LIGHT_SOURCE*>& sources,
                std::vector<SCENE_BASE_OBJECT*>& scene, int& n, int& m) {

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

        if (title.compare("camera") == 0) {
            tinyxml2::XMLHandle hCenter = hObject.FirstChildElement();
            std::vector<float> center = loadCoords(hCenter);

            tinyxml2::XMLHandle hWidth = hCenter.NextSiblingElement();
            const float W = std::stof(hWidth.ToElement()->GetText());

            tinyxml2::XMLHandle hHeight = hWidth.NextSiblingElement();
            const float H = std::stof(hHeight.ToElement()->GetText());

            tinyxml2::XMLHandle hFocal = hHeight.NextSiblingElement();
            const float focal = std::stof(hFocal.ToElement()->GetText());

            tinyxml2::XMLHandle hNWidth = hFocal.NextSiblingElement();
            n = std::stoi(hNWidth.ToElement()->GetText());

            tinyxml2::XMLHandle hNHeight = hNWidth.NextSiblingElement();
            m = std::stoi(hNHeight.ToElement()->GetText());

            camera = CAMERA(center, W, H, focal, n, m);

        } else if (title.compare("params") == 0) {
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
            scene.push_back(plan);
            
        } else if (title.compare("triangle") == 0) {
            tinyxml2::XMLHandle hA = hObject.FirstChildElement();
            std::vector<float> A = loadCoords(hA);

            tinyxml2::XMLHandle hB = hA.NextSiblingElement();
            std::vector<float> B = loadCoords(hB);

            tinyxml2::XMLHandle hC = hB.NextSiblingElement();
            std::vector<float> C = loadCoords(hC);

            tinyxml2::XMLHandle hSurface = hC.NextSiblingElement();
            OBJECT_BASE_SURFACE surface = loadSurface(hSurface);

            TRIANGLE_OBJECT* triangle = new TRIANGLE_OBJECT(A, B, C, surface);
            scene.push_back(triangle);
        } else if (title.compare("polygon") == 0) {
            tinyxml2::XMLHandle hA = hObject.FirstChildElement();
            std::vector<float> A = loadCoords(hA);

            tinyxml2::XMLHandle hB = hA.NextSiblingElement();
            std::vector<float> B = loadCoords(hB);

            tinyxml2::XMLHandle hC = hB.NextSiblingElement();
            std::vector<float> C = loadCoords(hC);

            tinyxml2::XMLHandle hSurface = hC.NextSiblingElement();
            OBJECT_BASE_SURFACE surface = loadSurface(hSurface);

            TRIANGLE_OBJECT* triangle = new TRIANGLE_OBJECT(A, B, C, surface);
            scene.push_back(triangle);
        }
    }
}