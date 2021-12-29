#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <material.h>

namespace RT
{
    class Lambertian : public Material
    {
    public:

        Lambertian(const Vec3<Float>& albedo)
        : m_albedo(albedo) {}

        bool Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const override;

    private:
        Vec3<Float> m_albedo;
    };
}

#endif /* LAMBERTIAN_H */
