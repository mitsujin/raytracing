#ifndef UTILS_H
#define UTILS_H

namespace RT
{
    template <typename T>
    bool Refract(const Vec3<T>& v, const Vec3<T>& n, T niOvernt, Vec3<T>& refracted)
    {
        auto uv = v.Normalize();
        T dt = Dot(uv, n);
        T discrimnant = 1.0 - niOvernt * niOvernt * (1 - dt*dt);
        if (discrimnant > 0)
        {
            refracted = niOvernt * (uv - n*dt) - n*sqrt(discrimnant);
            return true;
        }
        return false;
    }

    template <typename T>
    Vec3<T> Reflect(const Vec3<T>& v, const Vec3<T>& n)
    {
        return v - 2 * Dot(v, n) * n;
    }
}

#endif /* UTILS_H */
