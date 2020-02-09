#ifndef KERNEL_HPP
#define KERNEL_HPP

# include <cmath>
#include <chrono>
#include <iostream>
# include "object.hpp"
# include "source.hpp"
# include "camera.hpp"
# include "ray.hpp"
# include "utils.hpp"

std::vector<std::vector<int>> run(
    Camera &,
    std::vector<SceneBaseObject*> &,
    std::vector<LightSource*> &,
    int,
    std::vector<int>&
);

std::vector<int> getColors( 
    RAY& ray, std::vector<float>& origin,
    std::vector<SceneBaseObject*> &scene,
    std::vector<LightSource*> &sources,
    int specular,
    const std::vector<int> &ambiant,
    int stack
);

#endif