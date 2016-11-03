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

Vector2f::Vector2f(float x, float y)
{
  X = x;
  Y = y;
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

Vector2f Vector2f::CalculateDirection(float angle)
{
  Vector2f vector;
  vector.X = sinf(angle);
  vector.Y = cosf(angle);

  return vector;
}

Vector2f Vector2f::LinearInterp(const Vector2f& v1, const Vector2f& v2, const float& weight)
{
  if (weight <= 0.0f)
  {
    return v1;
  }

  if (weight >= 1.0f)
  {
    return v2;
  }

  Vector2f vector;
  vector.X = v1.X * (1.0f - weight) + v2.X * weight;
  vector.Y = v1.Y * (1.0f - weight) + v2.Y * weight;

  return vector;
}

Vector2f Vector2f::operator+(const Vector2f& v) const
{
  Vector2f vector;
  vector.X = X + v.X;
  vector.Y = Y + v.Y;

  return vector;
}

Vector2f Vector2f::operator-(const Vector2f& v) const
{
  Vector2f vector;
  vector.X = X - v.X;
  vector.Y = Y - v.Y;

  return vector;
}

Vector2f Vector2f::operator*(int mag) const
{
  Vector2f vector;
  vector.X = X * static_cast<float>(mag);
  vector.Y = Y * static_cast<float>(mag);

  return vector;
}

Vector2f Vector2f::operator*(float mag) const
{
  Vector2f vector;
  vector.X = X * mag;
  vector.Y = Y * mag;

  return vector;
}

Vector2f Vector2f::operator/(int mag) const
{
  Vector2f vector;
  vector.X = X / static_cast<float>(mag);
  vector.Y = Y / static_cast<float>(mag);

  return vector;
}

Vector2f Vector2f::operator/(float mag) const
{
  Vector2f vector;
  vector.X = X / mag;
  vector.Y = Y / mag;

  return vector;
}

void Vector2f::operator=(const Vector2f& v)
{
  X = v.X;
  Y = v.Y;
}

void Vector2f::operator+=(const Vector2f& v)
{
  X += v.X;
  Y += v.Y;
}

void Vector2f::operator-=(const Vector2f& v)
{
  X -= v.X;
  Y -= v.Y;
}

Vector2f operator*(int mag, const Vector2f& v)
{
  Vector2f vector;
  vector.X = v.X * static_cast<float>(mag);
  vector.Y = v.Y * static_cast<float>(mag);

  return vector;
}

Vector2f operator*(float mag, const Vector2f& v)
{
  Vector2f vector;
  vector.X = v.X * mag;
  vector.Y = v.Y * mag;

  return vector;
}
