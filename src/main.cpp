#include <iostream>
#include <math/vec3.h>
#include <math/ray.h>

using namespace RT;
using Vector3 = RT::Float3;

float HitSphere(const Vector3& center, float radius, const Ray& r)
{
    Vector3 oc = r.Origin() - center;
    float a = Dot(r.Direction(), r.Direction());
    float b = 2.0f * Dot(oc, r.Direction());
    float c = Dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0)
    {
        return -1.0f;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

Vector3 Color(const Ray& r)
{
    float t = HitSphere(Vector3(0.0f, 0.0f, -1.f), 0.5f, r);

    if (t > 0.0f)
    {
        Vector3 N = (r.PointAtParameter(t) - Vector3(0,0,-1.0f)).Normalize();
        return 0.5f * Vector3(N.x()+1, N.y()+1, N.z()+1);
    }
    Vector3 unitDirection = r.Direction().Normalize();
    t = 0.5f * (unitDirection.y() + 1.0f);
    return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
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

    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical);
            Vector3 col = Color(r);
            float b = 0.2f;
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
