#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include "noncopyable.h"

#include <assert.h>
#include <stdlib.h>
#include <mutex>

namespace rt {
    template<typename T>
    struct has_no_destroy {
        template<typename C> static char test(decltype(&C::no_destroy));
        template<typename C> static int32_t test(...);
        const static bool value = sizeof(test<T>(0)) == 1;
    };

    template<typename T>
    class Singleton : NonCopyable {
    public:
        Singleton() = delete;
        ~Singleton() = delete;

        static T& instance() {
            std::call_once(flag_, &Singleton::init);
            assert(nullptr != value_);
            return *value_;
        }

    private:
        static void init() {
            value_ = new T();
            if (!has_no_destroy<T>::value) {
                ::atexit(destroy);
            }
        }

        static void destroy() {
            typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
            T_must_be_complete_type dummy; (void) dummy;

            delete value_;
            value_ = nullptr;
        }
    private:
        static std::once_flag   flag_;
        static T*               value_;
    };

    template<typename T>
    T* Singleton<T>::value_ = nullptr;

}

#endif