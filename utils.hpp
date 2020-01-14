#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <cmath>
/** Overloading the vector operators for positions*/

template <typename T> std::vector<T> operator + (const std::vector<T>&, const std::vector<T>&);
template <typename T> std::vector<T> operator - (const std::vector<T>&, const std::vector<T>&);
template <typename T> T operator * (const std::vector<T>&, const std::vector<T>&); // scalar product
template <typename T> std::vector<T> operator * (const T&, const std::vector<T>&);
template <typename T> std::vector<T> normalise(const std::vector<T>&);
template <typename T> std::vector<T> operator / (std::vector<T> const& left, T const& right);
std::vector<int> operator * (const std::vector<int>&, const std::vector<float>&);

#endif