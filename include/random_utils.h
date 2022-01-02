#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <random_gen.h>
#include <math/vec3.h>
#include <float_def.h>

namespace RT
{
    Vec3<Float> RandomInUnitSphere();
    Vec3<Float> RandomInUnitDisk();
}

#endif /* RANDOM_UTILS_H */
