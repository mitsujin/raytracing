#ifndef METAL_H
#define METAL_H

#include <material.h>

namespace RT
{
    class Metal : public Material
    {
    public:
        Metal(Vec3<Float> albedo, Float f)
        : m_albedo(albedo) 
        , m_fuzz(std::min<Float>(f, 1.0)) 
        {}

        bool Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const override;

    private:
        Vec3<Float> m_albedo;
        Float m_fuzz = 1.0;
    };
}

#endif /* METAL_H */
