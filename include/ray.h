#ifndef __RAY_H__
#define __RAY_H__

#include "vec3.h"
#include "copyable.h"
namespace rt {
    //光线的表示p(t) = A + t * B, A表示光源，B表示光线方向向量，b有一定长度，t就是倍数time
    class Ray : public Copyable {
    public:
        Ray() {}
        Ray(const Point3& origin, const Vec3& direction, double time)
            : orig_(origin), dir_(direction), tm_(time)
        {}

        Point3 origin() const { return orig_; }
        Vec3 direction() const { return dir_; }
        double time() const { return tm_; }

        Point3 at(double t) const {
            return orig_ + t * dir_;
        }
    private:
        Point3 orig_;
        Vec3 dir_;
        double tm_;
    };
}

#endif