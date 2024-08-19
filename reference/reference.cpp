#include <iostream>
#include <format>
#include <vector>

// ######参照型について######
// C++では通常、変数を他の変数に代入すると、その値はコピー、つまり複製されます。
// double a = 1.5;
// double b = a;
// 上では、bにはaの値がコピーされ、1.5が入ります。ここで、aとbは独立した2個の変数となります。
// 仮に以下のようにbの値を変更したとしても、aとbは独立した変数のため、aの値は1.5のまま変化しません。
// b = 2.0;
// std::cout << std::format("{} {}\n", a, b); ... 1.5 2.0と表示されます。
// 
// 一方で、C++には参照と呼ばれる概念があります。
// double a = 1.5;
// double& b = a;
// このように'&'記号をつけて宣言した変数bは、aへの参照となります。
// すなわち、bはaと値を共有しており、同一の変数です。aもbも、メモリ上にある1個のdouble型変数を指し示しているのです。
// bは通常のint型変数と同じように扱うことができますが、bの値が変化すると値を共有しているaも変化します。同様に、aの値を変更するとbも変化します。
// b = b * 3;
// std::cout << std::format("{} {}\n", a, b); ... 4.5 4.5と表示されます。
//
// 更に加えると、const参照型というものもあります。
// const double& c = a;
// このように宣言した変数cは、aへの参照である点ではbと似ていますが、cはconst修飾されているため、cを通じてaの値を変更することはできません。
// a = 2.5;
// std::cout << c << std::endl; ... 2.5と表示されます。
// c = 2.0; ... エラーが発生します。const double&型のcを通じてaの値を変更することはできません。
//
// constは、特に理由がなければ付けておくことが推奨されます。不用意に値を変更されることを防ぐことができるためです。
// 値を変更しなければならないときだけ、constなしの参照型を使いましょう。


// 参照型はなぜ必要なのかというと、
// 1. 関数の引数など、別の変数に値を渡す際に、コピーを作らずに済む。
// 2. 関数の引数としてconstでない参照を受け取ると、その関数内で引数の値を変更することができる。
// などがあります。
// std::vectorやstd::stringなどの大きなオブジェクトは、安易に変数をコピーすると非常に大きなオーバーヘッドが生じ、
// プログラムのパフォーマンスを著しく低下させる可能性があります。
// int、float、doubleなどの基本型はコピーのコストが小さいため、参照型の引数でなくとも構いませんが、
// 大きなオブジェクトについては参照型の引数を使うことでパフォーマンスへの悪影響を回避することができます。

// ここで紹介した参照型は、lvalue reference（左辺値参照）と呼ばれるものです。
// 実はrvalue reference（右辺値参照）という概念もあり、モダンC++ではこれらをきちんと区別して扱う必要がありますが、
// このあたりはムーブセマンティクスの回で詳しく扱う予定です。

void func(int& x)
{
	x = 4;
}
void const_func(const int& x)
{
	// x = 5; const参照型は参照先の値を変更することができません。
}

// 良くない例。vecのコピーを作っているので、コピーのコストがかかるし、メモリも無駄に使う。
double sum_from_copy(std::vector<double> vec)
{
	double s = 0;
	for (auto v : vec)
	{
		s += v;
	}
	return s;
}
// 良い例。vecへの参照を受け取っているので、コピーのコストがかからないし、メモリも無駄に使わない。
double sum_from_reference(const std::vector<double>& vec)
{
	double s = 0;
	for (auto v : vec)
	{
		s += v;
	}
	return s;
}

// 参照型を返す関数も定義できる。x==0ならvec1、そうでなければvec2を返す。
const std::vector<double>& select(int x, const std::vector<double>& vec1, const std::vector<double>& vec2)
{
	if (x == 0) return vec1;
	else return vec2;
}
// 間違った使い方。関数内で作られた変数は関数を抜けるときに破棄されるので、
// 破棄された変数への参照を返すと未定義動作（どういう結果になるか分からない、大抵バグる）になる。
const std::vector<double>& wrong_select(int x, const std::vector<double>& vec1, const std::vector<double>& vec2)
{
	std::vector<double> vec;//vecは関数内で作られた変数なので、関数を抜けるときに破棄される。
	if (x == 0) vec = vec1;
	else vec = vec2;
	return vec;
}


int main()
{
	int a = 1;

	// 参照型。
	int& x = a;
	x += 3;// yに何らかの操作を行うと、yの参照先であるaの値が変更されます。
	std::cout << std::format("{} {}\n", a, x) << std::endl;// 4 4と表示されます。

	const int& z = a;
	//z += 3; const参照型は参照先の値を変更することができません。

	// 参照型を引数に取る関数。non-constのため、aの値はfuncによって変更される可能性があります。
	func(a);
	std::cout << a << std::endl;

	// const参照型を引数に取る関数。aの値はconst_funcによって変更されません（プログラマが悪意ある使い方をしない限り）。
	const_func(a);


	std::vector<double> vec1{ 1.0, 2.0, 3.0, 4.0, 5.0 };

	// sum_from_copyとsum_from_referenceの結果はどちらも同じですが、速度とメモリ使用量に差が出てきます。
	// 参照型を使うことで、関数の引数に大きなオブジェクトを渡す際に、コピーを作らずに済むようになります。
	// int、doubleなどの基本型についてはコピーのコストは十分小さいので、
	// 参照で渡す必要はありませんが（値を書き換えたい場合など、必要なら参照で渡しても構いません）、
	// std::vectorやstd::stringなどの大きなオブジェクトについてはコピーのコストが大きいため、参照渡しするほうが速度が速くなり、メモリの無駄遣いも防げます。
	std::cout << sum_from_copy(vec1) << std::endl;
	std::cout << sum_from_reference(vec1) << std::endl;


	std::vector<double> vec2{ 6.0, 7.0, 8.0, 9.0, 10.0 };

	// selectによってvec1かvec2のどちらかが返され、それを参照型で受け取っています。
	// selectの引数は参照型、戻り値も参照型なので、vec1やvec2のコピーは一切発生していません。
	const std::vector<double>& vec_ref = select(0, vec1, vec2);

	// vec_refはconst参照型なので、vec_refの要素を変更することはできません。
	// このとき、range-based for loopはdoubleかconst double&で受け取る必要が出てきます。double&にはできません。
	for (const double& x : vec_ref)
	{
		std::cout << x << " ";
	}
}

/*
 問題
 1. 次の要件を満たす関数を作ってください。
    * 引数としてstd::vector<Basetrack>を受け取り、PHが20以上のBasetrackの数を返す関数。
    * 引数はconst参照型で受け取り、何らかの整数型の戻り値で結果を返すこと。
 その後、前回の問題で使用したbasetracks.txt（read_textフォルダ内にあります）を読み込み、正しい結果を得られるか確認してください。

 2. 次の要件を満たす関数を作ってください。
    * 引数としてstd::vector<Basetrack>を受け取り、全Basetrackの座標と角度を次のアフィン変換パラメータを用いて変換する。
      (a, b, c, d, p, q) = (0.9978, 0.0031, -0.0035, 0.9894, 1359.1, -403.7)
      なお、アフィン変換は次のような変換式で行うものとします。
      座標 : x_ = x * a + y * b + p, y_ = x * c + y * d + q
      角度 : ax_ = ax * a + ay * b, ay_ = ax * c + ay * d
    * 引数は参照型で受け取り、受け取った引数を直接編集する。戻り値はvoidとし、何ら値を返さない。
 その後、前回の問題で使用したbasetrack.txtを読み込み、正しい結果を得られるか確認してください。
*/