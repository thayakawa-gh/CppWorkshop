#include <format>
#include <iostream>

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
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), arad(0.0), x(0.0), y(0.0), z(0.0)
	{
	}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), arad(sqrt(ax_* ax_ + ay_ * ay_)), x(x_), y(y_), z(z_)
	{
	}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_,
		int pos_m1_, int64_t rawid_m1_, int ph_m1_, double ax_m1_, double ay_m1_,
		int pos_m2_, int64_t rawid_m2_, int ph_m2_, double ax_m2_, double ay_m2_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), arad(sqrt(ax_* ax_ + ay_ * ay_)), x(x_), y(y_), z(z_),
		mt{ { pos_m1_, rawid_m1_, ph_m1_, ax_m1_, ay_m1_ }, { pos_m2_, rawid_m2_, ph_m2_, ax_m2_, ay_m2_ } }
	{
	}

	Basetrack(const Basetrack& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z),
		mt{ bt.mt[0], bt.mt[1] }
	{
	}
	~Basetrack()
	{
	}
	Basetrack& operator=(const Basetrack& bt)
	{
		pl = bt.pl;
		rawid = bt.rawid;
		ph = bt.ph;
		ax = bt.ax;
		ay = bt.ay;
		x = bt.x;
		y = bt.y;
		z = bt.z;
		mt[0] = bt.mt[0];
		mt[1] = bt.mt[1];
		return *this;
	}

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double arad;// 新たに追加したradial angleを格納する変数。
	double x, y, z;
	Microtrack mt[2];
};


int main__()
{
	Basetrack bt1(25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0,
		251, 123456, 110070, 0.2471, -1.5793,
		252, 123456, 110072, 0.2582, -1.6038);
	// aradは、コンストラクタの引数に直接は与えていませんが、コンストラクタ内でaxとayから計算、初期化されています。
	std::cout << std::format("bt.arad: {:>7.4f}\n", bt1.arad);
}