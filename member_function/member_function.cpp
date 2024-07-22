#include <format>
#include <iostream>

class Basetrack
{
public:
	/*
	 = defaultとすると、コンパイラが各種コンストラクタや代入演算子を自動生成します。
	 デフォルト/コピーコンストラクタ、デストラクタ、コピー代入演算子はdefault指定することができます。
	 ただし、デフォルトコンストラクタは全メンバ変数をデフォルト値で初期化するのみ、
	 コピーコンストラクタ/代入演算子は全メンバ変数をコピーするのみ、と、極めて単純な挙動になるので、
	 複雑な処理をしたい場合は自分で定義しましょう。
	*/
	Basetrack() = default;
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}
	Basetrack(const Basetrack& bt) = default;
	Basetrack& operator=(const Basetrack& bt) = default;
	~Basetrack() = default;

	// メンバ関数の定義
	double GetRadAng() const //<-- constは「メンバ変数を変更しない」という意味
	{
		// std::sqrtは平方根を計算する関数
		return std::sqrt(ax * ax + ay * ay);
	}

	int GetPH() const
	{
		return ph / 10000;
	}
	int GetVPH() const
	{
		return ph % 10000;
	}

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

/*
 #### メンバ関数
 クラスの面白いところは、クラスそれ自体に関数を持たせられる、ということです。
 例えば、Basettrackクラスの変数btがあるとしましょう。

 Basetrack bt;

 この変数btはidやax、ayなどの変数を持っていますが、radial angleは持っていません。
 constrcutorで問題に出したように、メンバ変数として予め持たせてしまうのも手ですが、
 追加した変数分だけ余計にメモリを消費しますし、不必要なときでも無意味に計算してしまいます。
 かといって、例えばbtからradial angleを計算したい場合、
 double rad = std::sqrt(bt.ax * bt.ax + bt.ay * bt.ay);
 なんて毎回書くのはちょっと面倒です。書き間違えて致命的なバグを生むかもしれません。
 これを解決する良い方法があります。それがメンバ関数です。

 メンバ関数は、クラス内で定義された関数で、クラスの変数にアクセスすることができます。
 つまり、BasetrackクラスにGetRadAng()という関数を追加して、radial angleを計算する処理を関数にまとめてしまうことができます。
 double rad = bt.GetRadAng();

*/

int main()
{
	// bt1を初期化。引数ありのコンストラクタが呼ばれる。
	Basetrack bt1(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	bt1.SetAngle(bt1.ax * 0.951, bt1.ay * 0.951);

	std::cout << std::format("Radial angle: {}\n", bt1.GetRadAng());
	std::cout << std::format("PH: {}\n", bt1.GetPH());
	std::cout << std::format("VPH: {}\n", bt1.GetVPH());
}

/* 問題
 Lecture-02a、02bで作成したMicrotrack情報を持つBasetrackクラスの中に、
 basetrack-microtrack間のax、ayそれぞれの角度差を計算して返す関数を追加してみましょう。
 もし可能なら、radial、lateral角度差も実装してみましょう。
 Microtrackは2本あるので、どちらとの角度差を取得するかを引数指定できたりするとなお良いですね。

 ちなみに、radial、lateralの角度差の定義は以下の通りです。
 ax、ayはBasetrackの、max、mayはMicrotrackの角度とします。
 denom = std::sqrt(ax * ax + ay * ay);
 radial    :((max - ax) * ax + (may - ay) * ay) / denom;
 lateral   :((max - ax) * ay - (may - ay) * ax) / denom;
*/