#include <iostream>

#include <float_def.h>

#include <math/vec3.h>
#include <math/ray.h>
#include <hitable_list.h>
#include <sphere.h>
#include <limits>

using namespace RT;
using Vector3 = RT::Float3;

Vector3 Color(const Ray& r, Hitable* world)
{
    HitRecord rec;
    if (world->Hit(r, 0.0, std::numeric_limits<Float>::max(), rec))
    {
        auto& N = rec.Normal;
        return 0.5f * Vector3(N.x()+1, N.y()+1, N.z()+1);
    }
    else
    {
        Vector3 unitDirection = r.Direction().Normalize();
        float t = 0.5f * (unitDirection.y() + 1.0f);
        return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    Vector3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
    Vector3 horizontal(4.0f, 0.0f, 0.0f);
    Vector3 vertical(0.0f, 2.0f, 0.0f);
    Vector3 origin(0.0f, 0.0f, 0.0f);

    Hitable* hList[2];
    hList[0] = new Sphere(Vector3(0.0, 0.0, -1.0f), 0.5f);
    hList[1] = new Sphere(Vector3(0.0, -100.5, -1.0f), 100);
    Hitable* world = new HitableList(hList, 2);

    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical);
            Vector3 col = Color(r, world);
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
