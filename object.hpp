#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <iostream>
#include "surface.hpp"
#include "source.hpp"
#include "utils.hpp"
#include "ray.hpp"
#include <cmath>

class SCENE_BASE_OBJECT {

    public:
        OBJECT_BASE_SURFACE surface;
        std::vector<float> center;
        virtual std::vector<float> getNormal(std::vector<float> P);
        virtual std::vector<float> getIntersection(RAY L, int&);
        bool isItLit(std::vector<float> P, std::vector<float> positionLight);
        
        // TOTEST Now
        std::vector<float> getIllumination(
            std::vector<float> L,
            std::vector<float> N,
            std::vector<float> V,
            std::vector<float> R,
            int specular
        );

        // TODO Later for recursive points
        // std::vector<float> getReflectedRayDirection(std::vector<float> V, std::vector<float> N);
        // std::vector<float> getRefractedRay(std::vector<float> V, std::vector<float> N);

        std::vector<float> getReflectedRayDirection(std::vector<float> V, std::vector<float> N);
        std::vector<float> getRefractedRayDirection(std::vector<float> V, std::vector<float> N);

        virtual void print();
        virtual void name();

        /** Constructors */
        SCENE_BASE_OBJECT() {
            for(int i = 0; i < 3; i++) {
                center.push_back(0);
            }
        }

        /** Destructor */
        ~SCENE_BASE_OBJECT(){}
};

class SPHERE_OBJECT : public SCENE_BASE_OBJECT{

    private:
      float radius;
      
    public:
        std::vector<float> getNormal(std::vector<float> P);
        std::vector<float> getIntersection(RAY L, int&);
        void print();
        void name();

        /** Constructors */
        SPHERE_OBJECT() {
            for(int i = 0; i < 3; i++) {
                center.push_back(0);
            }
            radius = 0;
        }

        SPHERE_OBJECT(std::vector<float> centre, float r, OBJECT_BASE_SURFACE s) {
          center=centre;
          radius=r;
          surface=s;
        }

        /** Destructor */
        ~SPHERE_OBJECT(){}

};

class PLAN_OBJECT : public SCENE_BASE_OBJECT{
    private:
      std::vector<float>  normal;
    public:

        std::vector<float> getNormal();
        std::vector<float> getNormal(std::vector<float> P);
        std::vector<float> getIntersection(RAY L, int&);
        void print();
        void name();

        /** Constructors */
        PLAN_OBJECT(std::vector<float> point, std::vector<float> vect , OBJECT_BASE_SURFACE texture) {
          center=point;
          normal=vect;
          surface=texture;
        }

        /** Destructor */
        ~PLAN_OBJECT(){}

};

class TRIANGLE_OBJECT : public SCENE_BASE_OBJECT{
    private:
      std::vector<float>  puntouno;
      std::vector<float>  puntodos;
      std::vector<float>  puntotres;
    public:
        std::vector<float> getNormal();
        std::vector<float> getNormal(std::vector<float> P);
        std::vector<float> getIntersection(RAY L, int&);
        void print();
        void name();

        /** Constructors */
        TRIANGLE_OBJECT(std::vector<float> pointA, std::vector<float> pointB, std::vector<float> pointC , OBJECT_BASE_SURFACE texture) {

          float d = 3;
          center=(pointA+pointB+pointC)/d;
          puntouno=pointA;
          puntodos=pointB;
          puntotres=pointC;
          surface=texture;
        }

        /** Destructor */
        ~TRIANGLE_OBJECT();

};

#endif
