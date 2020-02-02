#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <cmath>
#include <iostream>
/** Overloading the vector operators for positions*/

template <typename T>
inline std::vector<T> operator + (std::vector<T> const& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < left.size(); i++) {
            res[i] = left[i] + right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
};

template <typename T>
inline std::vector<T> operator - (std::vector<T> const& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < left.size(); i++) {
            res[i] = left[i] - right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
};

template <typename T>
inline T operator * (std::vector<T> const& left, std::vector<T> const& right) {
    T res = 0;
    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < 3; i++) {
            res+= left[i] * right[i];
        }
    } else {
        // TODO : handle error
    }
    return res;
};

template <typename T>
inline std::vector<T> operator * (T const& left, std::vector<T> const& right) {
    std::vector<T> res(right.size());
    for (unsigned int i = 0; i < right.size(); i++) {
        res[i] = left * right[i];
    }

    return res;
};

template <typename T> std::vector<T> normalise(const std::vector<T>&);

template <typename T>
inline std::vector<T> operator / (std::vector<T> const& left, T const& right) {
    std::vector<T> res(left.size());
    for (unsigned int i = 0; i < left.size(); i++) {
        res[i] = left[i] / right;
    }

    return res;
};

inline std::vector<int> operator * (const std::vector<int>& left, const std::vector<float>& right) {
    std::vector<int> res;

    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < right.size(); i++) {
            float result = left[i]*right[i];
            res.push_back((int)result);
        }
    } else {
        // TODO : handle error
    }
    return res;
};

template <typename T>
inline std::vector<float> CrossProduct(const std::vector<T> &a, const std::vector<T> &b) {
  std::vector<T> r (a.size());
  r[0] = a[1]*b[2]-a[2]*b[1];
  r[1] = a[2]*b[0]-a[0]*b[2];
  r[2] = a[0]*b[1]-a[1]*b[0];
  return r;
};

template <typename T>
inline std::vector<T> normalise (std::vector<T> const& vec) {
    std::vector<T> res(vec.size());
    T norm = 0;
    for (unsigned int i = 0; i < vec.size(); i++) {
        norm = sqrt(norm*norm + vec[i]*vec[i]);
    }
    res = vec / norm;
    return res;
};

template <typename T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& vect) {
    for (T elem : vect) {
        os << elem << " ";
    }
    return os;
}

#endif
