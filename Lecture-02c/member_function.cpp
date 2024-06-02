#include <format>
#include <iostream>

class Basetrack
{
public:
	Basetrack() = default; //defaultとすると、コンパイラがデフォルトコンストラクタを自動生成する。
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}

	double GetRadialAngle() const //<-- constは「メンバ変数を変更しない」という意味
	{
		return std::sqrt(ax * ax + ay * ay);
		//return std::hypot(ax, ay);でもよい。
	}

	// 宣言と定義を分けたい場合。
	int GetPH() const;
	int GetVPH() const;

	void SetAngle(double ax_, double ay_) //<-- メンバ変数を変更するのでconstはつけない
	{
		ax = ax_;
		ay = ay_;
	}

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

// クラス定義内では宣言のみにして、定義をクラススコープの外側に書くこともできる。
// コンストラクタも同様。

int Basetrack::GetPH() const
{
	return (int)(ph / 10000);
}
int Basetrack::GetVPH() const
{
	return (int)(ph % 10000);
}

int main()
{
	// bt1を初期化。引数ありのコンストラクタが呼ばれる。
	Basetrack bt1(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	bt1.SetAngle(bt1.ax * 0.951, bt1.ay * 0.951);

	std::cout << std::format("Radial angle: {}\n", bt1.GetRadialAngle());
	std::cout << std::format("PH: {}\n", bt1.GetPH());
	std::cout << std::format("VPH: {}\n", bt1.GetVPH());
}

/* 問題
 Lecture-02a、02bで作成したMicrotrack情報を持つBasetrackクラスの中に、base-micro角度差を計算して返す関数を追加してみましょう。
 axとay、可能ならradial、lateralそれぞれを。
*/