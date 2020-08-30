#ifndef __BBOX_H__
#define __BBOX_H__

#include "../include/vec3.h"
#include "../include/ray.h"

namespace rt {
    class BBox {
    public:
        BBox() {};
        BBox(const Vec3& a, const Vec3& b) {
            bb[0] = a;
            bb[1] = b;
        }
        Vec3 boxMin() const { return bb[0]; }
        Vec3 boxMax() const { return bb[1]; }
        bool intersect(const Ray& r) const;
    private:
        Vec3 bb[2];
    };

    BBox surround(const BBox& b1, const BBox& b2);
}

#endif