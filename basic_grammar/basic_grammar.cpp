#include <iostream> // <- std::coutを使うために必要。


int square(int x)
{
	return x * x;
}

int main()
{
	// 整数型の変数の宣言
	int var = 0;

	// 四則演算と代入
	var = (3 + 5 - 2 * 2) / 2; // 計算結果の2がsumに代入されます。

	int sum = 0;
	// for文によるループ
	for (int i = 0; i < 5; ++i)
	{
		// sumにiを加算していくことで、0から4までの合計を求めます。
		sum += i;
	}

	// std::coutによる結果の出力（コンソール画面に表示）。
	// C++ではputsやprintfではなく、std::coutを使うのが一般的です。
	// std::coutの後に「<<」で出力したい値をつなげていけばOKです。
	std::cout << "sum of 0 to 4 is " << sum << std::endl;
	// 「sum of 0 to 4 is 10」と表示されるはずです。

	// if文による条件分岐
	if (sum > 10)
	{
		std::cout << "sum is greater than 10" << std::endl;
	}
	else if (sum == 10)
	{
		std::cout << "sum is equal to 10" << std::endl;
	}
	else
	{
		std::cout << "sum is less than 10" << std::endl;
	}

	// 関数の呼び出し
	int result = square(5);
	std::cout << "square of 5 is " << result << std::endl;
}