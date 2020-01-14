#include <vector>
#include "kernel.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "source.hpp"
#include "surface.hpp"

int main(int argc, char const *argv[])
{
    OBJECT_BASE_SURFACE surface;

    std::vector<float> center = {100, 0, 0};
    float radius = 10;
    SPHERE_OBJECT sphere(center, radius, surface);
    std::vector<float> l_center = {0, 0, 50};
    std::vector<int> color = {255, 255, 255};
    LIGHT_SOURCE source(l_center, color);

    return 0;
}
