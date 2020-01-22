#include "display.hpp"

/** Construit et sauvegarde l'image **/
void savePicture( const std::string& filename, int W, int H, const std::vector<std::vector<int>>& nbIters)
{
    std::ofstream ofs( filename.c_str(), std::ios::out | std::ios::binary );
    ofs << "P6\n" << W << " " << H << "\n255\n";
    
    for ( int i = 0; i < W * H; ++i ) {
        
        double iter = (double)nbIters[i][0];
        double itev = (double)nbIters[i][1];
        double iteb = (double)nbIters[i][2];
        unsigned char r = (unsigned char)((unsigned (iter) & 0xFF));
        unsigned char b = (unsigned char)((unsigned (iteb) & 0xFF));
        unsigned char g = (unsigned char)((unsigned (itev) & 0xFF));
        
        ofs << r << g << b;
    }
    
    ofs.close();
}

