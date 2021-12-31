#include <dielectric.h>
#include <ray_utils.h>
#include <hitable.h>
#include <random_gen.h>

namespace RT
{
    bool Dielectric::Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const
    {
        Vec3<Float> outwardNormal;
        Float niOvernt = 0.0f;
        attenuation = Vec3<Float>(1.0, 1.0, 1.0);
        Vec3<Float> refracted;
        Float reflectProb = 0.0;
        Float cosine = 0.0;

        if (Dot(rIn.Direction(), rec.Normal) > 0)
        {
            outwardNormal = -rec.Normal;
            niOvernt = m_refractionIndex; 
            cosine = m_refractionIndex * Dot(rIn.Direction(), rec.Normal) / rIn.Direction().Length();
        }
        else 
        {
            outwardNormal = rec.Normal;
            niOvernt = 1.0 / m_refractionIndex; 
            cosine = -Dot(rIn.Direction(), rec.Normal) / rIn.Direction().Length();
        }
        Vec3<Float> reflected = Reflect(rIn.Direction(), rec.Normal);

        if (Refract(rIn.Direction(), outwardNormal, niOvernt, refracted))
        {
            reflectProb = Schlick(cosine, m_refractionIndex);
        }
        else
        {
            scattered = Ray_t<Float>(rec.P, reflected);
            reflectProb = 1.0;
        }
        if (RandomGen<Float>::Inst()(0.0f, 1.0f) < reflectProb)
        {
            scattered = Ray_t<Float>(rec.P, reflected);
        }
        else
        {
            scattered = Ray_t<Float>(rec.P, refracted);
        }

        return true;
    }

    
}
