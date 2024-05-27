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
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)//mtを明示的に初期化しない場合、勝手にMicrotrackのデフォルトコンストラクタが呼ばれる。
	{
		std::cout << "basetrack default constructor" << std::endl;
	}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)//mtを明示的に初期化しない場合、勝手にMicrotrackのデフォルトコンストラクタが呼ばれる。
	{
		std::cout << "basetrack constructor" << std::endl;
	}
	/*Basetrack(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z,
		int pos_m1, int64_t rawid_m1, int ph_m1, double ax_m1, double ay_m1,
		int pos_m2, int64_t rawid_m2, int ph_m2, double ax_m2, double ay_m2)
		: pl(pl), rawid(rawid), ph(ph), ax(ax), ay(ay), x(x), y(y), z(z),
		mt{ { pos_m1, rawid_m1, ph_m1, ax_m1, ay_m1 }, { pos_m2, rawid_m2, ph_m2, ax_m2, ay_m2 } }
	{
		std::cout << "basetrack constructor" << std::endl;
	}*/

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

	// ムーブコンストラクタとムーブ代入演算子は概念がややこしいため、今回は省略する。
	// ムーブセマンティクスの回が来たらその時に。

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
	//Microtrack mt[2];
};

int main()
{
	// bt1を初期化。デフォルトコンストラクタが呼ばれる。
	Basetrack bt1;

	// bt1を初期化。引数ありのコンストラクタが呼ばれる。
	Basetrack bt2(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	// bt2を初期化。コピーコンストラクタによってbt1の値がコピーされる。
	Basetrack bt3(bt2);

	// main関数を抜けるとき、用済みとなったbt1, bt2のデストラクタが呼ばれる。
}