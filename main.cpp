#include "kernel.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "source.hpp"
#include "surface.hpp"

int main(int argc, char const *argv[])
{
    OBJECT_BASE_SURFACE surface();
    SPHERE_OBJECT sphere({100, 0, 0}, 10);

    return 0;
}
