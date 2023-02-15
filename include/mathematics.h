#pragma once

#include <math.h>

namespace dragonbyte_engine
{

	class Vec3
	{
	public:
	
		Vec3() : x{0}, y{0}, z{0} {}
		Vec3(double x, double y, double z) : x{x}, y{y}, z{z} {}
		double x, y, z;
		
		static float distance(Vec3 a, Vec3 b)
		{
			return static_cast<float>(sqrt(a.x * b.x + a.y * b.y + a.z * b.z));
		}
		
		Vec3 operator+(const Vec3& a_krOther)
		{
			return { x + a_krOther.x, y + a_krOther.y, z + a_krOther.z };
		}
		Vec3 operator+=(const Vec3& a_krOther)
		{
			return *this + a_krOther;
		}
		Vec3 operator-(const Vec3& a_krOther)
		{
			return { x - a_krOther.x, y - a_krOther.y, z - a_krOther.z };
		}
		Vec3 operator-=(const Vec3& a_krOther)
		{
			return *this - a_krOther;
		}
		Vec3 operator*(const float scalar)
		{
			return { x * scalar, y * scalar, z * scalar };
		}
		Vec3 operator+=(const float scalar)
		{
			return *this * scalar;
		}
		Vec3 operator/(const float scalar)
		{
			return { x / scalar, y / scalar, z / scalar };
		}
		Vec3 operator/=(const float scalar)
		{
			return *this / scalar;
		}
	};

	class Quaternion
	{
	public:

		Quaternion();
		Quaternion(float x, float y, float z);
		Quaternion(float i, float j, float k, float w);
		
		Quaternion operator+(const Quaternion& a_krOther)
		{
			return {};
		}
		Quaternion operator+=(const Quaternion& a_krOther)
		{
			return *this + a_krOther;
		}
	};

} // namespace dragonbyte_engine