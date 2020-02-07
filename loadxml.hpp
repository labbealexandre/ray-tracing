#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml2/tinyxml2.h"
#include "texture.hpp"
#include "object.hpp"
#include "surface.hpp"
#include "display.hpp"
#include "camera.hpp"

std::vector<float> loadCoords(tinyxml2::XMLHandle &hCoords);
std::vector<int> loadColors(tinyxml2::XMLHandle &hColors);
TEXTURE loadTexture(tinyxml2::XMLHandle &hTexture);
OBJECT_BASE_SURFACE loadSurface(tinyxml2::XMLHandle &hSurface);
void loadFile(  std::string file, int& specular, std::vector<int>& ambiant,
                CAMERA& camera, std::vector<LIGHT_SOURCE*>& sources,
                std::vector<SCENE_BASE_OBJECT*>& scene, int& n, int& m);
