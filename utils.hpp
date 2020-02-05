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
inline void operator += (std::vector<T>& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < left.size(); i++) {
            left[i]+=right[i];
        }
    } else {
        // TODO : handle error
    }
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
inline void operator -= (std::vector<T>& left, std::vector<T> const& right) {
    std::vector<T> res(left.size());
    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < left.size(); i++) {
            left[i]-=right[i];
        }
    } else {
        // TODO : handle error
    }
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
inline std::vector<T> prod(const std::vector<T>& left, const std::vector<T>& right) {
    std::vector<T> res;

    if (left.size() == right.size()) {
        for (unsigned int i = 0; i < right.size(); i++) {
            T result = left[i]*right[i];
            res.push_back(result);
        }
    } else {
        // TODO : handle error
    }
    return res;
}

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

inline void capColors (std::vector<int> &colors) {
    for (int i = 0; i < 3; i++) {
        if (colors[i] > 255) {
            colors[i] = 255;
        }
    }
}

inline void capCoefs (std::vector<float> &coefs) {
    for (int i = 0; i < 3; i++) {
        if (coefs[i] > 1) {
            coefs[i] = 1;
        }
    }
}

template <typename T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& vect) {
    for (T elem : vect) {
        os << elem << " ";
    }
    return os;
}

template <typename T>
inline std::vector<T>& std::max(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> res;
    for (unsigned int i = 0; i < a.size(); i++) {
        res.push_back(std::max(a[i], b[i]));
    }
    return res;
}

#endif
