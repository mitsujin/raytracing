#include "hitable_list.h"

#include <math/vec3.h>
#include <math/ray.h>

namespace RT
{   
    bool HitableList::Hit(const Ray_t<Float>& r, Float t_min, Float t_max, HitRecord& rec) const
    {
        HitRecord temp;
        bool hit = false;
        Float closestSoFar = t_max;
        for (int i = 0; i < m_size; i++)
        {
            if (m_list[i]->Hit(r, t_min, closestSoFar, temp))
            {
                hit = true;
                closestSoFar = temp.T;
                rec = temp;
            }
        }
        return hit;
    }
}
