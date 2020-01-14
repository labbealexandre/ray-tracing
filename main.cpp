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

    return 0;
}
