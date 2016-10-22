// Vector.h //
#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
	public:
		Vector(float x = 0.0f, float y = 0.0f);

		float X;
		float Y;

		void Normalize();
		float Angle();
		float Length();
		static Vector CalculateDirection(float angle);
		static Vector LinearInterp(const Vector& v1, const Vector& v2, const float& weight);

		Vector operator +(const Vector& v);
		Vector operator -(const Vector& v);
		Vector operator *(const float& mag);
		Vector operator /(const float& mag);

		void operator =(const Vector& v);
		void operator +=(const Vector& v);
		void operator -=(const Vector& v);

};

Vector operator *(const float& mag, const Vector& v);

#endif
