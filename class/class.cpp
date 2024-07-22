#include <vector>
#include <iostream>
#include <format>

/*
 クラスとは、ややかみ砕きすぎた言い方ですが、色々な変数を一纏めにして、新しい型にしたものです。
 例えばBasetrackの情報を扱うとき、PL番号、ID、PH、角度、座標など様々な変数が必要になります。
 これらを全て個別に扱うのはとても面倒です。
 しかし、Basetrackクラスを作ってしまえば、これらの変数をBasetrack型の変数として一括管理できます。

 実は、これまでの勉強会で使ったstd::vectorやstd::stringもクラスです。
 C言語では非常にややこしかった配列の扱いを、クラスの中に押し込め包み隠すことで使いやすくしたものです。
*/
class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

// 引数として一括で受け取ることもできます。
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
		// 各要素へはbtlist[i].plのようにアクセスできます。
		std::cout << FormatBasetrack(btlist[i]);
	}
}

/* 問題
 1. pos、rawid、ph、ax、ayをメンバ変数として持つMicrotrack型を作ってみましょう。
 2. クラスはメンバ変数としてクラス型を持つこともできます。
    Basetrackクラス型に、Microtrack型のメンバ変数2個を追加してみましょう。
	その後、値を代入してstd::formatで表示し、意図したように動作しているか試してみてください。
*/