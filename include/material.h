#ifndef MATERIAL_H
#define MATERIAL_H

#include <float_def.h>
#include <math/ray.h>

namespace RT
{
    class HitRecord;
    class Material
    {
    public:
        virtual bool Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const = 0;

        virtual ~Material() = default;
    };
}

#endif /* MATERIAL_H */
