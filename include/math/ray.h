#ifndef RAY_H
#define RAY_H

#include <math/vec3.h>

namespace RT
{
    template <typename T>
    class Ray_t
    {
    public:
        Ray_t(const Vec3<T> a, const Vec3<T>& b)
        : m_a(a), m_b(b)
        {

        }

        Vec3<T> Origin() const { return m_a; }
        Vec3<T> Direction() const { return m_b; }
        Vec3<T> PointAtParameter(T t) const { return m_a + t*m_b; }

    private:
        Vec3<T> m_a;
        Vec3<T> m_b;
    };

    using Ray = Ray_t<float>;
}

#endif /* RAY_H */
