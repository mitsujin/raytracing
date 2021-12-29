#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

#include <random>

namespace RT
{
    template <typename T>
    class RandomGen
    {
    public:
        static RandomGen& Inst()
        {
            static RandomGen<T> gen;
            return gen;
        }

        T operator()(T min, T max)
        {
            return std::uniform_real_distribution<T>(min, max)(m_mt);
        }

    private:
        std::random_device m_rd;
        std::minstd_rand m_mt;
    };
}

#endif /* RANDOM_GEN_H */
