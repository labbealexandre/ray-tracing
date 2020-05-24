#include <vector>
#include "camera.hpp"
#include "object.hpp"
#include "source.hpp"
#include "loadxml.hpp"

void loadInputs(    int& specular, std::vector<float>& ambiant,
                    Camera& camera, std::vector<LightSource*>& sources,
                    std::vector<SceneBaseObject*>& scene, int& n, int& m);