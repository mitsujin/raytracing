#include <lambertian.h>
#include <random_gen.h>
#include <hitable.h>

namespace RT
{
    namespace
    {
        Vec3<Float> RandomInUnitSphere()
        {
            auto& gen = RandomGen<Float>::Inst();
            while (true)
            {
                Vec3<Float> pt(gen(-1.0f, 1.0f), gen(-1.0f, 1.0f), gen(-1.0f, 1.0f));
                if (pt.LengthSq() < 1)
                {
                    return pt;
                }
            }
        }
    }

    bool Lambertian::Scatter(const Ray_t<Float>& rIn, const HitRecord& rec, Vec3<Float>& attenuation, Ray_t<Float>& scattered) const 
    {
        Vec3<Float> target = rec.P + rec.Normal + RandomInUnitSphere();
        scattered = Ray_t<Float>(rec.P, target-rec.P);
        attenuation = m_albedo;
        return true;
    }
}
