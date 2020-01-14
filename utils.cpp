#include "utils.hpp"

template <typename T>
std::vector<T> operator + (std::vector<T> const& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (int i = 0; i < left.size(); i++) {
            res[i] = left[i] + right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
std::vector<T> operator - (std::vector<T> const& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (int i = 0; i < left.size(); i++) {
            res[i] = left[i] - right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
T operator * (std::vector<T> const& left, std::vector<T> const& right) {
    T res = 0;
    if (left.size() == right.size()) {
        res+= left[0] * right[0];
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
std::vector<T> operator * (T const& left, std::vector<T> const& right) {
    std::vector<T> res(right.size());
    for (int i = 0; i < right.size(); i++) {
        res[i] = left * right[i];
    }

    return res;
}

template <typename T>
std::vector<T> operator / (std::vector<T> const& left, T const& right) {
    std::vector<T> res(left.size());
    for (int i = 0; i < left.size(); i++) {
        res[i] = left[i] / right;
    }

    return res;
}

template <typename T>
std::vector<T> normalise (std::vector<T> const& vec) {
    std::vector<T> res(vec.size());
    T norm = 0;
    for (int i = 0; i < vec.size(); i++) {
        norm = sqrt(norm*norm + vec[i]*vec[i]);
    }
    res = vec / norm;
    return res;
}
