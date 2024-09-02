#include <iostream>
#include <cmath>

class Basetrack
{
public:

	double GetAng() const { return std::sqrt(ax * ax + ay * ay); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};
class BasetrackPair
{
public:
	// Basetrack2本分の情報をヒープに確保して保有するクラス。
	// new/deleteをコンストラクタ、デストラクタで呼び出しています。

	BasetrackPair() : ptr{ nullptr, nullptr } {}
	BasetrackPair(const Basetrack& bt1, const Basetrack& bt2)
	{
		ptr[0] = new Basetrack(bt1);
		ptr[1] = new Basetrack(bt2);
	}
	~BasetrackPair()
	{
		delete ptr[0];
		delete ptr[1];
	}
	BasetrackPair(const BasetrackPair& other)
	{
		// Basetrackの情報を複製する場合。
		ptr[0] = new Basetrack(*other.ptr[0]);
		ptr[1] = new Basetrack(*other.ptr[1]);
	}
	// コピー代入演算子。
	BasetrackPair& operator=(const BasetrackPair& other)
	{
		// thisは自分自身を指すポインタ。
		// もしotherが自分自身であった場合、Basetrackを作り直すのは良くないので、その場合は何もせずに自分自身を返す。
		if (this == &other) return *this;

		// ptr[0]とptr[1]に入っているBasetrackの情報を削除する。これをしないとメモリリークするかもしれない。
		delete ptr[0];
		delete ptr[1];
		// その後、otherのBasetrackの情報をコピーする。
		ptr[0] = new Basetrack(*other.ptr[0]);
		ptr[1] = new Basetrack(*other.ptr[1]);

		// 最後に自分自身を返す。
		return *this;
	}

	Basetrack* ptr[2];
};