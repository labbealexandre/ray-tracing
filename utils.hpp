#include <vector>

/** Overloading the vector operators for positions*/

template <typename T> std::vector<T> operator + (std::vector<T>, std::vector<T>);
template <typename T> std::vector<T> operator - (std::vector<T>, std::vector<T>);
template <typename T> T operator * (std::vector<T>, std::vector<T>); // scalar product
template <typename T> std::vector<T> operator * (T, std::vector<T>);
template <typename T> std::vector<T> normalise(std::vector<T>);
template <typename T> std::vector<T> CrossProduct(std::vector<T>, std::vector<T>)
