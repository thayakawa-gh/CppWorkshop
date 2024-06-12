#include <vector>
#include <iostream>
#include <format>

class Basetrack
{
public:
	// メンバ変数
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

std::string FormatBasetrack(const Basetrack& bt)
{
	return std::format("{:0>3} {:>10} {:>6} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
		bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y);
}

int main()
{
	// Basetrackの初期化
	Basetrack bt1;
	bt1.pl = 25;
	bt1.rawid = 12345;
	bt1.ph = 220142;
	bt1.ax = 0.2446;
	bt1.ay = -1.5907;
	bt1.x = 12605.2;
	bt1.y = 190451.0;
	bt1.z = 0.0;

	std::cout << FormatBasetrack(bt1);

	// 初期化リストを使って初期化
	Basetrack bt2{ 103, 67890, 290301, -0.3567, -2.2021, 1194581.8, 60312.7, 0.0 };
	std::cout << FormatBasetrack(bt2);

	// vectorにBasetrackを格納
	std::vector<Basetrack> btlist;
	btlist.push_back(bt1);
	btlist.push_back(bt2);
	for (int i = 0; i < btlist.size(); ++i)
	{
		std::cout << FormatBasetrack(btlist[i]);
	}
}

/* 問題
 1. pos、rawid、ph、ax、ayをメンバ変数として持つMicrotrack型を作ってみましょう。
 2. クラスはメンバ変数としてクラス型を持つこともできます。Basetrackクラス型に、Microtrack型のメンバ変数2個を追加してみましょう。
*/