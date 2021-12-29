#include <iostream>

#include <float_def.h>

#include <math/vec3.h>
#include <math/ray.h>
#include <hitable_list.h>
#include <sphere.h>
#include <limits>
#include <camera.h>
#include <random>

using namespace RT;
using Vector3 = RT::Float3;

std::random_device g_rd;
std::minstd_rand g_mt(g_rd());
std::uniform_real_distribution<Float> g_dist(-1.0f, 1.0f);


Vector3 RandomInUnitSphere()
{
    while (true)
    {
        Vector3 pt(g_dist(g_mt), g_dist(g_mt), g_dist(g_mt));
        if (pt.LengthSq() < 1)
        {
            return pt;
        }
    }
}

Vector3 Color(const Ray& r, Hitable* world)
{
    HitRecord rec;
    if (world->Hit(r, 0.0, std::numeric_limits<Float>::max(), rec))
    {
        Vector3 target = rec.P + rec.Normal + RandomInUnitSphere();
        return 0.5f * Color(Ray(rec.P, target - rec.P), world);
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
    int ns = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    Vector3 vertical(0.0f, 2.0f, 0.0f);
    Vector3 origin(0.0f, 0.0f, 0.0f);

    Hitable* hList[2];
    hList[0] = new Sphere(Vector3(0.0, 0.0, -1.0f), 0.5f);
    hList[1] = new Sphere(Vector3(0.0, -100.5, -1.0f), 100);
    Hitable* world = new HitableList(hList, 2);

    Camera cam;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<Float> dist(0.0f, 1.0f);

    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vector3 col;
            for (int s=0; s < ns; s++)
            {
                float u = float(i + dist(mt)) / float(nx);
                float v = float(j + dist(mt)) / float(ny);
                auto r = cam.GetRay(u, v);
                col += Color(r, world);
            }
            col /= float(ns);
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
