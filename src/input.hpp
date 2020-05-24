#include <vector>
#include "../src/camera.hpp"
#include "../src/object.hpp"
#include "../src/source.hpp"

void loadInputs(    int& specular, std::vector<float>& ambiant,
                    Camera& camera, std::vector<LightSource*>& sources,
                    std::vector<SceneBaseObject*>& scene, int& n, int& m);