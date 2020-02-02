#ifndef KERNEL_HPP
#define KERNEL_HPP

# include <cmath>
# include "object.hpp"
# include "source.hpp"
# include "camera.hpp"
# include "ray.hpp"
# include "utils.hpp"

std::vector<std::vector<int>> run(
    CAMERA &,
    std::vector<SCENE_BASE_OBJECT*> &,
    std::vector<LIGHT_SOURCE*> &,
    int,
    std::vector<int>&
);

std::vector<int> getColors( 
    RAY& ray, std::vector<float>& origin,
    std::vector<SCENE_BASE_OBJECT*> &scene,
    std::vector<LIGHT_SOURCE*> &sources,
    int specular,
    const std::vector<int> &ambiant
);

#endif