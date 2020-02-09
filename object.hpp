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
        float n1, n2;
        virtual std::vector<float> getNormal(std::vector<float> P);
        virtual std::vector<float> getIntersection(RAY L, int&);
        virtual std::vector<float> getColor(const std::vector<float> &P);
        virtual int type();
        bool isItLit(std::vector<float> P, std::vector<float> positionLight, std::vector<SCENE_BASE_OBJECT*> &scene);
        
        // TOTEST Now
        std::vector<float> getIllumination(
            const std::vector<float>& P,
            const std::vector<float>& L,
            const std::vector<float>& N,
            const std::vector<float>& V,
            const std::vector<float>& R,
            int specular
        );

        std::vector<float> getReflectedRayDirection(std::vector<float> V, std::vector<float> P);
        std::vector<float> getRefractedRayDirection(std::vector<float> V, std::vector<float> P, int& code);

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
        int type();

        /** Constructors */
        SPHERE_OBJECT() {
            for(int i = 0; i < 3; i++) {
                center.push_back(0);
            }
            radius = 0;
            n1 = 0;
            n2 = 0;
        }

        SPHERE_OBJECT(std::vector<float> centre, float r, OBJECT_BASE_SURFACE s, float indice1, float indice2) {
          center=centre;
          radius=r;
          surface=s;
          n1 = indice1;
          n2 = indice2;
        }

        /** Destructor */
        ~SPHERE_OBJECT(){}

};

class PLAN_OBJECT : public SCENE_BASE_OBJECT {
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
        PLAN_OBJECT(std::vector<float> point, std::vector<float> vect , OBJECT_BASE_SURFACE texture, 
                    float indice1, float indice2) {
          center=point;
          normal=vect;
          surface=texture;
          n1 = indice1;
          n2 = indice2;
        }

        /** Destructor */
        ~PLAN_OBJECT(){}

};

class TRIANGLE_OBJECT : public SCENE_BASE_OBJECT{
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
        TRIANGLE_OBJECT(std::vector<float> N, std::vector<float> pointA, std::vector<float> pointB,
                        std::vector<float> pointC, OBJECT_BASE_SURFACE texture, float indice1, float indice2) {

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
        ~TRIANGLE_OBJECT(){};
};

#endif
