#include <vector>
#include <iostream>
#include <format>
#include <cassert>
#include <array>

class Microtrack_c
{
public:
	Microtrack_c()
		: pos(0), rawid(0), ph(0), ax(0.0), ay(0.0)
	{}
	Microtrack_c(int pos, int64_t rawid, int ph, double ax, double ay)
		: pos(pos), rawid(rawid), ph(ph), ax(ax), ay(ay)
	{}
	Microtrack_c(const Microtrack_c& mt)
		: pos(mt.pos), rawid(mt.rawid), ph(mt.ph), ax(mt.ax), ay(mt.ay)
	{}
	~Microtrack_c()
	{}
	Microtrack_c& operator=(const Microtrack_c& mt)
	{
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

class Basetrack_c
{
public:
	Basetrack_c()
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)
	{}
	Basetrack_c(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z)
		: pl(pl), rawid(rawid), ph(ph), ax(ax), ay(ay), x(x), y(y), z(z)
	{}
	Basetrack_c(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z,
		int pos_m1, int64_t rawid_m1, int ph_m1, double ax_m1, double ay_m1,
		int pos_m2, int64_t rawid_m2, int ph_m2, double ax_m2, double ay_m2)
		: pl(pl), rawid(rawid), ph(ph), ax(ax), ay(ay), x(x), y(y), z(z),
		mt{ { pos_m1, rawid_m1, ph_m1, ax_m1, ay_m1 }, { pos_m2, rawid_m2, ph_m2, ax_m2, ay_m2 } }
	{}

	Basetrack_c(const Basetrack_c& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z)
	{}
	~Basetrack_c()
	{}
	Basetrack_c& operator=(const Basetrack_c& bt)
	{
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

	//posは0か1を与える。
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
	Microtrack_c mt[2];
};

int main()
{
	Basetrack_c bt1;
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

	std::cout << std::format("dax0 = {:>7.4f}, day0 = {:>7.4f}, dar0 = {:>7.4f}, dal0 = {:>7.4f}\n", bt1.GetDax(0), bt1.GetDay(0), bt1.GetDar(0), bt1.GetDal(0));
	std::cout << std::format("dax1 = {:>7.4f}, day1 = {:>7.4f}, dar1 = {:>7.4f}, dal1 = {:>7.4f}\n", bt1.GetDax(1), bt1.GetDay(1), bt1.GetDar(1), bt1.GetDal(1));

	return 0;
}