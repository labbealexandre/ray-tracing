#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <tuple>
#include "tinyxml2/tinyxml2.h"
#include "texture.hpp"
#include "object.hpp"
#include "surface.hpp"
#include "display.hpp"
#include "camera.hpp"
#include "utils.hpp"

std::vector<float> loadCoords(tinyxml2::XMLHandle &hCoords);
std::vector<int> loadColors(tinyxml2::XMLHandle &hColors);
Texture loadTexture(tinyxml2::XMLHandle &hTexture);
Surface loadSurface(tinyxml2::XMLHandle &hSurface);
void loadFile(  std::string file, int& specular, std::vector<float>& ambiant,
                Camera& camera, std::vector<LightSource*>& sources,
                std::vector<SceneBaseObject*>& scene, int& n, int& m);

std::vector<Triangle*> polyToTriangles(std::vector<float> N, std::vector<std::vector<float>>& corners,
                                            Surface& surface, float n1, float n2);

void monotoneToTriangles(std::vector<float> N, std::vector<std::tuple<float, std::vector<float>*, int>>& heights,
                          std::vector<Triangle*>& triangles, Surface& surface,
                          float n1, float n2);

void deleteTextures();