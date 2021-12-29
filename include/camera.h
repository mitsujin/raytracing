#ifndef CAMERA_H
#define CAMERA_H

#include <math/ray.h>

namespace RT
{
    class Camera
    {
    public:
        Camera()
        : m_origin(0.0, 0.0, 0.0)
        , m_lowerLeftCorner(-2.0, -1.0, -1.0)
        , m_vertical(0.0, 2.0, 0.0)
        , m_horizontal(4.0, 0.0, 0.0)
        {}

        Ray GetRay(Float u, Float v)
        {
            return Ray(m_origin, m_lowerLeftCorner + u*m_horizontal + v * m_vertical - m_origin);
        }

    private:
        Vec3<Float> m_origin;
        Vec3<Float> m_lowerLeftCorner;
        Vec3<Float> m_horizontal;
        Vec3<Float> m_vertical;
    };
}

#endif /* CAMERA_H */
