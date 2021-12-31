#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include <material.h>

namespace RT
{
    class Dielectric : public Material
    {
    public:
        Dielectric(Float ri)
        : m_refractionIndex(ri)
        {}

        bool Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const override;

    private:
        Float m_refractionIndex;
    };
}

#endif /* DIELECTRIC_H */
