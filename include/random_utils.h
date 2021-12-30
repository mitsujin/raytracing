#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <random_gen.h>
#include <math/vec3.h>

namespace RT
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

#endif /* RANDOM_UTILS_H */
