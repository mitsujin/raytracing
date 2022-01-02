#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"
#include <vector>
#include <memory>

namespace RT
{
    class HitableList : public Hitable
    {
    public:
        void Add(std::shared_ptr<Hitable> hitable)
        {
            m_list.push_back(hitable);
        }

        bool Hit(const Ray_t<Float>& r, Float t_min, Float t_max, HitRecord& rec) const override;

    private:
        std::vector<std::shared_ptr<Hitable>> m_list;
    };
}

#endif /* HITABLE_LIST_H */
