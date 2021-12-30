#include <lambertian.h>
#include <random_utils.h>
#include <hitable.h>

namespace RT
{
    bool Lambertian::Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const 
    {
        Vec3<Float> target = rec.P + rec.Normal + RandomInUnitSphere();
        scattered = Ray_t<Float>(rec.P, target-rec.P);
        attenuation = m_albedo;
        return true;
    }
}
