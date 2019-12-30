#include <vector>

template <typename T> std::vector<T> operator + (std::vector<T>, std::vector<T>);
template <typename T> std::vector<T> operator - (std::vector<T>, std::vector<T>);

/** scalar product */
template <typename T> T operator * (std::vector<T>, std::vector<T>);

template <typename T> std::vector<T> operator * (T, std::vector<T>);