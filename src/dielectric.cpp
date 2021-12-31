#include <dielectric.h>
#include <ray_utils.h>
#include <hitable.h>

namespace RT
{
    bool Dielectric::Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const
    {
        Vec3<Float> outwardNormal;
        Float niOvernt = 0.0f;
        attenuation = Vec3<Float>(1.0, 1.0, 1.0);
        Vec3<Float> refracted;
        if (Dot(rIn.Direction(), rec.Normal) > 0)
        {
            outwardNormal = -rec.Normal;
            niOvernt = m_refractionIndex; 
        }
        else 
        {
            outwardNormal = rec.Normal;
            niOvernt = 1.0 / m_refractionIndex; 
        }

        if (Refract(rIn.Direction(), outwardNormal, niOvernt, refracted))
        {
            scattered = Ray_t<Float>(rec.P, refracted);
            return true;
        }
        else
        {
            Vec3<Float> reflected = Reflect(rIn.Direction(), rec.Normal);
            scattered = Ray_t<Float>(rec.P, reflected);
            return false;
        }
    }

    
}
