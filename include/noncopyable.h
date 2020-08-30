#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

namespace rt {
    class NonCopyable {
    public:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;
    };
}

#endif