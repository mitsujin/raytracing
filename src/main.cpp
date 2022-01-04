#include <iostream>

#include <float_def.h>

#include <chrono>
#include <math/vec3.h>
#include <math/ray.h>
#include <hitable_list.h>
#include <sphere.h>
#include <limits>
#include <camera.h>
#include <random>
#include <material.h>
#include <lambertian.h>
#include <dielectric.h>
#include <metal.h>

using namespace RT;
using Vector3 = RT::Float3;

Vector3 Color(const Ray& r, Hitable* world, int depth)
{
    HitRecord rec;
    if (depth <= 0)
    {
        return Vector3();
    }
    
    if (world->Hit(r, 0.001, std::numeric_limits<Float>::max(), rec))
    {
        Ray scattered;
        Vector3 attenuation;
        if (rec.Mat->Scatter(r, rec, attenuation, scattered))
        {
            return attenuation * Color(scattered, world, depth-1);
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

Vector3 ColorNonRecursive(Ray ray, Hitable* world, int maxDepth)
{
    Ray scattered;
    HitRecord rec;
    Vector3 attenuation;
    Vector3 combinedColor(1.0f, 1.0f, 1.0f);
    for (int i = maxDepth; i >= 0; i--)
    {
        if (world->Hit(ray, 0.001, std::numeric_limits<Float>::max(), rec))
        {
            if (rec.Mat->Scatter(ray, rec, attenuation, scattered))
            {
                combinedColor *= attenuation;
                ray = scattered;
            }
            else
            {
                // black
                combinedColor = Vector3();
                break;
            }
        }
        else
        {
            Vector3 unitDirection = ray.Direction().Normalize();
            float t = 0.5f * (unitDirection.y() + 1.0f);
            combinedColor *= (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
            break;
        }
    }

    return combinedColor;
}

std::unique_ptr<HitableList> MakeWorld()
{
    int n = 500;
    auto world = std::make_unique<HitableList>();
    world->Add(std::make_unique<Sphere>(Vector3(0,-1000,0), 1000, std::make_unique<Lambertian>(Vector3(0.5,0.5,0.5)))); 

    auto& gen = RandomGen<Float>::Inst();

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto chooseMat = gen(0.0, 1.0);
            Vector3 center(a + 0.9 * gen(0.0, 1.0), 0.2, b * 0.9 * gen(0.0, 1.0));

            if ((center - Vector3(4, 0.2, 0)).Length() > 0.9)
            {
                std::shared_ptr<Material> sphereMat;
                if (chooseMat < 0.8)
                {
                    // diffuse
                    auto albedo = Vector3(gen(0.0, 1.0), gen(0.0, 1.0), gen(0.0, 1.0)) * Vector3(gen(0.0, 1.0), gen(0.0, 1.0), gen(0.0, 1.0));
                    sphereMat = std::make_shared<Lambertian>(albedo);
                    world->Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
                }
                else if (chooseMat < 0.95)
                {
                    // metal
                    auto albedo = Vector3(gen(0.5, 1.0), gen(0.5, 1.0), gen(0.5, 1.0));
                    auto fuzz = gen(0.0, 0.5);
                    sphereMat = std::make_shared<Metal>(albedo, fuzz);
                    world->Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
                }
                else 
                {
                    // glass
                    sphereMat = std::make_shared<Dielectric>(1.5);
                    world->Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
                }
            }
        }

        auto mat1 = std::make_shared<Dielectric>(1.5);
        world->Add(std::make_shared<Sphere>(Vector3(0, 1, 0), 1.0, mat1));

        auto mat2 = std::make_shared<Lambertian>(Vector3(0.4, 0.2, 0.1));
        world->Add(std::make_shared<Sphere>(Vector3(-4, 1, 0), 1.0, mat2));

        auto mat3 = std::make_shared<Metal>(Vector3(0.7, 0.6, 0.5), 0.0);
        world->Add(std::make_shared<Sphere>(Vector3(4, 1, 0), 1.0, mat3));
    }
    return std::move(world);       
}

int main()
{
    int imageWidth = 1400;
    int imageHeight = 933;
    int samplesPerPixel = 100;
    int maxDepth = 50;

    int* imageBuffer = new int[imageWidth * imageHeight * 3];

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    Vector3 vertical(0.0f, 2.0f, 0.0f);
    Vector3 origin(0.0f, 0.0f, 0.0f);

    auto worldPtr = MakeWorld();
    auto& world = *worldPtr;

    Vector3 lookFrom(13,2,3);
    Float aspectRatio = 3.0 / 2.0;
    Vector3 lookAt(0,0,0);
    float distToFocus = 10.0f;
    float aperture = 0.1;

    Camera cam(lookFrom, lookAt, Vector3(0,1,0), 20.0f, Float(imageWidth) / Float(imageHeight), aperture, distToFocus);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<Float> dist(0.0f, 1.0f);

    auto start = std::chrono::high_resolution_clock::now();
    auto stride = imageWidth * 3;

    #pragma omp parallel for num_threads(24)
    for(int j = imageHeight-1; j >= 0; j--)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            Vector3 col;
            for (int s=0; s < samplesPerPixel; s++)
            {
                float u = float(i + dist(mt)) / float(imageWidth-1);
                float v = float(j + dist(mt)) / float(imageHeight-1);
                auto r = cam.GetRay(u, v);
                col += ColorNonRecursive(r, &world, maxDepth);
                //col += Color(r, &world, maxDepth);
            }
            col /= float(samplesPerPixel);
            col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            imageBuffer[j*stride + i*3] = ir;
            imageBuffer[j*stride + i*3+1] = ig;
            imageBuffer[j*stride + i*3+2] = ib;
            //std::cout << (j*imageWidth + i) << "," << ir << " " << ig << " " << ib << "\n";
        }
    }

    for (int j = imageHeight-1; j>= 0; j--)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            std::cout << imageBuffer[j*stride + i*3] << " " << imageBuffer[j*stride + i*3+1] << " " << imageBuffer[j*stride + i*3+2] << "\n";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cerr << "Duration: " << std::chrono::duration_cast<std::chrono::seconds>(end-start).count() << " seconds" << std::endl;
}
