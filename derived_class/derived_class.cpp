#include <iostream>
#include <format>

class MicrotrackSubset
{
public:
	MicrotrackSubset() : ax(0), ay(0), z(0), ph(0), pos(0), col(0), row(0), zone(0), isg(0), rawid(0) {}
	MicrotrackSubset(double ax_, double ay_, double z_, int ph_, int pos_, int col_, int row_, int zone_, int isg_, int64_t rawid_)
		: ax(ax_), ay(ay_), z(z_), ph(ph_), pos(pos_), col(col_), row(row_), zone(zone_), isg(isg_), rawid(rawid_)
	{}

	double ax, ay;
	double z;
	int ph;
	int pos, col, row, zone, isg;
	int64_t rawid;
};

class BasetrackSubset
{
public:
	BasetrackSubset(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}

	int GetPH() const { return int(ph / 10000); }
	int GetVol() const { return int(ph % 10000); }

	double GetRadAng() const { return std::sqrt(ax * ax + ay * ay); }
	double GetLatAng() const { return std::atan2(ay, ax); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};

class BasetrackFull : public BasetrackSubset
{
public:

	BasetrackFull(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_, int isg_, int zone_)
		: BasetrackSubset(pl_, rawid_, ph_, ax_, ay_, x_, y_, z_), isg(isg_), zone(zone_)
	{}

	const MicrotrackSubset& GetMicrotrack(int i) const { return mt[i]; }
	MicrotrackSubset& GetMicrotrack(int i) { return mt[i]; }

	double GetDax(int i) const
	{
		// axはBasetrackSubsetのメンバ変数ですが、
		// BasetrackFullはBasetrackSubsetを継承しているので、そのメンバ変数を持っています。
		return ax - GetMicrotrack(i).ax;
	}
	double GetDay(int i) const
	{
		return ay - GetMicrotrack(i).ay;
	}

	int isg, zone;
	MicrotrackSubset mt[2];
};

/*
 ######継承について######
 継承は、あるクラスを元にした新しいクラスを作るための機能です。
 例えば、BasetrackSubsetクラスを継承してBasetrackFullクラスを作っています。
 BasetrackFullクラスはBasetrackSubsetクラスのメンバ変数やメンバ関数を引き継いており、それらを使用することができます。
 さらに新たにisgとzone、そしてMicrotrackSubset型のmtというメンバ変数、GetMicrotrack、GetDax/GetDayというメンバ関数を追加しています。
*/


int main()
{
	BasetrackFull bt(25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0, 0, 0);
	// BasetrackFullクラスはBasetrackSubsetクラスを継承しているので、BasetrackSubsetのメンバ変数やメンバ関数を使うことができます。
	std::cout << std::format("pl = {}, rawid = {}, ra = {}\n", bt.pl, bt.rawid, bt.GetRadAng());
	std::cout << std::format("ph = {}V{}\n", bt.GetPH(), bt.GetVol());
	std::cout << std::format("lat = {}\n", bt.GetLatAng());
	// BasetrackFullクラスで新たに定義したメンバ変数や関数も使えます。
	std::cout << std::format("dax = {}, day = {}\n", bt.GetDax(0), bt.GetDay(0));

	// 当然ですが、BasetrackSubsetクラスはBasetrackFullクラスのメンバ変数やメンバ関数を使うことはできません。
	BasetrackSubset bts(25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0);
	// std::cout << std::format("pl = {}, rawid = {}, ra = {}\n", bts.pl, bts.rawid, bts.GetRadAng());
}