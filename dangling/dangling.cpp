#include <format>
#include <vector>
#include <iostream>

/*
 ######参照型の危険性について######
 ダングリング参照とは、既に破棄された変数を指す参照のことです。
 以下の例では、関数内で作られた変数vecを参照型で返しています。
 が、関数内で用意された変数は、関数を抜けるときに破棄されるため、
 関数の戻り値の参照は、既に破棄された、無効となった変数を指し示していることになります。
 その後のvecへの参照は未定義動作（どういう結果になるか分からない、大抵バグる）になります。
 参照型を使うときは、参照先の変数がいつまで有効なのかを意識しましょう。
*/

const std::vector<int>& MakeIntegers_danger()
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	return vec;
}
// 関数内で作られた一時的な変数を返すのなら、参照型ではなく、コピーを返すべきです。
// コピーコストがかかるのでは？と思うかもしれませんが、一時的な変数の場合はコンパイラがうまく最適化してコストをなくしてくれます。
// RVO（Return Value Optimization）、NRVO（Named Return Value Optimization）という機能です。
std::vector<int> MakeIntegers_safe()
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	return vec;
	//もしくは、
	//return std::vector<int>{ 1, 2, 3, 4, 5 };
	//のように一行で書いてもOKです。
}

int main()
{
	// 以下の例では、意図的に危険な処理をしています。
	// このような処理を実行したとき、何が起きるかは不明です。
	// もしかすると何事もなく動いてしまうかもしれませんし、空のvectorと扱われ何も出力されないだけかもしれませんし、
	// あるいはクラッシュ（プログラムの異常終了）するかもしれません。

	const std::vector<int>& vec = MakeIntegers_danger();
	for (auto v : vec)
	{
		std::cout << v << " ";
	}
	std::cout << "\n";


	// こちらは正しい処理です。
	std::vector<int> vec2 = MakeIntegers_safe();
	for (auto v : vec2)
	{
		std::cout << v << " ";
	}
}