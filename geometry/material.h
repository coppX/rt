#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "../include/vec3.h"

namespace rt {
    class Material {
    public:
        
        Material()
            : ambient_(), diffuse_(), specular_(),reflect_(0.1, 0.1, 0.1),
            emission_(), shiness_(0.0), t_(1.0), ior_(0.0)
        {}

        void setAmbient(const Color a) {
            ambient_ = a;
        }

        void setDiffuse(const Color d) {
            diffuse_ = d;
        }
        void setSpecular(const Color s) {
            specular_ = s;
        }
        void setReflect(const Color r) {
            reflect_ = r;
        }
    private:
        Color ambient_;
        Color diffuse_;
        Color specular_;
        Color reflect_;
        Color emission_;
        float shiness_;
        float t_;
        float ior_;
    };
}

#endif