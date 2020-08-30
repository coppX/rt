#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>
#include <iostream>
#include <algorithm>
#include "utils.h"

namespace rt {

    using namespace Utils;
    class Vec3 {
        public:
            Vec3() {
                e[0] = e[1] = e[2] = 0;
            }
            Vec3(double e0, double e1, double e2) {
                e[0] = e0;
                e[1] = e1;
                e[2] = e2;
            }

            double x() const { return e[0]; } 
            double y() const { return e[1]; }
            double z() const { return e[2]; }

            Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
            double operator[](int i) const { return e[i]; };
            double operator[](int i) { return e[i]; }

            Vec3& operator+=(const Vec3 &v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
            }

            Vec3& operator*=(const double t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                return *this;
            }

            Vec3& operator/=(const double t) {
                return *this *= 1/t;
            }

            double length_squared() const {
                return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
            }

            double length() const {
                return sqrt(length_squared());
            }

            void write_color(std::ostream &out, int samples_per_pixel) {
                if (e[0] != e[0]) e[0] = 0.0;
                if (e[1] != e[1]) e[1] = 0.0;
                if (e[2] != e[2]) e[2] = 0.0;

                auto scale = 1.0 / samples_per_pixel;
                auto r = sqrt(scale * e[0]);
                auto g = sqrt(scale * e[1]);
                auto b = sqrt(scale * e[2]);

                out << static_cast<int>(256 * clamp<double>(r, 0.0, 0.999)) << " "
                    << static_cast<int>(256 * clamp<double>(g, 0.0, 0.999)) << " "
                    << static_cast<int>(256 * clamp<double>(b, 0.0, 0.999)) << "\n";
            }

        inline static Vec3 random() {
            return Vec3(random_double(), random_double(), random_double());
        }

        inline static Vec3 random(double min, double max) {
            return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
        public:
            double e[3];
    };

    using Point3 = Vec3;
    using Color = Vec3;

    inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
        return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
    }

    inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline Vec3 operator*(double t, const Vec3 &v) {
        return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    inline Vec3 operator*(const Vec3 &v, double t) {
        return t * v;
    }

    inline Vec3 operator/(Vec3 v, double t) {
        return (1 / t) * v;
    }
    //向量点乘
    inline double dot(const Vec3 &u, const Vec3 &v) {
        return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; 
    }
    //向量叉乘
    inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }
    //向量单位化
    inline Vec3 unit_vector(Vec3 v) {
        return v / v.length();
    }

    Vec3 random_in_unit_disk() {
        while (true) {
            auto p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
            if (p.length_squared() >= 1) continue;
            return p;
        }
    }

    Vec3 random_unit_vector() {
        auto a = random_double(0, 2 * pi);
        auto z = random_double(-1, 1);
        auto r = sqrt(1 - z * z);
        return Vec3(r * cos(a), r * sin(a), z);
    }

    Vec3 random_in_unit_sphere() {
        while (true) {
            auto p = Vec3::random(-1, 1);
            if (p.length_squared() >= 1) continue;
            return p;
        }
    }

    Vec3 random_in_hemisphere(const Vec3& normal) {
        Vec3 in_unit_sphere = random_in_unit_sphere();
        if (dot(in_unit_sphere, normal) > 0.0)
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }

    Vec3 reflect(const Vec3& v, const Vec3& n) {
        return v - 2*dot(v, n) * n;
    }

    Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
        auto cos_theta = fmin(dot(-uv, n), 1.0);
        Vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
        Vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
        return r_out_parallel + r_out_perp;
    }
}

#endif