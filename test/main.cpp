#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include "../src/kernel.hpp"
#include "../src/camera.hpp"
#include "../src/object.hpp"
#include "../src/source.hpp"
#include "../src/display.hpp"
#include "../src/loadxml.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    unsigned begin, A,B,C, end;
    begin=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
         
    if (argc != 3) {
        cout << "You need 2 arguments : xml source file and tga target image" << endl;
        return -1;
    }

    string file(argv[1]);
    string target(argv[2]);

    Camera camera;
    vector<LightSource*> sources;
    vector<SceneBaseObject*> scene;
    int specular;
    vector<float> ambiant;
    int n;
    int m;

    A=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    
    loadFile(file, specular, ambiant, camera, sources, scene, n, m);
    
    B=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    cout << "temps chargement de la scène: "<< ((float)(B - A))/1000 << "s" << endl;
    
    for (auto object : scene) {
        object->surface.print();
    }

    vector<vector<int>> colors = run(camera, scene, sources, specular, ambiant);
    
    C=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    cout << "temps calcul de l'image: "<< ((float)(C - B))/1000 << "s" << endl;

    savePicture(target.data(), n, m, colors);

    deleteTextures();
    for (auto source : sources) delete source;
    for (auto object : scene) delete object;
    
    end=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    cout << "temps sauvegarde: "<< ((float)(end - C))/1000 << "s" << endl;
    cout << "temps total: "<<((float)(end -begin))/1000 << "s" << endl;
    
    return 0;
}