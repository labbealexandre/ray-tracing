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

Texture loadTexture(tinyxml2::XMLHandle &hTexture) {
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

    Texture texture(p_colors, center, direction, W, H, n, m);
    return texture;
}

Surface loadSurface(tinyxml2::XMLHandle &hSurface) {
    std::vector<float> array;

    tinyxml2::XMLHandle hColors = hSurface.FirstChildElement();
    std::vector<float> colors = loadCoords(hColors);

    tinyxml2::XMLHandle hTexture = hColors.NextSiblingElement();
    Texture texture = loadTexture(hTexture);

    tinyxml2::XMLHandle hCoefs = hTexture.NextSiblingElement();
    for (int i = 0; i < 4; i++) {
        float coef = std::stof(hCoefs.ToElement()->GetText());
        array.push_back(coef);

        if (i < 3)
        hCoefs = hCoefs.NextSiblingElement();
    }

    Surface surface(colors, texture, array[0], array[1], array[2], array[3]);

    return surface;
}

void loadFile(  std::string file, int& specular, std::vector<float>& ambiant,
                Camera& camera, std::vector<LightSource*>& sources,
                std::vector<SceneBaseObject*>& scene, int& n, int& m) {

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

            camera = Camera(center, W, H, focal, n, m);

        } else if (title.compare("params") == 0) {
            tinyxml2::XMLHandle hSpecular = hObject.FirstChildElement();
            specular = std::stoi(hSpecular.ToElement()->GetText());

            tinyxml2::XMLHandle hColors = hSpecular.NextSiblingElement();
            ambiant = loadCoords(hColors);

        } else if (title.compare("source") == 0) {
            tinyxml2::XMLHandle hCenter = hObject.FirstChildElement();
            std::vector<float> center = loadCoords(hCenter);

            tinyxml2::XMLHandle hColors = hCenter.NextSiblingElement();
            std::vector<int> colors = loadColors(hColors);

            LightSource* source = new LightSource(center, colors);
            sources.push_back(source);

        } else {

            tinyxml2::XMLHandle h = hObject.FirstChildElement();
            Surface surface = loadSurface(h);

            h = h.NextSiblingElement();
            float n1 = std::stof(h.ToElement()->GetText());

            h = h.NextSiblingElement();
            float n2 = std::stof(h.ToElement()->GetText());

            if (title.compare("sphere") == 0) {
                h = h.NextSiblingElement();
                std::vector<float> center = loadCoords(h);

                h = h.NextSiblingElement();
                float radius = std::stof(h.ToElement()->GetText());

                Sphere* sphere = new Sphere(center, radius, surface, n1, n2);
                scene.push_back(sphere);

            } else if (title.compare("plan") == 0) {
                h = h.NextSiblingElement();
                std::vector<float> center = loadCoords(h);

                h = h.NextSiblingElement();
                std::vector<float> normal = loadCoords(h);

                Plan* plan = new Plan(center, normal, surface, n1, n2);
                scene.push_back(plan);
                
            } else if (title.compare("triangle") == 0) {
                h = h.NextSiblingElement();
                std::vector<float> N = loadCoords(h);

                h = h.NextSiblingElement();
                std::vector<float> A = loadCoords(h);

                h = h.NextSiblingElement();
                std::vector<float> B = loadCoords(h);

                h = h.NextSiblingElement();
                std::vector<float> C = loadCoords(h);

                Triangle* triangle = new Triangle(N, A, B, C, surface, n1, n2);
                scene.push_back(triangle);
            }
            else if (title.compare("polygon") == 0) {
                int n = std::stoi(elem->Attribute("corners"));

                std::vector<std::vector<float>> corners;

                h = h.NextSiblingElement();
                std::vector<float> N = loadCoords(h);

                h = h.NextSiblingElement();
                corners.push_back(loadCoords(h));
                for (int i = 1; i < n; i++) {
                    h = h.NextSiblingElement();
                    corners.push_back(loadCoords(h));
                }

                std::vector<Triangle*> triangles = polyToTriangles(N, corners, surface, n1, n2);
                scene.insert(scene.end(), triangles.begin(), triangles.end());
            }
        }
    }
}

// TODO : end the spliting into triangles
std::vector<Triangle*> polyToTriangles(std::vector<float> N, std::vector<std::vector<float>>& corners,
                                            Surface& surface, float n1, float n2) {

    std::vector<Triangle*> triangles;
    std::vector<float> n = normalise(corners[corners.size()/2] - corners[0]);

    std::vector<std::tuple<float, std::vector<float>*, int>> heights;

    float maxHeight = 0;
    unsigned int indexMaxHeight = 0;

    /* Computation of the heights */
    for (unsigned int i = 0; i < corners.size(); i++) {
        float height = (corners[i] - corners[0])*n; 
        if (height > maxHeight) {
            maxHeight = height;
            indexMaxHeight = i;
        }
        heights.push_back(std::make_tuple(height, corners.data()+i, 0));
    }

    /* Spliting in tow chains */
    for (unsigned int i = 0; i < corners.size(); i++) {
        if (i <= indexMaxHeight) std::get<2>(heights[i]) = 1;
        else std::get<2>(heights[i]) = 2;
    }

    /* Sorting by height */
    std::sort(heights.begin(), heights.end());
    std::reverse(heights.begin(), heights.end());

    monotoneToTriangles(N, heights, triangles, surface, n1, n2); // TODO : case of non-monotone polygons

    return triangles;
}

void monotoneToTriangles(std::vector<float> N, std::vector<std::tuple<float, std::vector<float>*, int>>& heights,
                        std::vector<Triangle*>& triangles, Surface& surface, float n1, float n2) {
    
    unsigned int s = heights.size();
    Triangle* triangle = new Triangle(N, *std::get<1>(heights[s-1]), *std::get<1>(heights[s-2]),
                            *std::get<1>(heights[s-3]), surface, n1, n2);

    triangles.push_back(triangle);
    
    if (std::get<2>(heights[s-2]) == std::get<2>(heights[s-3])) {
        heights.erase(heights.end()-2);
    } else {
        heights.pop_back();
    }

    if(heights.size() >= 3)  monotoneToTriangles(N, heights, triangles, surface, n1, n2);
}