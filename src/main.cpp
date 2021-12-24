#include <iostream>
#include <math/vec3.h>
#include <math/ray.h>

using namespace RT;

bool HitSphere(const Float3& center, float radius, const Ray& r)
{
    Float3 oc = r.Origin() - center;
    float a = Dot(r.Direction(), r.Direction());
    float b = 2.0f * Dot(oc, r.Direction());
    float c = Dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

Float3 Color(const Ray& r)
{
    if (HitSphere(Float3(0.0f, 0.0f, -1.f), 0.5f, r))
    {
        return Float3(1.0f, 0.0f, 0.0f);
    }
    Float3 unitDirection = r.Direction().Normalize();
    float t = 0.5f * (unitDirection.y() + 1.0f);
    return (1.0f - t) * Float3(1.0f, 1.0f, 1.0f) + t * Float3(0.5f, 0.7f, 1.0f);
}

int main()
{
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    Float3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
    Float3 horizontal(4.0f, 0.0f, 0.0f);
    Float3 vertical(0.0f, 2.0f, 0.0f);
    Float3 origin(0.0f, 0.0f, 0.0f);

    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical);
            Float3 col = Color(r);
            float b = 0.2f;
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
