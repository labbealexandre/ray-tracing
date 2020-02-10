#include "display.hpp"

using namespace std;

/** Build and save the picture **/
void savePicture( const string& filename, int W, int H, const vector<vector<int>>& nbIters)
{
    ofstream ofs( filename.c_str(), ios::out | ios::binary );
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
vector<vector<float>>* loadPicture( const string& filename, int& n, int& m) {
    cout << filename << endl;

    ifstream ifs; 
    ifs.open(filename, ios::binary);

    vector<vector<float>>* p_colors = new vector<vector<float>>();

    try { 
        if (ifs.fail()) { 
            throw("Can't open input file"); 
        }
        string header;
        float b;
        ifs >> header; 
        if (header.compare("P6") != 0) throw("Can't read input file"); 
        ifs >> n >> m >> b;
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 
        for (int i = 0; i < n * m; ++i) {
            vector<float> color;
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

