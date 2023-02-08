#pragma once

namespace dragonbyte_engine
{

	class Vec3
	{
	public:
	
		Vec3(double x, double y, double z) : x{x}, y{y}, z{z} {}
		double x, y, z;
		
		Vec3 operator+(const Vec3& a_krOther)
		{
			return { x + a_krOther.x, y + a_krOther.y, z + a_krOther.z };
		}
		Vec3 operator+=(const Vec3& a_krOther)
		{
			return *this + a_krOther;
		}
	};

	class Vec2
	{

	};

	class Quaternion
	{
	public:
		
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