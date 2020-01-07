# include "object.hpp"
# include "source.hpp"
# include "camera.hpp"
# include "ray.hpp"
#include "basic_types.hpp"

image run(
    CAMERA &,
    std::vector<SPHERE_OBJECT> &,
    std::vector<LIGHT_SOURCE> &
);