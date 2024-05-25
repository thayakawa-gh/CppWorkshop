#include <format>
#include <iostream>

class Basetrack
{
public:
	Basetrack()
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)
	{
		std::cout << "default constructor" << std::endl;
	}
	Basetrack(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z)
		: pl(pl), rawid(rawid), ph(ph), ax(ax), ay(ay), x(x), y(y), z(z)
	{
		std::cout << "constructor" << std::endl;
	}

	Basetrack(const Basetrack& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z)
	{
		std::cout << "copy constructor" << std::endl;
	}
	~Basetrack()
	{
		std::cout << "destructor" << std::endl;
	}
	Basetrack& operator=(const Basetrack& bt)
	{
		std::cout << "assignment operator" << std::endl;
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
};

int main()
{
	// bt1を初期化。引数ありのコンストラクタが呼ばれる。
	Basetrack bt1(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	// bt2を初期化。コピーコンストラクタによってbt1の値がコピーされる。
	Basetrack bt2(bt1);

	// main関数を抜けるとき、用済みとなったbt1, bt2のデストラクタが呼ばれる。
}