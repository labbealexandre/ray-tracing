#include "display.hpp"

/** Build and save the picture **/
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

/** Load textures **/
std::vector<std::vector<float>>* loadPicture( const std::string& filename, int& n, int& m) {
    std::cout << filename << std::endl;

    std::ifstream ifs; 
    ifs.open(filename, std::ios::binary);

    std::vector<std::vector<float>>* p_colors = new std::vector<std::vector<float>>();

    try { 
        if (ifs.fail()) { 
            throw("Can't open input file"); 
        }
        std::string header;
        float b;
        ifs >> header; 
        if (header.compare("P6") != 0) throw("Can't read input file"); 
        ifs >> n >> m >> b;
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 
        for (int i = 0; i < n * m; ++i) {
            std::vector<float> color;
            ifs.read(reinterpret_cast<char *>(pix), 3);
            
            for (int i = 0; i < 3; i++) {
                color.push_back(pix[i] / 255.f);
            }

            p_colors->push_back(color);
        } 
        ifs.close(); 
    } 
    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ifs.close(); 
    }

    return p_colors;
}

