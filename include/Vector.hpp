// Vector.hpp

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

class Vector
{
  public:
    static const Vector Zero;
    static const Vector One;
    static const Vector Up;
    static const Vector Down;
    static const Vector Left;
    static const Vector Right;

    Vector(float x = 0.0f, float y = 0.0f);

    float X;
    float Y;

    void Normalize();
    float Angle() const;
    float Length() const;
    static Vector CalculateDirection(float angle);
    static Vector LinearInterp(const Vector& v1, const Vector& v2, const float& weight);

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(int mag) const;
    Vector operator*(float mag) const;
    Vector operator/(int mag) const;
    Vector operator/(float mag) const;

    void operator=(const Vector& v);
    void operator+=(const Vector& v);
    void operator-=(const Vector& v);

};

Vector operator*(int mag, const Vector& v);
Vector operator*(float mag, const Vector& v);

#endif
