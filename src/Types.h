#ifndef TYPES_H
#define TYPES_H

#include <math.h>
#include <iostream>

template <class T>
struct vec2
{
    T x = 0;
    T y = 0;
    vec2() : x(0), y(0) {}
    vec2(T _x) : x(_x), y(_x) {}
    vec2(T _x, T _y) : x(_x), y(_y) {}
    vec2 floor() const { return vec2(std::floor(x), std::floor(y)); }
    bool operator==(const vec2 &rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
    bool operator!=(const vec2 &rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
    vec2 operator+(const vec2 &rhs) const { return vec2(this->x + rhs.x, this->y + rhs.y); }
    vec2 operator-(const vec2 &rhs) const { return vec2(this->x - rhs.x, this->y - rhs.y); }
    vec2 operator*(const T &rhs) const { return vec2(T(this->x * rhs), T(this->y * rhs)); } // Non-commutative implementation so far
    vec2 operator/(const T &rhs) const { return vec2(T(this->x / rhs), T(this->y / rhs)); } // Non-commutative implementation so far
    T magnitude() const { return T(std::sqrt(x * x + y * y)); }
    friend std::ostream &operator<<(std::ostream &os, const vec2 &rhs)
    {
        os << "{ x: " + std::to_string(rhs.x) + ", y: " + std::to_string(rhs.y) + " }\n";
        return os;
    }
};

typedef vec2<int> vec2i;
typedef vec2<float> vec2f;

#endif
