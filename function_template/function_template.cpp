#include <vector>
#include <format>
#include <iostream>

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
 1. クラステンプレート
 2. 関数テンプレート
 （変数テンプレートやエイリアステンプレートもありますが、およそ皆さんが使うことはないだろうと思います。）


*/

// 関数テンプレートの例。
// この関数は、引数aとbを受け取り、その和を返すだけのシンプルな関数ですが、
// int型、double型、float型などのプリミティブ型はもちろん、
// std::string型など、+演算子に対応するどのような型に対しても使えるようになっています。
// 逆に、+演算子に対応していない型に対しては呼び出すことができず、コンパイルエラーになります。
// このとき、Tのことを「テンプレート引数」と呼びます。
template <class T>
T Add(T a, T b)
{
	return a + b;
}
// テンプレート引数は複数指定しても構いません。
// この場合、t1にBasetrack、t2にMicrotrackのように異なる型を与えることも可能になります。
// さらに、この関数自身はTrack1、Track2がどのような型であるかを知りませんが、
// それらの型が持つメンバ変数axにアクセスできます。axを持たない型の変数を引数に与えるとコンパイルエラーになります。
// メンバ変数だけでなく、メンバ関数を呼び出すことももちろん可能です。
template <class Track1, class Track2>
double GetDax(const Track1& t1, const Track2& t2)
{
	return t1.ax - t2.ax;
}
// テンプレート引数Trackを引数や戻り値のどこに使うかは結構自由度があります。vectorの<>の中に置いても構いません。
template <class Track>
double AxMean(const std::vector<Track>& tracks, int phmin)
{
	//PH >= phminであるようなtrackのaxの平均値を求める関数。
	double sum = 0;
	for (const Track& t : tracks)
	{
		if (int(t.ph / 10000) >= phmin) sum += t.ax;
	}
	return sum / tracks.size();
}


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

int main()
{
	// Add関数を用いた例。
	// int、double、std::stringはいずれも+演算子に対応しているので、Add関数を使うことができます。
	int a = 1;
	int b = 3;
	int res_int = Add(a, b);
	std::cout << res_int << std::endl;

	double c = 1.5;
	double d = 3.5;
	double res_double = Add(c, d);
	std::cout << res_double << std::endl;

	std::string e = "Hello, ";
	std::string f = "world!";
	std::string res_string = Add(e, f);
	std::cout << res_string << std::endl;


	// GetDax関数を用いた例。
	Basetrack bt1{ 12, 12345, 230058, 2.3015, 0.5933, 69341.0, 56801.9, 9123.0 };
	Basetrack bt2{ 12, 67890, 200025, 2.0169, 0.4104, 69332.0, 56824.4, 9123.0 };
	Microtrack mt{ 121, 11111, 110021, 2.1134, 0.5180, 69338.1, 56817.2, 9123.0 };

	double dax_bb = GetDax(bt1, bt2);
	std::cout << dax_bb << std::endl;
	double dax_bm = GetDax(bt1, mt);
	std::cout << dax_bm << std::endl;

	return 0;
}