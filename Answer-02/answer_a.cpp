#include <vector>
#include <iostream>
#include <format>

class Microtrack
{
public:
	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
};

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
	Microtrack mt[2];
};

int main()
{
	Basetrack bt1;
	bt1.pl = 25;
	bt1.rawid = 12345;
	bt1.ph = 220142;
	bt1.ax = 0.2446;
	bt1.ay = -1.5907;
	bt1.x = 12605.2;
	bt1.y = 190451.0;
	bt1.z = 0.0;
	bt1.mt[0] = { 251, 123456, 110070, 0.2471, -1.5793 };
	bt1.mt[1] = { 252, 123456, 110072, 0.2582, -1.6038 };

	Basetrack bt2{ 25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0,
		{ { 251, 123456, 110070, 0.2471, -1.5793 }, { 252, 123456, 110072, 0.2582, -1.6038 } }
	};
}