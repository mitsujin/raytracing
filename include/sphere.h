#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

namespace RT
{
    class Sphere: public Hitable
    {
    public:
        Sphere(Vec3<Float> cen, Float r)
        : m_center(cen), m_radius(r) {}

        bool Hit(const Ray_t<Float>& r, Float t_min, Float t_max, HitRecord& rec) const override;
        
    private:
        Vec3<Float> m_center;
        Float m_radius;
    };
}

#endif /* SPHERE_H */
