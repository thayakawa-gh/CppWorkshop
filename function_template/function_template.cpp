#include <vector>
#include <format>
#include <iostream>

class Microtrack
{
public:
	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

/*
 ######テンプレートについて######
 C++にはテンプレートという強力な機能があります。
 今までstd::vectorやstd::unique_ptrなどのクラスの使い方を勉強する中で、
 std::vector<double>の<...>は一体何なのかと疑問を持った人も多かろうと思います。
 この<...>こそがテンプレートで、あるクラスに対して何らかの型情報などを伝達する役割があります。
 例えば、std::vectorそれ自体は格納するリストの型情報を持ちません。double型なのか、int型なのか、Basetrack型なのかを知らないのです。
 最初はこの型を適当に（関数の引数のように）Tなどと仮置きして	std::vectorを設計しておき、
 std::vector<double>のように指定されたときにはじめてTをdoubleに置換し、double型用std::vectorを生成しているのです。

 テンプレートは極めて強力な機能で、これをマスターするとプログラミングの自由度が大幅に向上し、再利用性に優れた設計が可能になります。
 一方で、文法が複雑で可読性が悪化しやすいなどのデメリットもあり、濫用は禁物です。
 ここではテンプレートのごく初歩的な部分だけを紹介します。

 テンプレートには大別して2種類あります。
 1. 関数テンプレート
 2. クラステンプレート
 （変数テンプレートやエイリアステンプレートもありますが、およそ皆さんが使うことはないだろうと思います。）
*/

// 関数テンプレートの例。
// この関数は、引数aとbを受け取り、その和を返すだけのシンプルな関数ですが、
// int型、double型、float型などのプリミティブ型はもちろん、
// std::string型など、+演算子に対応するどのような型に対しても使えるようになっています。
// 逆に、+演算子に対応していない型に対しては呼び出すことができず、コンパイルエラーになります。
// このとき、Tのことを「テンプレート引数」と呼びます。
template <class T>
T Add(T a, T b)//Tにconstや&を付けずに定義すると、これはT型の変数a、bをコピーで受け取ることになります。
{
	return a + b;
}

// テンプレート引数は複数指定しても構いません。
// この場合、t1にBasetrack、t2にMicrotrackのように異なる型を与えることも可能になります。
// さらに、この関数自身はTrack1、Track2がどのような型であるかを知りませんが、
// それらの型が持つメンバ変数axにアクセスできます。axを持たない型の変数を引数に与えるとコンパイルエラーになります。
// メンバ変数だけでなく、メンバ関数を呼び出すことももちろん可能です。
template <class Track1, class Track2>
double GetDax(const Track1& t1, const Track2& t2)//const&を付けることで、t1、t2をコピーせずにconst参照で受け取ることができます。もちろんconstなしも可能です。
{
	return t1.ax - t2.ax;
}

// テンプレート引数Trackを引数や戻り値のどこに使うかは結構自由度があります。vectorの<>の中に置いても構いません。
// （テンプレート引数推定のルールは非常に複雑なので、ここではあまり詳細には説明しません。）
template <class Track>
double AxMean(const std::vector<Track>& tracks)
{
	//axの平均値を求める関数。
	double sum = 0;
	for (const Track& t : tracks) sum += t.ax;
	return sum / tracks.size();
}

// テンプレートで受け取った引数のメンバ関数を呼び出せるということは、
// 前回扱った仮想関数のように、外部から条件を与える関数なども作成可能です。
template <class Track, class Cut>
double AxMean(const std::vector<Track>& tracks, const Cut& cut)
{
	double sum = 0;
	int count = 0;
	for (const Track& t : tracks)
	{
		if (cut.Judge(t))
		{
			sum += t.ax;
			count++;
		}
	}
	return sum / count;
}

class PHCut
{
public:
	PHCut(int ph_min_) : ph_min(ph_min_) {}
	// メンバ関数を関数テンプレートにすることもできます。
	template <class Track>
	bool Judge(const Track& t) const
	{
		return t.ph >= ph_min;
	}
	int ph_min;
};


int main()
{
	// Add関数を用いた例。
	// int、double、std::stringはいずれも+演算子に対応しているので、Add関数を使うことができます。
	// 関数テンプレートは多くの場合、std::vector<...>のような<...>の部分は不要です。
	int a = 1;
	int b = 3;
	int res_int = Add(a, b);//Add関数の持つクラス型Tは自動的にint型と推定されます。言い換えると、Add<int>(a, b)と同等です。
	std::cout << res_int << std::endl;//4

	double c = 1.5;
	double d = 3.5;
	double res_double = Add(c, d);// Tはdouble型と推定されます。
	std::cout << res_double << std::endl;//5.0

	std::string e = "Hello, ";
	std::string f = "world!";
	std::string res_string = Add(e, f);// Tはstd::string型と推定されます。
	std::cout << res_string << std::endl;//Hello, world!


	// GetDax関数を用いた例。
	Basetrack bt1{ 12, 12345, 230058, 2.3015, 0.5933, 69341.0, 56801.9, 9123.0 };
	Basetrack bt2{ 12, 67890, 200025, 2.0169, 0.4104, 69332.0, 56824.4, 9123.0 };
	Microtrack mt{ 121, 11111, 110021, 2.1134, 0.5180, 69338.1, 56817.2, 9123.0 };

	//GetDaxは引数それぞれが.axというメンバ変数を持つことを要求します。
	//BasetrackとMicrotrackはともにこの条件を満たしているので、GetDax関数を呼び出すことができます。
	double dax_bb = GetDax(bt1, bt2);
	std::cout << dax_bb << std::endl;// 0.2846
	double dax_bm = GetDax(bt1, mt);// 0.1881
	std::cout << dax_bm << std::endl;


	// AxMean関数を用いた例。
	std::vector<Basetrack> btlist;
	btlist.push_back({ 12, 12345, 230058, 2.3015, 0.5933, 69341.0, 56801.9, 9123.0 });
	btlist.push_back({ 12, 67890, 200025, 2.0169, 0.4104, 69332.0, 56824.4, 9123.0 });
	btlist.push_back({ 12, 13579, 210041, 2.1798, 0.2223, 69389.1, 56830.6, 9123.0 });

	// AxMeanの引数は、.axというメンバ変数を持つクラスを格納するstd::vectorである必要があります。
	// std::vector<Basetrack>やstd::vector<Microtrack>はこの条件を満たしているので、AxMean関数を呼び出すことができます。
	double axmean1 = AxMean(btlist);//btlistのax平均値を求めています。
	double axmean2 = AxMean(btlist, PHCut(21));//btlistのうち、PHが21以上のもののax平均値を求めています。

	return 0;
}

/*
 問題
 BasetrackやMicrotrackなどの飛跡型の変数を受け取り、その2本が接続されうるかを判定、
 接続可/不可のときそれぞれtrue/falseを返すJudgeConnection関数を作成してください。
 このとき、受け取る飛跡の型はテンプレート引数として与え、Base-Base、Base-Microなど任意の組み合わせで動作するようにしてください。
 接続条件は次のようにしましょう。
 1. x、y方向の角度差がそれぞれ0.2以内である
 2. 両飛跡のz座標中心面までこれらの飛跡を延長したとき、その平面上での距離が200um以内である。
 （接続判定としては緩すぎる条件ですが、演習用に調整しています。）
*/