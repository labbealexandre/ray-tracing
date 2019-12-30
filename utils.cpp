#include <vector>

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