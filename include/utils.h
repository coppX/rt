#ifndef __UTILS_H__
#define __UTILS_H__

#include <algorithm>

namespace utils {
    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    template<typename T>
    inline T clamp(T x, T min, T max) {
        return std::max(std::min(x, max), min);
    }

    inline double random_double() {
        return rand() / (RAND_MAX + 1.0);
    }

    inline double random_double(int min, int max) {
        return min + (max - min) * random_double();
    }
    
    //角度转弧度
    inline double degress_to_radians(double degress) {
        return degress * pi / 180.0;
    }
}

#endif