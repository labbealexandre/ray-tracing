#include <vector>
#include <cmath>

/** Overloading the vector operators for positions*/

template <typename T> std::vector<T> operator + (const std::vector<T>&, const std::vector<T>&);
template <typename T> std::vector<T> operator - (const std::vector<T>&, const std::vector<T>&);
template <typename T> T operator * (const std::vector<T>&, const std::vector<T>&); // scalar product
template <typename T> std::vector<T> operator * (const T&, const std::vector<T>&);
template <typename T> std::vector<T> normalise(const std::vector<T>&);


template <typename T>
std::vector<T> operator + (std::vector<T> const& left, std::vector<T> const& right) {
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
std::vector<T> operator - (std::vector<T> const& left, std::vector<T> const& right) {
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

float operator * (std::vector<float> const& left, std::vector<float> const& right) {
    float res = 0;
    if (left.size() != right.size()) {
        res+= left[0] * right[0];
    } else {
        // TODO : handle error
    }

    return res;
}

std::vector<float> operator * (float const& left, std::vector<float> const& right) {
    std::vector<float> res;
    for (int i = 0; i < right.size(); i++) {
        res[i] = left * right[i];
    }

    return res;
}

std::vector<float> operator / (std::vector<float> const& left, float const& right) {
    std::vector<float> res;
    for (int i = 0; i < left.size(); i++) {
        res[i] = left[i] / right;
    }

    return res;
}

std::vector<float> normalise (std::vector<float> const& vec) {
    std::vector<float> res;
    float norm = 0;
    for (int i = 0; i < vec.size(); i++) {
        norm = sqrt(norm*norm + vec[i]*vec[i]);
    }
    res = vec / norm;
    return res;
}

int main(){

    return 0;
}