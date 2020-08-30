#ifndef __RAY_H__
#define __RAY_H__

#include "vec3.h"
namespace rt {
    //光线的表示p(t) = A + t * B, A表示光源，B表示光线方向向量，b有一定长度，t就是倍数time
    class Ray {
    public:
        Ray() {}
        Ray(const Point3& origin, const Vec3& direction, double time)
            : orig(origin), dir(direction), tm(time)
        {}

        Point3 origin() const { return orig; }
        Vec3 direction() const { return dir; }
        double time() const { return tm; }

        Point3 at(double t) const {
            return orig + t * dir;
        }
    private:
        Point3 orig;
        Vec3 dir;
        double tm;
    };
}

#endif