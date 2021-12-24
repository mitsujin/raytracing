#include "gtest/gtest.h"
#include <math/vec3.h>

namespace RT
{
    TEST(Vec3Tests, TestConstructor)
    {
        Double3 v;
        EXPECT_EQ(0.0, v.x());    
        EXPECT_EQ(0.0, v.y());    
        EXPECT_EQ(0.0, v.z());    
    }
}
