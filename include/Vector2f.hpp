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

    Vector2f(float p_X = 0.0f, float p_Y = 0.0f);
    Vector2f(int p_X, int p_Y);

    float X;
    float Y;

    void Normalize();
    float Angle() const;
    float Length() const;
    static Vector2f CalculateDirection(float p_Angle);
    static Vector2f LinearInterp(const Vector2f& p_Vector1, const Vector2f& p_Vector2, const float& p_Weight);

    Vector2f operator+(const Vector2f& p_Vector) const;
    Vector2f operator-(const Vector2f& p_Vector) const;
    Vector2f operator*(int p_Scalar) const;
    Vector2f operator*(float p_Scalar) const;
    Vector2f operator/(int p_Scalar) const;
    Vector2f operator/(float p_Scalar) const;

    void operator=(const Vector2f& p_Vector);
    void operator+=(const Vector2f& p_Vector);
    void operator-=(const Vector2f& p_Vector);

};

Vector2f operator*(int p_Scalar, const Vector2f& p_Vector);
Vector2f operator*(float p_Scalar, const Vector2f& p_Vector);

#endif
