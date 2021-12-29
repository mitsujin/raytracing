#include <iostream>

#include <float_def.h>

#include <math/vec3.h>
#include <math/ray.h>
#include <hitable_list.h>
#include <sphere.h>
#include <limits>
#include <camera.h>
#include <random>
#include <material.h>
#include <lambertian.h>
#include <metal.h>

using namespace RT;
using Vector3 = RT::Float3;

Vector3 Color(const Ray& r, Hitable* world, int depth)
{
    HitRecord rec;
    if (world->Hit(r, 0.001, std::numeric_limits<Float>::max(), rec))
    {
        Ray scattered;
        Vector3 attenuation;
        if (depth < 50 && rec.Mat->Scatter(r, rec, attenuation, scattered))
        {
            return attenuation * Color(scattered, world, depth+1);
        }
        else
        {
            return Vector3();
        }
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

    HitableList world;
    world.Register(std::make_unique<Sphere>(Vector3(0.0, 0.0, -1.0f), 0.5f, std::make_unique<Lambertian>(Vector3(0.8, 0.3, 0.3))));
    world.Register(std::make_unique<Sphere>(Vector3(0.0, -100.5, -1.0f), 100, std::make_unique<Lambertian>(Vector3(0.8, 0.8, 0.0))));
    world.Register(std::make_unique<Sphere>(Vector3(1.0, 0.0, -1.0f), 0.5f, std::make_unique<Metal>(Vector3(0.8, 0.6, 0.2))));
    world.Register(std::make_unique<Sphere>(Vector3(-1.0, 0.0, -1.0f), 0.5f, std::make_unique<Metal>(Vector3(0.8, 0.8, 0.8))));

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
                col += Color(r, &world, 0);
            }
            col /= float(ns);
            col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
