# Ray-Tracing

This project includes a ray-tracing engine coded in C++ based on the CPU. Scenes are described in XML files. The output is an image with the _Portable Pixmap_ format (.ppm).

## Requirements

- Linux environment (tested on Debian 12)
- g++ compiler
- imagemagick (in order to convert to popular image format, ex: .png)

## Installation

```bash
make
```

## Execution

```bash
./bin/main <path to xml scene> <path to output file>
```

ex:

```bash
./bin/main scenes/ReflexionSphere.xml assets/ReflexionSphere.ppm
```

Convert to png image:

```bash
convert assets/ReflexionSphere.ppm assets/ReflexionSphere.png
```
