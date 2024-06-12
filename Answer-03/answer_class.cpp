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

std::string FormatMicrotrack(const Microtrack& mt)
{
	return std::format("    {:0>4} {:>10} {:>6} {:>7.4f} {:>7.4f}\n",
		mt.pos, mt.rawid, mt.ph, mt.ax, mt.ay);
}
std::string FormatBasetrack(const Basetrack& bt)
{
	return std::format("{:0>3} {:>10} {:>6} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
		bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y) + 
		FormatMicrotrack(bt.mt[0]) + FormatMicrotrack(bt.mt[1]);
}

int main_()
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
	std::cout << FormatBasetrack(bt1);

	Basetrack bt2{ 25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0,
		{ { 251, 123456, 110070, 0.2471, -1.5793 }, { 252, 123456, 110072, 0.2582, -1.6038 } }
	};
	std::cout << FormatBasetrack(bt2);

	return 0;
}