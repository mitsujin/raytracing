#include <metal.h>
#include <hitable.h>

namespace RT
{
    namespace
    {
        Vec3<Float> Reflect(const Vec3<Float>& v, const Vec3<Float>& n)
        {
            return v - 2 * Dot(v, n) * n;
        }
    }
    
    bool Metal::Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const 
    {
        Vec3<Float> reflected = Reflect(rIn.Direction().Normalize(), rec.Normal);
        scattered = Ray_t<Float>(rec.P, reflected); 
        attenuation = m_albedo;
        return (Dot(scattered.Direction(), rec.Normal) > 0);
    }
}
