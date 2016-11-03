// Vector2f.hpp

#ifndef __VECTOR2F_HPP__
#define __VECTOR2F_HPP__

class Vector2f
{
  public:
    static const Vector2f Zero;
    static const Vector2f One;
    static const Vector2f Up;
    static const Vector2f Down;
    static const Vector2f Left;
    static const Vector2f Right;

    Vector2f(float x = 0.0f, float y = 0.0f);

    float X;
    float Y;

    void Normalize();
    float Angle() const;
    float Length() const;
    static Vector2f CalculateDirection(float angle);
    static Vector2f LinearInterp(const Vector2f& v1, const Vector2f& v2, const float& weight);

    Vector2f operator+(const Vector2f& v) const;
    Vector2f operator-(const Vector2f& v) const;
    Vector2f operator*(int mag) const;
    Vector2f operator*(float mag) const;
    Vector2f operator/(int mag) const;
    Vector2f operator/(float mag) const;

    void operator=(const Vector2f& v);
    void operator+=(const Vector2f& v);
    void operator-=(const Vector2f& v);

};

Vector2f operator*(int mag, const Vector2f& v);
Vector2f operator*(float mag, const Vector2f& v);

#endif
