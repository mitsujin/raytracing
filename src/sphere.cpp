#include "sphere.h"

#include <math/vec3.h>
#include <math/ray.h>

namespace RT
{
    
    bool Sphere::Hit(const Ray_t<Float>& r, Float t_min, Float t_max, HitRecord& rec) const
    {
        Vec3<Float> oc = r.Origin() - m_center;
        float a = Dot(r.Direction(), r.Direction());
        float b = Dot(oc, r.Direction());
        float c = Dot(oc, oc) - m_radius*m_radius;
        float discriminant = b*b - a*c;
        if (discriminant > 0)
        {
            Float sqrtDet = sqrt(discriminant);
            Float temp = (-b - sqrtDet) / a;

            if (temp < t_max && temp > t_min)
            {
                rec.T = temp;
                rec.P = r.PointAtParameter(rec.T);
                rec.Normal = (rec.P - m_center) / m_radius;
                return true;
            }
            temp = (-b + sqrtDet) /a;
            if (temp < t_max && temp > t_min)
            {
                rec.T = temp;
                rec.P = r.PointAtParameter(rec.T);
                rec.Normal = (rec.P - m_center) / m_radius;
                return true;
            }
        }
        return false;
    }
    
}
