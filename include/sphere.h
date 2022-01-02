#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include <memory>

namespace RT
{
    class Material;
    class Sphere: public Hitable
    {
    public:
        Sphere(Vec3<Float> cen, Float r, std::unique_ptr<Material> mat)
        : m_center(cen), m_radius(r), m_material(std::move(mat)) {}

        bool Hit(const Ray_t<Float>& r, Float t_min, Float t_max, HitRecord& rec) const override;
        
    private:
        Vec3<Float> m_center;
        Float m_radius;
        std::unique_ptr<Material> m_material;
    };
}

#endif /* SPHERE_H */
