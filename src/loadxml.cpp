#include "loadxml.hpp"

using namespace tinyxml2;
using namespace std;

vector<vector<vector<float>>*> colors_pointers;
vector<int> resolutions;
vector<string> paths;

vector<float> loadCoords(XMLHandle &hCoords) {
    vector<float> coords;
    for (XMLElement* coor = hCoords.FirstChildElement().ToElement();
        coor != NULL; coor = coor->NextSiblingElement()) {

        string text(coor->GetText());
        coords.push_back(stof(text));
    }
    return coords;
}

vector<int> loadColors(XMLHandle &hColors) {
    vector<int> colors;
    for (XMLElement* color = hColors.FirstChildElement().ToElement();
        color != NULL; color = color->NextSiblingElement()) {

        string text(color->GetText());
        colors.push_back(stoi(text));
    }
    return colors;
}

Texture loadTexture(XMLHandle &hTexture) {
    XMLHandle hPath = hTexture.FirstChildElement();
    string path = hPath.ToElement()->GetText();

    vector<vector<float>>* p_colors;
    int n, m;

    vector<string>::iterator it = find(paths.begin(), paths.end(), path);
    if (it != paths.cend()) {
        n = resolutions[2*distance(paths.begin(), it)];
        m = resolutions[2*distance(paths.begin(), it)+1];
        p_colors = colors_pointers[distance(paths.begin(), it)];
    } else {
        p_colors = loadPicture(path, n, m);
        paths.push_back(path);
        pair<int, int> pair;
        resolutions.push_back(n);
        resolutions.push_back(m);

        colors_pointers.push_back(p_colors);
    }

    XMLHandle hCenter = hPath.NextSiblingElement();
    vector<float> center = loadCoords(hCenter);

    XMLHandle hDirection = hCenter.NextSiblingElement();
    vector<float> direction = loadCoords(hDirection);

    XMLHandle hWidth = hDirection.NextSiblingElement();
    float W = stof(hWidth.ToElement()->GetText());

    XMLHandle hHeight = hWidth.NextSiblingElement();
    float H = stof(hHeight.ToElement()->GetText());

    Texture texture(p_colors, center, direction, W, H, n, m);
    return texture;
}

Surface loadSurface(XMLHandle &hSurface) {
    vector<float> array;

    XMLHandle hColors = hSurface.FirstChildElement();
    vector<float> colors = loadCoords(hColors);

    XMLHandle hTexture = hColors.NextSiblingElement();
    Texture texture = loadTexture(hTexture);

    XMLHandle hCoefs = hTexture.NextSiblingElement();
    for (int i = 0; i < 4; i++) {
        float coef = stof(hCoefs.ToElement()->GetText());
        array.push_back(coef);

        if (i < 3)
        hCoefs = hCoefs.NextSiblingElement();
    }

    Surface surface(colors, texture, array[0], array[1], array[2], array[3]);

    return surface;
}

void loadFile(  string file, int& specular, vector<float>& ambiant,
                Camera& camera, vector<LightSource*>& sources,
                vector<SceneBaseObject*>& scene, int& n, int& m) {

    XMLDocument doc;
	doc.LoadFile(file.data());

    XMLHandle hDoc(&doc);
    XMLElement* pElem;
    XMLHandle hRoot(0), hObject(0);

    pElem=hDoc.FirstChildElement().ToElement();

    hRoot=XMLHandle(pElem);

    for (XMLElement* elem = hRoot.FirstChildElement().ToElement();
        elem != NULL; elem = elem->NextSiblingElement()) {
        
        string title(elem->Value());
        hObject=XMLHandle(elem);

        if (title.compare("camera") == 0) {
            XMLHandle hCenter = hObject.FirstChildElement();
            vector<float> center = loadCoords(hCenter);

            XMLHandle hWidth = hCenter.NextSiblingElement();
            const float W = stof(hWidth.ToElement()->GetText());

            XMLHandle hHeight = hWidth.NextSiblingElement();
            const float H = stof(hHeight.ToElement()->GetText());

            XMLHandle hFocal = hHeight.NextSiblingElement();
            const float focal = stof(hFocal.ToElement()->GetText());

            XMLHandle hNWidth = hFocal.NextSiblingElement();
            n = stoi(hNWidth.ToElement()->GetText());

            XMLHandle hNHeight = hNWidth.NextSiblingElement();
            m = stoi(hNHeight.ToElement()->GetText());

            camera = Camera(center, W, H, focal, n, m);

        } else if (title.compare("params") == 0) {
            XMLHandle hSpecular = hObject.FirstChildElement();
            specular = stoi(hSpecular.ToElement()->GetText());

            XMLHandle hColors = hSpecular.NextSiblingElement();
            ambiant = loadCoords(hColors);

        } else if (title.compare("source") == 0) {
            XMLHandle hCenter = hObject.FirstChildElement();
            vector<float> center = loadCoords(hCenter);

            XMLHandle hColors = hCenter.NextSiblingElement();
            vector<int> colors = loadColors(hColors);

            LightSource* source = new LightSource(center, colors);
            sources.push_back(source);

        } else {

            XMLHandle h = hObject.FirstChildElement();
            Surface surface = loadSurface(h);

            h = h.NextSiblingElement();
            float n1 = stof(h.ToElement()->GetText());

            h = h.NextSiblingElement();
            float n2 = stof(h.ToElement()->GetText());

            if (title.compare("sphere") == 0) {
                h = h.NextSiblingElement();
                vector<float> center = loadCoords(h);

                h = h.NextSiblingElement();
                float radius = stof(h.ToElement()->GetText());

                Sphere* sphere = new Sphere(center, radius, surface, n1, n2);
                scene.push_back(sphere);

            } else if (title.compare("plan") == 0) {
                h = h.NextSiblingElement();
                vector<float> center = loadCoords(h);

                h = h.NextSiblingElement();
                vector<float> normal = loadCoords(h);

                Plan* plan = new Plan(center, normal, surface, n1, n2);
                scene.push_back(plan);
                
            } else if (title.compare("triangle") == 0) {
                h = h.NextSiblingElement();
                vector<float> N = loadCoords(h);

                h = h.NextSiblingElement();
                vector<float> A = loadCoords(h);

                h = h.NextSiblingElement();
                vector<float> B = loadCoords(h);

                h = h.NextSiblingElement();
                vector<float> C = loadCoords(h);

                Triangle* triangle = new Triangle(N, A, B, C, surface, n1, n2);
                scene.push_back(triangle);
            }
            else if (title.compare("polygon") == 0) {
                int n = stoi(elem->Attribute("corners"));

                vector<vector<float>> corners;

                h = h.NextSiblingElement();
                vector<float> N = loadCoords(h);

                h = h.NextSiblingElement();
                corners.push_back(loadCoords(h));
                for (int i = 1; i < n; i++) {
                    h = h.NextSiblingElement();
                    corners.push_back(loadCoords(h));
                }

                vector<Triangle*> triangles = polyToTriangles(N, corners, surface, n1, n2);
                scene.insert(scene.end(), triangles.begin(), triangles.end());
            }
        }
    }
}

// TODO : end the spliting into triangles
vector<Triangle*> polyToTriangles(vector<float> N, vector<vector<float>>& corners,
                                            Surface& surface, float n1, float n2) {

    vector<Triangle*> triangles;
    vector<float> n = normalise(corners[corners.size()/2] - corners[0]);

    vector<tuple<float, vector<float>*, int>> heights;

    float maxHeight = 0;
    unsigned int indexMaxHeight = 0;

    /* Computation of the heights */
    for (unsigned int i = 0; i < corners.size(); i++) {
        float height = (corners[i] - corners[0])*n; 
        if (height > maxHeight) {
            maxHeight = height;
            indexMaxHeight = i;
        }
        heights.push_back(make_tuple(height, corners.data()+i, 0));
    }

    /* Spliting in tow chains */
    for (unsigned int i = 0; i < corners.size(); i++) {
        if (i <= indexMaxHeight) get<2>(heights[i]) = 1;
        else get<2>(heights[i]) = 2;
    }

    /* Sorting by height */
    sort(heights.begin(), heights.end());
    reverse(heights.begin(), heights.end());

    monotoneToTriangles(N, heights, triangles, surface, n1, n2); // TODO : case of non-monotone polygons

    return triangles;
}

void monotoneToTriangles(vector<float> N, vector<tuple<float, vector<float>*, int>>& heights,
                        vector<Triangle*>& triangles, Surface& surface, float n1, float n2) {
    
    unsigned int s = heights.size();
    Triangle* triangle = new Triangle(N, *get<1>(heights[s-1]), *get<1>(heights[s-2]),
                            *get<1>(heights[s-3]), surface, n1, n2);

    triangles.push_back(triangle);
    
    if (get<2>(heights[s-2]) == get<2>(heights[s-3])) {
        heights.erase(heights.end()-2);
    } else {
        heights.pop_back();
    }

    if(heights.size() >= 3)  monotoneToTriangles(N, heights, triangles, surface, n1, n2);
}

void deleteTextures() {
    for (auto pointer : colors_pointers) delete pointer;
}