#pragma once

#include <math.h>
#include <glm/glm.hpp>

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
			return *this += a_krOther;
		}
		Vec3& operator+=(const Vec3& a_krOther)
		{
			x += a_krOther.x;
			y += a_krOther.y;
			z += a_krOther.z;
			return *this;
		}
		Vec3 operator-(const Vec3& a_krOther)
		{
			return *this -= a_krOther;
		}
		Vec3& operator-=(const Vec3& a_krOther)
		{
			x -= a_krOther.x;
			y -= a_krOther.y;
			z -= a_krOther.z;
			return *this;
		}
		Vec3 operator*(const float scalar)
		{
			return *this *= scalar;
		}
		Vec3& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}
		Vec3 operator/(const float scalar)
		{
			return *this /= scalar;
		}
		Vec3& operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}
		glm::vec3 to_glm()
		{
			return glm::vec3{ x, y, z };
		}
	};

	class Quaternion
	{
	public:

		float i, j, k, w;

		Quaternion() { *this = identity(); }
		Quaternion(float x, float y, float z)
		{
			*this = identity();
			rotate(x, { 1, 0, 0 });
			rotate(y, { 0, 1, 0 });
			rotate(z, { 0, 0, 1 });
		}
		Quaternion(float i, float j, float k, float w) : i{ i }, j{ j }, k{ k }, w{ w } {}
		
		Quaternion operator+(const Quaternion& a_krOther)
		{
			return {  };
		}
		Quaternion operator+=(const Quaternion& a_krOther)
		{
			return *this + a_krOther;
		}

		Vec3 to_euler()
		{

		}
		void rotate(float angle, Vec3 up);
		static Quaternion identity()
		{
			return Quaternion(0, 0, 0, 1);
		}
	};

} // namespace dragonbyte_engine