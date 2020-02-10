#ifndef KERNEL_HPP
#define KERNEL_HPP

# include <cmath>
#include <chrono>
#include <iostream>
#include <omp.h>
# include <cstdlib>
# include "object.hpp"
# include "source.hpp"
# include "camera.hpp"
# include "ray.hpp"
# include "utils.hpp"

std::vector<std::vector<int>> run(
    Camera& camera,
    std::vector<SceneBaseObject*>& scene,
    std::vector<LightSource*>& sources,
    int specular,
    std::vector<float>& ambiant
);

std::vector<int> getColors( 
    Ray& ray, std::vector<float>& origin,
    std::vector<SceneBaseObject*>& scene,
    std::vector<LightSource*>& sources,
    int specular,
    const std::vector<float>& ambiant,
    int stack
);

#endif