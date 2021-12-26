#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"

namespace RT
{
    class HitableList : public Hitable
    {
    public:
        HitableList(Hitable** l, int n)
        : m_list(l), m_size(n) {}

        bool Hit(const Ray_t<Float>& r, Float t_min, Float t_max, HitRecord& rec) const override;

    private:
        Hitable** m_list;
        int m_size;
    };
}

#endif /* HITABLE_LIST_H */
