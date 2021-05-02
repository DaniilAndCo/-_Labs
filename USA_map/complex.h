#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>
class complex
{
private:
    double x, y;

public:
    complex() : x(0), y(0) {}
    complex(const double &_x, const double& _y) : x(_x), y(_y) {}
    complex operator + (const complex &other)
    {
        return complex(x + other.x, y + other.y);
    }
    complex operator * (const complex &other)
    {
        return complex(x*other.x  - y*other.y, x*other.y + y*other.x);
    }
    complex operator = (const complex &other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
    double ABS()
    {
        return sqrt(x*x + y*y);
    }
    ~complex(){}


};
#endif // COMPLEX_H
