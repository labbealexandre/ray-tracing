#ifndef KERNEL_HPP
#define KERNEL_HPP

# include "object.hpp"
# include "source.hpp"
# include "camera.hpp"
# include "ray.hpp"

std::vector<std::vector<int>> run(
    CAMERA &,
    std::vector<SPHERE_OBJECT> &,
    std::vector<PLAN_OBJECT> &,
    std::vector<LIGHT_SOURCE> &
);

#endif