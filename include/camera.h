#ifndef CAMERA_H
#define CAMERA_H

#include <math/ray.h>
#include <random_utils.h>

namespace RT
{
    class Camera
    {
    public:
        Camera(Vec3<Float> lookFrom, Vec3<Float> lookAt, Vec3<Float> vUp, Float vFov, Float aspect, Float aperture, Float focusDistance)
        : m_origin(0.0, 0.0, 0.0)
        , m_lowerLeftCorner(-2.0, -1.0, -1.0)
        , m_vertical(0.0, 2.0, 0.0)
        , m_horizontal(4.0, 0.0, 0.0)
        {
            m_lensRadius = aperture / 2.0;
            Float theta = vFov * M_PI / 180;
            Float halfHeight = tan(theta/2); 
            Float halfWidth = aspect * halfHeight;

            m_origin = lookFrom;
            m_w = (lookFrom - lookAt).Normalize();
            m_u = Cross(vUp, m_w).Normalize();
            m_v = Cross(m_w, m_u);

            m_lowerLeftCorner = m_origin - halfWidth * focusDistance * m_u - halfHeight * focusDistance * m_v - focusDistance * m_w;
            m_horizontal = 2 * halfWidth * focusDistance * m_u;
            m_vertical = 2*halfHeight * focusDistance * m_v;
        }

        Ray GetRay(Float s, Float t)
        {
            Vec3<Float> rd = m_lensRadius * RandomInUnitDisk();
            Vec3<Float> offset = m_u * rd.x() + m_v * rd.y();

            return Ray(m_origin + offset, m_lowerLeftCorner + s*m_horizontal + t * m_vertical - m_origin - offset);
        }

    private:
        Vec3<Float> m_origin;
        Vec3<Float> m_lowerLeftCorner;
        Vec3<Float> m_horizontal;
        Vec3<Float> m_vertical;
        Float m_lensRadius;
        Vec3<Float> m_u;
        Vec3<Float> m_v;
        Vec3<Float> m_w;
    };
}

#endif /* CAMERA_H */
