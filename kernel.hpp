#ifndef KERNEL_HPP
#define KERNEL_HPP

# include "object.hpp"
# include "source.hpp"
# include "camera.hpp"
# include "ray.hpp"

std::vector<std::vector<int>> run(
    CAMERA &,
    std::vector<SCENE_BASE_OBJECT*> &,
    std::vector<LIGHT_SOURCE> &
);

#endif