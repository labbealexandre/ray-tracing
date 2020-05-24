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
#include "../src/input.hpp"

using namespace std;

Camera camera;
vector<LightSource*> sources;
vector<SceneBaseObject*> scene;
int specular;
vector<float> ambiant;
int n;
int m;

void initParams() {
    specular = 10;
    n = 512; m = 512;
    for (int i = 0; i < 3; i++) {
        ambiant.push_back(0.3);
    }
}

void initCamera() {
    camera = Camera();
}

void addSource() {
    LightSource* source = new LightSource();
    sources.push_back(source);
}

int main(int argc, char const *argv[])
{
    unsigned A,B,C, end;
    A=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    int _target;
    if (argc == 2) {
        _target = 1;
        B=A;
        loadInputs(specular, ambiant, camera, sources, scene, n, m);
        initParams();
        initCamera();
        addSource();
    } else if (argc == 3) {
        _target = 2;
        string file(argv[1]);
        loadFile(file, specular, ambiant, camera, sources, scene, n, m);
        B=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << "temps chargement de la scène: "<< ((float)(B - A))/1000 << "s" << endl;
    } else {
        cout << "You need 2 arguments : xml source file and tga target image" << endl;
        return -1;
    }

    string target(argv[_target]);
    
    vector<vector<int>> colors = run(camera, scene, sources, specular, ambiant);
    
    C=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    cout << "temps calcul de l'image: "<< ((float)(C - B))/1000 << "s" << endl;

    savePicture(target.data(), n, m, colors);

    deleteTextures();
    for (auto source : sources) delete source;
    for (auto object : scene) delete object;
    
    end=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    cout << "temps sauvegarde: "<< ((float)(end - C))/1000 << "s" << endl;
    cout << "temps total: "<<((float)(end - A))/1000 << "s" << endl;
    
    return 0;
}