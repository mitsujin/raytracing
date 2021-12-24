#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace RT
{
    template <typename T>
    class Vec3
    {
    public:
        Vec3() : m_x(0), m_y(0), m_z(0) {}
        Vec3(T x, T y, T z)
        : m_x(x)
        , m_y(y)
        , m_z(z) {}

        inline T x() const { return m_x; }
        inline T y() const { return m_y; }
        inline T z() const { return m_z; }
        inline T r() const { return m_x; }
        inline T g() const { return m_y; }
        inline T b() const { return m_z; }

        inline Vec3 operator-() const { return Vec3(-m_x, -m_y, -m_z); }

        inline T operator[] (int i) const { return m_data[i]; }

        inline Vec3& operator += (const Vec3& o)
        {
            m_x += o.m_x;
            m_y += o.m_y;
            m_z += o.m_z;

            return *this;
        }

        inline Vec3& operator -= (const Vec3& o)
        {
            m_x -= o.m_x;
            m_y -= o.m_y;
            m_z -= o.m_z;

            return *this;
        }

        inline Vec3& operator /= (const Vec3& o)
        {
            m_x /= o.m_x;
            m_y /= o.m_y;
            m_z /= o.m_z;

            return *this;
        }

        inline Vec3& operator *= (T t)
        {
            m_x *= t;
            m_y *= t;
            m_z *= t;
            return *this;
        }

        inline Vec3& operator /= (T t)
        {
            m_x /= t;
            m_y /= t;
            m_z /= t;
            return *this;
        }

        inline T Length() const
        {
            return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        }

        inline T LengthSq() const 
        {
            return m_x * m_x + m_y * m_y + m_z * m_z;
        }

    private:
        union
        {
            struct
            {
                T m_x;
                T m_y;
                T m_z;
            };
            struct
            {
                T m_r;
                T m_g;
                T m_b;
            };
            T m_data[3];
        };
    };

    using Float3 = Vec3<float>;
    using Double3 = Vec3<double>;
}
