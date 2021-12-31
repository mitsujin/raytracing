#include <metal.h>
#include <hitable.h>
#include <random_utils.h>
#include <ray_utils.h>

namespace RT
{
    bool Metal::Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const 
    {
        Vec3<Float> reflected = Reflect(rIn.Direction().Normalize(), rec.Normal);
        scattered = Ray_t<Float>(rec.P, reflected + m_fuzz * RandomInUnitSphere()); 
        attenuation = m_albedo;
        return (Dot(scattered.Direction(), rec.Normal) > 0);
    }
}
