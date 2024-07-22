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
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)//mtを明示的に初期化しない場合、自動的にMicrotrackのデフォルトコンストラクタが呼ばれます。
	{
		std::cout << "basetrack default constructor" << std::endl;
	}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)//mtを明示的に初期化しない場合、自動的にMicrotrackのデフォルトコンストラクタが呼ばれます。
	{
		std::cout << "basetrack constructor 1" << std::endl;
	}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_,
		int pos_m1_, int64_t rawid_m1_, int ph_m1_, double ax_m1_, double ay_m1_,
		int pos_m2_, int64_t rawid_m2_, int ph_m2_, double ax_m2_, double ay_m2_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_),
		mt{ { pos_m1_, rawid_m1_, ph_m1_, ax_m1_, ay_m1_ }, { pos_m2_, rawid_m2_, ph_m2_, ax_m2_, ay_m2_ } }
	{
		std::cout << "basetrack constructor 2" << std::endl;
	}

	Basetrack(const Basetrack& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z),
		mt{ bt.mt[0], bt.mt[1] }
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
		mt[0] = bt.mt[0];
		mt[1] = bt.mt[1];
		return *this;
	}

	// ムーブコンストラクタとムーブ代入演算子は概念がややこしいため、今回は省略します。
	// ムーブセマンティクスの回が来たらその時に。

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
	Microtrack mt[2];
};

/*
 #####コンストラクタとデストラクタ#####
 コンストラクタはクラスのインスタンスが生成されるときに呼ばれる特殊な関数で、インスタンスの初期化を担うものです。
 デストラクタはその逆で、インスタンスを処分するときに呼ばれ、インスタンスの中身の後始末を行います。
 注) インスタンスとは、何らかのクラスや変数型の実体のこと。Basetrack bt;のように宣言したとき、"bt"はBasetrackクラスのインスタンス。

 コンストラクタにもいくつか種類があります。

 * デフォルトコンストラクタ
 引数を持たないコンストラクタのことで、引数なしでインスタンスを生成するときに呼ばれます。
 例えばBasetrack bt;のように書くと、btはBasetrackクラスのデフォルトコンストラクタによって初期化されます。

 * デストラクタ
 インスタンスが破棄されるときに呼ばれる関数で、インスタンスの後始末を担っています。
 Basetrack bt;のように宣言されたインスタンスは、定義されたスコープ（関数や{}で括られた範囲）を抜けるときに破棄され、デストラクタが呼ばれます。

 * 引数ありコンストラクタ
 何らかの引数を取り、それらからインスタンスを初期化するコンストラクタを指します。C++の正式な用語ではありません。
 Basetrack bt(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);のように書くと、引数ありのコンストラクタが呼ばれます。

 * コピーコンストラクタ
 自身と同じクラスのインスタンスを引数に取るコンストラクタで、インスタンスのコピーを生成するときに使います。
 Basetrack bt;が既にあるとして、
 Basetrack bt2(bt);のようにすると、bt2はBasetrackクラスのコピーコンストラクタによって初期化されます。
 Basetrack bt2 = bt;と書いても同じです。

 * コピー代入演算子
 コンストラクタではありませんが、似た働きをします。
 代入演算子は既に初期化されたインスタンスに新たなインスタンスを再代入するときに呼ばれます。
 Basetrack bt, bt2;が既にあるとして、bt = bt2;のようにすると、btにbt2の値がコピーされます。


 基本的にコンストラクタ、デストラクタ、代入演算子の中にはどのような処理を書いても構いません。プログラマーの裁量次第です。
 尤も、初期化や破棄の役割を逸脱する処理を書くのは止めておきましょう。プログラムが分かりにくくなりますし、バグの温床になります。

 引数ありのコンストラクタ以外は、コンパイラの自動生成を頼っても構いません。
 コピーコンストラクタやコピー代入演算子が未定義の場合、
 コンパイラは自動的に"全メンバ変数をコピーする"だけのコピーコンストラクタ/代入演算子を生成します。
 デストラクタも同様に、"全メンバ変数のデストラクタを呼ぶ"だけのデストラクタを生成します。
 class.cppのBasetrackクラスは、この自動生成によってデフォルトコンストラクタ、コピーコンストラクタ、コピー代入演算子、デストラクタが生成されています。
*/
int main()
{
	if (false)
	{
		// bt1を初期化。デフォルトコンストラクタが呼ばれます。
		Basetrack bt1;
		// デフォルトコンストラクタで初期化されたため、全てのメンバ変数は0になっています。
		std::cout << std::format("x: {}, y: {}, z: {}\n", bt1.x, bt1.y, bt1.z);
		// if、for、関数などのスコープ{}を抜けるとき、デストラクタが呼ばれます。
	}

	if (false)
	{
		// bt2を初期化。引数ありのコンストラクタが呼ばれます。
		Basetrack bt2(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);
		// 引数ありのコンストラクタで初期化されたため、引数の値が代入されています。
		std::cout << std::format("x: {}, y: {}, z: {}\n", bt2.x, bt2.y, bt2.z);
	}

	if (true)
	{
		// bt3の初期化。引数ありのコンストラクタが呼ばれます。
		Basetrack bt3{ 30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0,
					  251, 123456, 130077, -0.1571, 2.5793,
					  252, 123456, 120051, -0.1322, 2.8038 };

		std::cout << "----------------" << std::endl;

		// bt2の初期化。コピーコンストラクタによってbt1の値がコピーされます。
		Basetrack bt4(bt3);

		std::cout << "----------------" << std::endl;

		// bt3にbt2の値を代入。代入演算子が呼ばれます。
		bt4 = bt3;
	}

	std::cout << "----------------" << std::endl;

	return 0;
}

/* 問題
 1. Basetrackクラスにradial angleを格納しておくためのdouble型変数を追加し、
    コンストラクタの引数ax、ayからradial angleを計算して初期化するようコンストラクタを修正してみましょう。
	なお、radial angleは一般的にsqrt(ax * ax + ay * ay)で計算できます。
*/