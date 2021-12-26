#ifndef HITABLE_H
#define HITABLE_H

#include <float_def.h>
#include <math/vec3.h>
#include <math/ray.h>

namespace RT
{
    struct HitRecord
    {
        Float T; 
        Vec3<Float> P;
        Vec3<Float> Normal;
    };

    class Hitable
    {
    public:    
        virtual bool Hit(const Ray_t<Float>& r, Float t_min, Float t_max, HitRecord& rec) const = 0;
    };
};

#endif /* HITABLE_H */
