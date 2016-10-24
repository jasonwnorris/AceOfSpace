// Vector.cpp //
#include "Vector.hpp"

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

Vector::Vector(float x, float y)
{
  X = x;
  Y = y;
}

// trims vector down to a unit vector
void Vector::Normalize()
{
  float length = Length();
  if (length <= 0)
    return;

  X /= length;
  Y /= length;
}

// finds the angle of a given vector (radians)
float Vector::Angle()
{
  if (X == 0.0f)
    if (Y > 0.0f)
      return M_PI / 2.0f;
    else
      return 3.0f * M_PI / 2.0f;

  float omega = Y / X;

  if (omega < 0.0f)
    omega *= -1;

  float angle = atan(omega);

  if (X < 0.0f && Y >= 0.0f)
    return M_PI - angle;

  if (X < 0.0f && Y <= 0.0f)
    return M_PI + angle;

  if (X > 0.0f && Y <= 0.0f)
    return 2.0f * M_PI - angle;

  return angle;
}

// find magnitude
float Vector::Length()
{
  return sqrt(X * X + Y * Y);
}

// find a vector of the given angle
Vector Vector::CalculateDirection(float angle)
{
  Vector vector;
  vector.X = sin(angle);
  vector.Y = cos(angle);

  return vector;
}

// was ganna use this to make the enemies dodge around you
// didn't get around to it
Vector Vector::LinearInterp(const Vector& v1, const Vector& v2, const float& weight)
{
  Vector vector;

  if (weight < 0 || weight > 1)
    return vector;

  vector.X = v1.X * (1.0f - weight) + v2.X * weight;
  vector.Y = v1.Y * (1.0f - weight) + v2.Y * weight;

  return vector;
}

Vector Vector::operator +(const Vector& v)
{
  Vector vector;
  vector.X = X + v.X;
  vector.Y = Y + v.Y;

  return vector;
}

Vector Vector::operator -(const Vector& v)
{
  Vector vector;
  vector.X = X - v.X;
  vector.Y = Y - v.Y;

  return vector;
}

Vector Vector::operator *(const float& mag)
{
  Vector vector;
  vector.X = X * mag;
  vector.Y = Y * mag;

  return vector;
}

Vector Vector::operator /(const float& mag)
{
  Vector vector;
  vector.X = X / mag;
  vector.Y = Y / mag;

  return vector;
}

void Vector::operator =(const Vector& v)
{
  X = v.X;
  Y = v.Y;
}

void Vector::operator +=(const Vector& v)
{
  X += v.X;
  Y += v.Y;
}

void Vector::operator -=(const Vector& v)
{
  X -= v.X;
  Y -= v.Y;
}

// ex: Vector(5, 2) * 2.5f
Vector operator *(const float& mag, const Vector& v)
{
  Vector vector;
  vector.X = v.X * mag;
  vector.Y = v.Y * mag;

  return vector;
}
