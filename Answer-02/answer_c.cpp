#include <vector>
#include <iostream>
#include <format>
#include <cassert>
#include <array>

class Microtrack
{
public:
	Microtrack()
		: pos(0), rawid(0), ph(0), ax(0.0), ay(0.0)
	{
		std::cout << "microtrack default constructor" << std::endl;
	}
	Microtrack(int pos, int64_t rawid, int ph, double ax, double ay)
		: pos(pos), rawid(rawid), ph(ph), ax(ax), ay(ay)
	{
		std::cout << "microtrack constructor" << std::endl;
	}
	Microtrack(const Microtrack& mt)
		: pos(mt.pos), rawid(mt.rawid), ph(mt.ph), ax(mt.ax), ay(mt.ay)
	{
		std::cout << "microtrack copy constructor" << std::endl;
	}
	~Microtrack()
	{
		std::cout << "microtrack destructor" << std::endl;
	}
	Microtrack& operator=(const Microtrack& mt)
	{
		std::cout << "microtrack assignment operator" << std::endl;
		pos = mt.pos;
		rawid = mt.rawid;
		ph = mt.ph;
		ax = mt.ax;
		ay = mt.ay;
		return *this;
	}

	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
};

class Basetrack
{
public:
	Basetrack()
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)
	{
		std::cout << "basetrack default constructor" << std::endl;
	}
	Basetrack(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z)
		: pl(pl), rawid(rawid), ph(ph), ax(ax), ay(ay), x(x), y(y), z(z)
	{
		std::cout << "basetrack constructor" << std::endl;
	}

	Basetrack(const Basetrack& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z)
	{
		std::cout << "basetrack copy constructor" << std::endl;
	}
	~Basetrack()
	{
		std::cout << "basetrack destructor" << std::endl;
	}
	Basetrack& operator=(const Basetrack& bt)
	{
		std::cout << "basetrack assignment operator" << std::endl;
		pl = bt.pl;
		rawid = bt.rawid;
		ph = bt.ph;
		ax = bt.ax;
		ay = bt.ay;
		x = bt.x;
		y = bt.y;
		z = bt.z;
		return *this;
	}

	//pos‚Í0‚©1‚ð—^‚¦‚éB
	double GetDax(int pos) const { return mt[pos].ax - ax; }
	double GetDay(int pos) const { return mt[pos].ay - ay; }

	double GetDar(int pos) const
	{
		double denom = std::sqrt(ax * ax + ay * ay);
		return ((mt[pos].ax - ax) * ax + (mt[pos].ay - ay) * ay) / denom;
	}
	double GetDal(int pos) const
	{
		double denom = std::sqrt(ax * ax + ay * ay);
		return ((mt[pos].ax - ax) * ay - (mt[pos].ay - ay) * ax) / denom;
	}

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