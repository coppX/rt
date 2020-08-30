#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "../include/utils.h"
#include "../include/vec3.h"
#include "../include/ray.h"

#include "bbox.h"
#include "material.h"

namespace rt {
    class HitRecord;
    class Shape {
    public:
        Shape() {}
        virtual ~Shape();
        virtual bool intersect(const Ray& ray, HitRecord& record) {
            std::cerr << "intersect not implemented yet\n";
            return false;
        }

        virtual Material getMaterial() {
            std::cerr<< "getMaterial not implemented yet\n";
            return material;
        }

        virtual BBox boundingBox() {
            return bbox;
        }

        virtual void updateBoundingBox() {
            std::cerr<< "updateBoundingBox not implemented yet\n";
        }

    protected:
        Material material;
        BBox bbox;
    };

    class HitRecord {
    public:
        HitRecord()
            : pos_(), normal_(), t_(infinity), obj_(nullptr), tex_col_(1.0, 1.0, 1.0)
        {}
        Point3 pos_;
        Vec3 normal_;
        float t_;
        Shape *obj_;
        Color tex_col_;
    };

    class Sphere : public Shape {
    public:
        Sphere(const Point3& p, float r)
            : center_(p), radius_(r)
        {}
        bool intersect(const Ray& ray, HitRecord& record) {
            Vec3 op = center_ - ray.origin();
            float eps = 1e-4;
            float b = dot(ray.direction(), op);
            float det = b * b - dot(op, op) + radius_ * radius_;
            float t = infinity;
            if (det < 0)
                return false;
            else
                det = sqrt(det);
            t = b - det;
            if (t < eps) {
                t = b + det;
                if (t < eps) {
                    return false;
                }
            }
            record.t_ = t;
            record.obj_ = this;
            record.pos_ = ray.origin() + record.t_ * ray.direction();
            record.normal_ = record.pos_ - center_;
            record.normal_.normalize();
            return true;
        }
    private:
        Point3  center_;
        float   radius_;
    };
}

#endif