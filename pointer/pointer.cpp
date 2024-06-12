#include <iostream>
#include <vector>

void func(int& x)
{
	x = 4;
}
void const_func(const int& x)
{
	// x = 5; const参照型はこうした変更ができない。
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

int main()
{
	int a = 1;
	int b = 10;

	// ポインタ型。C言語のポインタと同じ。
	int* x = &a;
	*x = 2;
	std::cout << a << std::endl;
	x = &b;// xがbを指すように変更する。
	std::cout << b << std::endl;
	x = nullptr;// NULLを代入することで、何の変数も指し示していない空のポインタの状態にできる。

	// 参照型。本質的にはポインタと同じだが、「*」を使う必要がないこと、NULLを扱えないこと、初期化後に再代入できないことなどの違いがある。
	int& y = a;
	y += 3;
	std::cout << a << std::endl;
	// y = &b; 参照型はこうした再代入ができない。
	// y = nullptr; 参照型はNULLを扱えない。

	// 参照型を引数に取る関数。aの値はfuncによって変更されうる。
	func(a);
	std::cout << a << std::endl;

	// const参照型を引数に取る関数。aの値はconst_funcによって変更されない（プログラマが悪意ある使い方をしない限り）。
	const_func(a);


	std::vector<double> vec1{ 1.0, 2.0, 3.0, 4.0, 5.0 };

	// sum_from_copyとsum_from_referenceの結果はどちらも同じだが、速度とメモリ使用量が異なる。
	// 参照型を使うことで、関数の引数に大きなオブジェクトを渡す際に、コピーを作らずに済む。
	// int、doubleなどの基本型についてはコピーのコストは無視できるので参照で渡す必要はないが、
	// std::vectorやstd::stringなどの大きなオブジェクトについてはコピーのコストが大きいため、参照渡しが推奨される。
	std::cout << sum_from_copy(vec1) << std::endl;
	std::cout << sum_from_reference(vec1) << std::endl;


	std::vector<double> vec2{ 6.0, 7.0, 8.0, 9.0, 10.0 };

	// selectによってvec1かvec2のどちらかが返され、それを参照型で受け取る。
	// selectの引数は参照型、戻り値も参照型なので、vec1やvec2のコピーは一切発生しない。
	const std::vector<double>& vec_ref = select(0, vec1, vec2);
	// vec_refはconst参照型なので、vec_refの要素を変更することはできない。
	// このとき、range-based for loopはdoubleかconst double&で受け取らなければならない。double&にはできない。
	for (const double& x : vec_ref)
	{
		std::cout << x << " ";
	}
}