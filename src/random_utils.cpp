#include "random_utils.h"

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

    Vec3<Float> RandomInUnitDisk()
    {
        auto& gen = RandomGen<Float>::Inst();
        Vec3<Float> p;
        do {
            p = (Float)2.0 * Vec3<Float>(gen(0.0, 1.0), gen(0.0, 1.0), 0.0);
        } while (Dot(p,p) >= 1.0);
        return p;
    }
}
