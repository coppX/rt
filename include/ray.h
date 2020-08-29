#ifndef __RAY_H__
#define __RAY_H__

#include "vec3.h"
namespace rt {
    //光线的表示p(t) = A + t * B, A表示光源，B表示光线方向向量，b有一定长度，t就是倍数time
    class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction, double time)
            : orig(origin), dir(direction), tm(time)
        {}

        point3 origin() const { return orig; }
        vec3 direction() const { return dir; }
        double time() const { return tm; }

        point3 at(double t) const {
            return orig + t * dir;
        }
    private:
        point3 orig;
        vec3 dir;
        double tm;
    };
}

#endif