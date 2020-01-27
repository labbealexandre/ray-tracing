#include <vector>
#include "kernel.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "source.hpp"
#include "surface.hpp"
#include "display.hpp"

int main(int argc, char const *argv[])
{
    std::vector<SPHERE_OBJECT> spheres;
    std::vector<PLAN_OBJECT> plans;
    std::vector<LIGHT_SOURCE> sources;

    OBJECT_BASE_SURFACE surface;
    std::vector<float> center = {50, 0, 0};
    float radius = 10;
    SPHERE_OBJECT sphere(center, radius, surface);
    spheres.push_back(sphere);

    std::vector<float> p_point = {140, 0, 0};
    std::vector<float> p_direction = {-1, 0, 0};
    PLAN_OBJECT plan(p_point, p_direction, surface);
    // plans.push_back(plan);

    std::vector<float> l_center = {0, 0, 50};
    std::vector<int> color = {255, 255, 255};
    LIGHT_SOURCE source(l_center, color);
    sources.push_back(source);

    const float W = 10;
    const float H = 10;
    const float focal = 5;
    const int n = 2000;
    const int m = 2000;
    std::vector<float> c_center = {0, 0, 0};
    CAMERA camera(c_center, W, H, focal, n, m);

    std::vector<std::vector<int>> colors = run(camera, spheres, plans, sources);

    savePicture("./test.tga", n, m, colors);

    return 0;
}
