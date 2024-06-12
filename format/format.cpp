#include <iostream>// <- std::coutを使うために必要。
#include <format>// <- std::formatを使うために必要。
#include <print>// <- std::printlnを使うために必要。

int main()
{
	// C言語のHello World
	printf("Hello World!");


	//printfはもう古い。
	//C++ではstd::coutとstd::formatを使おう。

	char hello[] = "Hello";
	char world[] = "World";
	std::cout << hello << " " << world << "!\n";

	std::cout << std::format(" {}!\n", hello, world);

	// 整数
	int i = 1;
	std::cout << std::format("i == {}\n", i);//
	std::cout << std::format("i == {:0>3}\n", i);// 0埋め、右寄せ、3桁
	//i == 003
	// 
	// 浮動小数点
	double d = 3.141592653589793;
	std::cout << std::format("pi == {}\n", d);
	std::cout << std::format("pi == {:>4.2f}\n", d);// 右寄せ、幅4、小数点以下2桁、fは指数表記をしないことを明示。

	// std::cout << std::formatを使う代わりに、std::printやstd::printlnを使うこともできる。
	std::println("pi == {:>6.4f}", d);

	// std::format、std::printlnはどちらもここ数年の間に導入された新しい機能のため、古いコンパイラでは使えないことがある。
	// std::formatを使うにはVisual Studio 2019 16.10以降が必要で、C++言語標準を/std:c++20または/std:c++latestに設定する必要がある。
	// std::printlnを使うにはVisual Studio 2022 17.7以降が必要、かつC++言語標準を/std:c++latestに設定する必要がある。

	return 0;
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
このBasetrackの情報を、いずれも右寄せで、
pl:0埋め幅3、rawid:幅10、ph:幅6、axay:幅7で小数第4位まで、xyz:幅9で小数第1位まで
というフォーマットで表示させてみましょう。
次のように表示されたら正解です。
025      12345 220142  0.2446 -1.5907   12605.2  190451.0
*/