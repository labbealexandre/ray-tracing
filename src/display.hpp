# include <iostream>
# include <cstdlib>
# include <string>
# include <chrono>
# include <cmath>
# include <vector>
# include <fstream>

/** Construit et sauvegarde l'image **/
void savePicture( const std::string& filename, int W, int H, const std::vector<std::vector<int>>& nbIters);

std::vector<std::vector<float>>* loadPicture( const std::string& filename, int& n, int& m);
