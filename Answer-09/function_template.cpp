#include <iostream>
#include <format>

class Microtrack
{
public:
	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

template <class Track1, class Track2>
bool JudgeConnection(const Track1& t1, const Track2& t2)
{
	if (std::abs(t1.ax - t2.ax) > 0.2) return false;
	if (std::abs(t1.ay - t2.ay) > 0.2) return false;
	double z = (t1.z + t2.z) / 2;
	double x1 = t1.x + (z - t1.z) * t1.ax;
	double x2 = t2.x + (z - t2.z) * t2.ax;
	if (std::abs(x1 - x2) > 200) return false;
	double y1 = t1.y + (z - t1.z) * t1.ay;
	double y2 = t2.y + (z - t2.z) * t2.ay;
	if (std::abs(y1 - y2) > 200) return false;
	return true;
}

int main()
{
	Basetrack bt1{ 12, 12345, 230058, -0.1883, -2.0417, 124743.9, 121878.6, 0.0 };
	Basetrack bt2{ 12, 67890, 200025, -0.1910, -2.0403, 125285.4, 127689.3, -2846.9 };
	Microtrack mt{ 121, 11111, 110021, -0.1910, -2.0403, 125285.4, 127689.3, -2846.9 };
	bool res = JudgeConnection(bt1, bt2);
	std::cout << "base-base:" << res << std::endl;
	res = JudgeConnection(bt1, mt);
	std::cout << "base-micro:" << res << std::endl;
}