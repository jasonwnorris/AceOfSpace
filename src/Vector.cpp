// Vector.cpp

// STL Includes
#define _USE_MATH_DEFINES
#include <math.h>
// AOS Includes
#include "Vector.hpp"

const Vector Vector::Zero = Vector(0.0f, 0.0f);
const Vector Vector::One = Vector(1.0f, 1.0f);
const Vector Vector::Up = Vector(0.0f, -1.0f);
const Vector Vector::Down = Vector(0.0f, 1.0f);
const Vector Vector::Left = Vector(-1.0f, 0.0f);
const Vector Vector::Right = Vector(1.0f, 0.0f);

Vector::Vector(float x, float y)
{
  X = x;
  Y = y;
}

void Vector::Normalize()
{
  float length = Length();
  if (length > 0.0f)
  {
    X /= length;
    Y /= length;
  }
}

float Vector::Angle() const
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

float Vector::Length() const
{
  return sqrtf(X * X + Y * Y);
}

Vector Vector::CalculateDirection(float angle)
{
  Vector vector;
  vector.X = sinf(angle);
  vector.Y = cosf(angle);

  return vector;
}

Vector Vector::LinearInterp(const Vector& v1, const Vector& v2, const float& weight)
{
  if (weight <= 0.0f)
  {
    return v1;
  }

  if (weight >= 1.0f)
  {
    return v2;
  }

  Vector vector;
  vector.X = v1.X * (1.0f - weight) + v2.X * weight;
  vector.Y = v1.Y * (1.0f - weight) + v2.Y * weight;

  return vector;
}

Vector Vector::operator+(const Vector& v) const
{
  Vector vector;
  vector.X = X + v.X;
  vector.Y = Y + v.Y;

  return vector;
}

Vector Vector::operator-(const Vector& v) const
{
  Vector vector;
  vector.X = X - v.X;
  vector.Y = Y - v.Y;

  return vector;
}

Vector Vector::operator*(int mag) const
{
  Vector vector;
  vector.X = X * static_cast<float>(mag);
  vector.Y = Y * static_cast<float>(mag);

  return vector;
}

Vector Vector::operator*(float mag) const
{
  Vector vector;
  vector.X = X * mag;
  vector.Y = Y * mag;

  return vector;
}

Vector Vector::operator/(int mag) const
{
  Vector vector;
  vector.X = X / static_cast<float>(mag);
  vector.Y = Y / static_cast<float>(mag);

  return vector;
}

Vector Vector::operator/(float mag) const
{
  Vector vector;
  vector.X = X / mag;
  vector.Y = Y / mag;

  return vector;
}

void Vector::operator=(const Vector& v)
{
  X = v.X;
  Y = v.Y;
}

void Vector::operator+=(const Vector& v)
{
  X += v.X;
  Y += v.Y;
}

void Vector::operator-=(const Vector& v)
{
  X -= v.X;
  Y -= v.Y;
}

Vector operator*(int mag, const Vector& v)
{
  Vector vector;
  vector.X = v.X * static_cast<float>(mag);
  vector.Y = v.Y * static_cast<float>(mag);

  return vector;
}

Vector operator*(float mag, const Vector& v)
{
  Vector vector;
  vector.X = v.X * mag;
  vector.Y = v.Y * mag;

  return vector;
}
