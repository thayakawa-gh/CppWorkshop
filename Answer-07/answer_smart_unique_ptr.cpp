#include <memory>
#include <iostream>
#include <fstream>
#include <format>


class Basetrack
{
public:

	Basetrack()
	{}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}
	~Basetrack()
	{}

	double GetAng() const { return std::sqrt(ax * ax + ay * ay); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};
class BasetrackPair
{
public:

	BasetrackPair(const Basetrack& bt1, const Basetrack& bt2)
	{
		ptr[0] = std::make_unique<Basetrack>(bt1);
		ptr[1] = std::make_unique<Basetrack>(bt2);
	}
	~BasetrackPair() = default;
	BasetrackPair(const BasetrackPair& other)
	{
		// Basetrackの情報を複製する場合。
		ptr[0] = std::make_unique<Basetrack>(*other.ptr[0]);
		ptr[1] = std::make_unique<Basetrack>(*other.ptr[1]);
	}
	// コピー代入演算子。
	BasetrackPair& operator=(const BasetrackPair& other)
	{
		// thisは自分自身を指すポインタ。
		// もしotherが自分自身であった場合、今回は生のポインタを使った場合と異なりバグにはなりませんが、
		// Basetrackを作り直すのはヒープの再確保が発生して非効率なので、ここでreturnしたほうがよいでしょう。
		if (this == &other) return *this;

		ptr[0] = std::make_unique<Basetrack>(*other.ptr[0]);
		ptr[1] = std::make_unique<Basetrack>(*other.ptr[1]);

		// 最後に自分自身を返す。
		return *this;
	}

	std::unique_ptr<Basetrack> ptr[2];
};

int main()
{
	Basetrack bt1(26, 67890, 200085, 0.2541, -1.6531, 12316.2, 191893.3, 10802.3);
	Basetrack bt2(27, 67891, 200086, 0.2542, -1.6532, 12316.3, 191893.4, 10802.4);

	BasetrackPair btp1(bt1, bt2);
	BasetrackPair btp2(btp1);

	std::cout << std::format("{:>3} {:>11} {:>3} {:>11}\n", btp1.ptr[0]->pl, btp1.ptr[0]->rawid, btp1.ptr[1]->pl, btp1.ptr[1]->rawid);
	std::cout << std::format("{:>3} {:>11} {:>3} {:>11}\n", btp2.ptr[0]->pl, btp2.ptr[0]->rawid, btp2.ptr[1]->pl, btp2.ptr[1]->rawid);
	if (btp1.ptr[0] == btp2.ptr[0])
	{
		std::cout << "btp1.ptr[0] and btp2.ptr[0] are the same object\n";
	}
	else
	{
		std::cout << "btp1.ptr[0] and btp2.ptr[0] are different objects\n";
	}
	if (btp1.ptr[1] == btp2.ptr[1])
	{
		std::cout << "btp1.ptr[1] and btp2.ptr[1] are the same object\n";
	}
	else
	{
		std::cout << "btp1.ptr[1] and btp2.ptr[1] are different objects\n";
	}
}