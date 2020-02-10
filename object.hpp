#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <iostream>
#include "surface.hpp"
#include "source.hpp"
#include "utils.hpp"
#include "ray.hpp"
#include <cmath>

class SceneBaseObject {

    public:
        Surface surface;
        std::vector<float> center;
        float n1, n2;
        std::vector<float> getNormal(std::vector<float> P);                       // Return the normal to the object at the point P
        std::vector<float> getIntersection(RAY L, int&);                          // Return the intersection between the object and a ray
        std::vector<float> getColor(const std::vector<float> &P);                 // Return the color of the object at the point P

        virtual int type();
        bool isItLit(std::vector<float> P, std::vector<float> positionLight, std::vector<SceneBaseObject*> &scene);
        // Return true if the point P is lit, and false if it is in shadows
        
        std::vector<float> getIllumination(                                       // Return the light level of the object at the point P
            const std::vector<float>& P,
            const std::vector<float>& L,
            const std::vector<float>& N,
            const std::vector<float>& V,
            const std::vector<float>& R,
            int specular
        );

        std::vector<float> getReflectedRayDirection(std::vector<float> V, std::vector<float> P);
        // Return the direction vector of a ray reflected on the object at the point P
        std::vector<float> getRefractedRayDirection(std::vector<float> V, std::vector<float> P, int& code);
        // Return the direction vector of a ray refracted by the object at the point P
        virtual void print();
        virtual void name();

        /** Constructors */
        SceneBaseObject() {
            for(int i = 0; i < 3; i++) {
                center.push_back(0);
            }
        }

        /** Destructor */
        ~SceneBaseObject(){}
};

class Sphere : public SceneBaseObject{

    private:
      float radius;
      
    public:
        std::vector<float> getNormal(std::vector<float> P);
        std::vector<float> getIntersection(RAY L, int&);
        void print();
        void name();
        int type();

        /** Constructors */
        Sphere() {
            for(int i = 0; i < 3; i++) {
                center.push_back(0);
            }
            radius = 0;
            n1 = 0;
            n2 = 0;
        }

        Sphere(std::vector<float> centre, float r, Surface s, float indice1, float indice2) {
          center=centre;
          radius=r;
          surface=s;
          n1 = indice1;
          n2 = indice2;
        }

        /** Destructor */
        ~Sphere(){}

};

class Plan : public SceneBaseObject {
    private:
      std::vector<float>  normal;
    public:

        std::vector<float> getNormal();
        std::vector<float> getNormal(std::vector<float> P);
        std::vector<float> getIntersection(RAY L, int&);
        std::vector<float> getColor(const std::vector<float> &P);
        void print();
        void name();
        int type();

        /** Constructors */
        Plan(std::vector<float> point, std::vector<float> vect , Surface texture, 
                    float indice1, float indice2) {
          center=point;
          normal=vect;
          surface=texture;
          n1 = indice1;
          n2 = indice2;
        }

        /** Destructor */
        ~Plan(){}

};

class Triangle : public SceneBaseObject{
    private:
      std::vector<float> normal;
      std::vector<float>  A;
      std::vector<float>  B;
      std::vector<float>  C;
    public:
        std::vector<float> getNormal();
        std::vector<float> getNormal(std::vector<float> P);
        std::vector<float> getIntersection(RAY L, int&);
        void print();
        void name();
        int type();

        /** Constructors */
        Triangle(std::vector<float> N, std::vector<float> pointA, std::vector<float> pointB,
                        std::vector<float> pointC, Surface texture, float indice1, float indice2) {

          float d = 3;
          center=(pointA+pointB+pointC)/d;
          normal = N;
          A=pointA;
          B=pointB;
          C=pointC;
          surface=texture;
          n1 = indice1;
          n2 = indice2;
        }

        /** Destructor */
        ~Triangle(){};
};

#endif
