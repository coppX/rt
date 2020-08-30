#include "bbox.h"
#include "../include/ray.h"
namespace rt
{
    BBox surround(const BBox& b1, const BBox& b2) {
        float x1 = b1.boxMin()[0];
        float x2 = b2.boxMin()[0];
        float x3 = b1.boxMax()[0];
        float x4 = b2.boxMax()[0];

        float y1 = b1.boxMin()[1];
        float y2 = b2.boxMin()[1];
        float y3 = b1.boxMax()[1];
        float y4 = b2.boxMax()[1];

        float z1 = b1.boxMin()[2];
        float z2 = b2.boxMin()[2];
        float z3 = b1.boxMax()[2];
        float z4 = b2.boxMax()[2];

        return BBox(
            Vec3(x1 < x2 ? x1 : x2, y1 < y2 ? y1 : y2, z1 < z2 ? z1 : z2),
            Vec3(x3 > x4 ? x3 : x4, y3 > y4 ? y3 : y4, z3 > z4 ? z3 : z4)
        );
    }
    
    //FIXME
    bool BBox::intersect(const Ray& r) const {
        // float t0, t1;
        // float min = -infinity;
        // float max = infinity;

        return false;
    }
} // namespace rt

