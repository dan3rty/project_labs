#include <cstdio>
#include <cmath>

int main()
{
    std::puts("Please, enter 'a', 'b' and 'c' for `ax^2 + bx + c = 0`:");
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float d = (b * b) - (4 * a * c);
    if (d < 0)
    {
        std::printf("No solutions");
        return 0;
    }
    float x1 = (-b - std::sqrt(d)) / (2 * a);
    if (d == 0)
    {
        std::printf("x = %f\n", x1);
    }
    else
    {
        float x2 = (-b + std::sqrt(d)) / (2 * a);
        std::printf("x1 = %f\nx2 = %f\n", x1, x2);
    }
}
