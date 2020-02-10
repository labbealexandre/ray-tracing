#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <vector>

class Texture {

  public:
    std::vector<std::vector<float>>* p_colors;
    std::vector<float> center;
    std::vector<float> direction;
    float width;
    float height;
    int n;
    int m;

    /** Constructors */
    Texture() {
      p_colors = NULL;
      center = {0, 0, 0};
      direction = {1, 0, 0};
      width = 10;
      height = 10;
      n = 100;
      m = 100;
    };

    Texture(std::vector<std::vector<float>>* p_col, const std::vector<float>& c,
            const std::vector<float>& d, const float& W, const float& H, const int& nWidth, const int& nHeight) {

      p_colors = p_col;
      center = c;
      direction = d;
      width = W;
      height = H;
      n = nWidth;
      m = nHeight;
    };

    /** Destructor */
    ~Texture(){}
};

#endif