#include <vector>
#include <math.h>

template <typename T>
std::vector<T> operator + (std::vector<T> &left, std::vector<T> &right) {
    std::vector<T> res;
    if (left.size() != right.size()) {
        for (int i = 0; i < left.size(); i++) {
            res[i] = left[i] + right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
std::vector<T> operator - (std::vector<T> &left, std::vector<T> &right) {
    std::vector<T> res;
    if (left.size() != right.size()) {
        for (int i = 0; i < left.size(); i++) {
            res[i] = left[i] - right[i];
        }
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
float operator * (std::vector<float> &left, std::vector<float>&right) {
    float res = 0;
    if (left.size() != right.size()) {
        res+= left[0] * right[0];
    } else {
        // TODO : handle error
    }

    return res;
}

template <typename T>
std::vector<float> operator * (float &left, std::vector<float>&right) {
    std::vector<float> res;
    for (int i = 0; i < right.size(); i++) {
        res[i] = left * right[i];
    }

    return res;
}

template <typename T>
std::vector<float> normalise (std::vector<float>&vec) {
    std::vector<float> res;
    float norm=0;
    for (int i = 0; i < vec.size(); i++) {
        norm = sqrt(norm*norm + vec[i]*vec[i]);
    }
    res=(1/norm)*vec
    return res;
}


template <typename T>
std::vector<float> CrossProduct(std::vector<T> &left, std::vector<T> &right) {
  std::vector<T> r (a.size());
  r[0] = a[1]*b[2]-a[2]*b[1];
  r[1] = a[2]*b[0]-a[0]*b[2];
  r[2] = a[0]*b[1]-a[1]*b[0];
  return r;
}
