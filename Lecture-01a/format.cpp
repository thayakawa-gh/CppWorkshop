#include <iostream>// <- std::coutを使うために必要。
#include <format>// <- std::formatを使うために必要。
#include <print>// <- std::printを使うために必要。

int main()
{
	//printfはもう古い。
	//C++ではstd::coutとstd::formatを使おう。

	char hello[] = "Hello";
	char world[] = "World";
	std::cout << hello << " " << world << "!\n";

	std::cout << std::format("{} {}!\n", hello, world);

	// 整数
	int i = 1;
	std::cout << std::format("i == {}\n", i);
	std::cout << std::format("i == {:0>3}\n", i);// 0埋め、右寄せ、3桁

	// 浮動小数点
	double d = 3.141592653589793;
	std::cout << std::format("pi == {}\n", d);
	std::cout << std::format("pi == {:>4.2f}\n", d);// 右寄せ、幅4、小数点以下2桁、fは指数表記をしないことを明示。

	// std::cout << std::formatを使う代わりに、std::printを使うこともできる。
	// ただしstd::printはかなり新しい機能なので、Visual Studio 2022 Update 7以降が必要、
	// かつC++言語標準を/std:c++latestに設定する必要がある。
	std::print("pi == {:>6.4f}\n", d);
}

/* 問題
int pl = 25;
int64_t rawid = 12345;
int ph = 220142;
double ax = 0.2446;
doulbe ay = -1.5907;
double x = 12605.2;
double y = 190451.0;
上記のような情報を持つBasetrackがあります。
このBasetrackの情報を、pl:0埋め3桁、rawid:10桁、ph:6桁、axay:小数第4位まで、xyz:小数第1位までというフォーマットで表示させてみましょう。
次のように表示されたら正解です。
025      12345 220142  0.2446 -1.5907   12605.2  190451.0
*/