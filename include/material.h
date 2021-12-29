#ifndef MATERIAL_H
#define MATERIAL_H

namespace RT
{
    class Material
    {
    public:
        virtual bool Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const = 0;
    };
}

#endif /* MATERIAL_H */
