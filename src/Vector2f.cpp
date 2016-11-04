// Vector2f.cpp

// STL Includes
#define _USE_MATH_DEFINES
#include <math.h>
// AOS Includes
#include "Vector2f.hpp"

const Vector2f Vector2f::Zero = Vector2f(0.0f, 0.0f);
const Vector2f Vector2f::One = Vector2f(1.0f, 1.0f);
const Vector2f Vector2f::Up = Vector2f(0.0f, -1.0f);
const Vector2f Vector2f::Down = Vector2f(0.0f, 1.0f);
const Vector2f Vector2f::Left = Vector2f(-1.0f, 0.0f);
const Vector2f Vector2f::Right = Vector2f(1.0f, 0.0f);

Vector2f::Vector2f(float p_X, float p_Y)
{
  X = p_X;
  Y = p_Y;
}

void Vector2f::Normalize()
{
  float length = Length();
  if (length > 0.0f)
  {
    X /= length;
    Y /= length;
  }
}

float Vector2f::Angle() const
{
  if (X == 0.0f)
  {
    if (Y > 0.0f)
    {
      return static_cast<float>(M_PI / 2.0f);
    }
    else
    {
      return static_cast<float>(3.0f * M_PI / 2.0f);
    }
  }

  float omega = fabsf(Y / X);
  float angle = atanf(omega);

  if (X < 0.0f && Y >= 0.0f)
  {
    return static_cast<float>(M_PI - angle);
  }

  if (X < 0.0f && Y <= 0.0f)
  {
    return static_cast<float>(M_PI + angle);
  }

  if (X > 0.0f && Y <= 0.0f)
  {
    return static_cast<float>(2.0f * M_PI - angle);
  }

  return angle;
}

float Vector2f::Length() const
{
  return sqrtf(X * X + Y * Y);
}

Vector2f Vector2f::CalculateDirection(float p_Angle)
{
  Vector2f vector;
  vector.X = sinf(p_Angle);
  vector.Y = cosf(p_Angle);

  return vector;
}

Vector2f Vector2f::LinearInterp(const Vector2f& p_Vector1, const Vector2f& p_Vector2, const float& p_Weight)
{
  if (p_Weight <= 0.0f)
  {
    return p_Vector1;
  }

  if (p_Weight >= 1.0f)
  {
    return p_Vector2;
  }

  Vector2f vector;
  vector.X = p_Vector1.X * (1.0f - p_Weight) + p_Vector2.X * p_Weight;
  vector.Y = p_Vector1.Y * (1.0f - p_Weight) + p_Vector2.Y * p_Weight;

  return vector;
}

Vector2f Vector2f::operator+(const Vector2f& p_Vector) const
{
  Vector2f vector;
  vector.X = X + p_Vector.X;
  vector.Y = Y + p_Vector.Y;

  return vector;
}

Vector2f Vector2f::operator-(const Vector2f& p_Vector) const
{
  Vector2f vector;
  vector.X = X - p_Vector.X;
  vector.Y = Y - p_Vector.Y;

  return vector;
}

Vector2f Vector2f::operator*(int p_Scalar) const
{
  Vector2f vector;
  vector.X = X * static_cast<float>(p_Scalar);
  vector.Y = Y * static_cast<float>(p_Scalar);

  return vector;
}

Vector2f Vector2f::operator*(float p_Scalar) const
{
  Vector2f vector;
  vector.X = X * p_Scalar;
  vector.Y = Y * p_Scalar;

  return vector;
}

Vector2f Vector2f::operator/(int p_Scalar) const
{
  Vector2f vector;
  vector.X = X / static_cast<float>(p_Scalar);
  vector.Y = Y / static_cast<float>(p_Scalar);

  return vector;
}

Vector2f Vector2f::operator/(float p_Scalar) const
{
  Vector2f vector;
  vector.X = X / p_Scalar;
  vector.Y = Y / p_Scalar;

  return vector;
}

void Vector2f::operator=(const Vector2f& p_Vector)
{
  X = p_Vector.X;
  Y = p_Vector.Y;
}

void Vector2f::operator+=(const Vector2f& p_Vector)
{
  X += p_Vector.X;
  Y += p_Vector.Y;
}

void Vector2f::operator-=(const Vector2f& p_Vector)
{
  X -= p_Vector.X;
  Y -= p_Vector.Y;
}

Vector2f operator*(int p_Scalar, const Vector2f& p_Vector)
{
  Vector2f vector;
  vector.X = p_Vector.X * static_cast<float>(p_Scalar);
  vector.Y = p_Vector.Y * static_cast<float>(p_Scalar);

  return vector;
}

Vector2f operator*(float p_Scalar, const Vector2f& p_Vector)
{
  Vector2f vector;
  vector.X = p_Vector.X * p_Scalar;
  vector.Y = p_Vector.Y * p_Scalar;

  return vector;
}
