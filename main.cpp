#include <vector>
#include <string>
#include "kernel.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "source.hpp"
#include "display.hpp"
#include "loadxml.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        std::cout << "You need 2 arguments : xml source file and tga target image" << std::endl;
        return -1;
    }

    std::string file(argv[1]);
    std::string target(argv[2]);

    Camera camera;
    std::vector<LightSource*> sources;
    std::vector<SceneBaseObject*> scene;
    int specular;
    std::vector<int> ambiant;
    int n;
    int m;

    loadFile(file, specular, ambiant, camera, sources, scene, n, m);

    std::vector<std::vector<int>> colors = run(camera, scene, sources, specular, ambiant);

    savePicture(target.data(), n, m, colors);

    return 0;
}