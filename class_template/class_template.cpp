#include <iostream>
#include <vector>
#include <format>

template <class T>
class Vector3D
{
public:
	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

	T norm() const { return std::sqrt(x * x + y * y + z * z); }
	T dot(const Vector3D& v) const { return x * v.x + y * v.y + z * v.z; }
	Vector3D cross(const Vector3D& v) const
	{
		return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	Vector3D add(const Vector3D& v) const
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}
	Vector3D sub(const Vector3D& v) const
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	T x, y, z;
};


int main()
{

}

/*
 問題
 1. 


*/