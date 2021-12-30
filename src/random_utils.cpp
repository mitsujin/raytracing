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
}
