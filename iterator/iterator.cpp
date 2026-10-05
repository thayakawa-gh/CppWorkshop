#include <iostream>
#include <format>
#include <vector>

/*
 #####イテレータを用いたforループ#####
 C++では、整数型のカウンタを使ったループだけでなく、イテレータを使ったループをよく用います。
 イテレータとは、std::vectorなどの要素を0番目から順に追跡していくものです。

 * std::vector<int>::iterator it = vec.begin()  ...  vecの0番目の要素を指すイテレータを取得します。
 * std::vector<int>::iterator end = vec.end()   ...  vecの最後の要素の"1個次"を指すイテレータを取得します。
 * ++it  ...  itを1個次の要素へ移動させます。
 * --it  ...  itを1個前の要素へ移動させます。
 * int x = *it  ...  イテレータが指し示している要素の値を取得します。
 * *it = 4 ... 代入も可能です※。

 イテレータを使って要素を一つ一つ参照していくことを、一般に走査(traverse)と呼びます。

 ※イテレータには上述のような通常のiteratorと、値の変更ができないconst_iteratorがあります。
 もしvectorがconst（ポインタと参照の回で扱います）の場合、begin()、end()はstd::vector<int>::const_iteratorを返します。
 const_iteratorの場合は、*it = 5のような代入はできません。
*/
int main()
{
	std::vector<double> vec{ 0.0, 0.1, 0.2, 0.3, 0.4 };

	std::vector<double>::iterator it = vec.begin();
	std::vector<double>::iterator end = vec.end();
	// endはvecの最後の要素の"次"を指しています。例えば10個の要素を持つvecの場合、
	// [0] [1] [2] [3] ... [9] [10]
	//  ↑                        ↑
	// begin                    end
	// です。もちろんvecの要素は0～9番目までしか存在しないので、endは実際には存在しない要素を指しています。

	std::cout << std::format("it refers to {}\n", *it); // itはvecの0番目の要素を指しているので、0.0が表示されます。
	//std::cout << std::format("end refers to {}\n", *end); // endはvecの最後の要素の"次"を指しているので、存在しない要素を参照しようとしており、バグります。実行しないでください。

	// イテレータでvectorの全要素を走査するためには、itがendに一致するまで++itで移動し続ければよいです。
	for (; it != end; ++it)
	{
		// 「*」によって、itの指している要素の値を取得。
		double x = *it;
		*it = 3 * x; // 代入も可能です。
		std::cout << std::format("{:.1f} -> {:.1f}\n", x, *it);
	}

	// 比較的新しいC++には、右辺の型を自動で推論し変数型を決定してくれるautoという機能があります。
	// auto x = 52; // xはint型として扱われます。
	// auto y = 3.14; // yはdouble型として扱われます。
	// std::vector<...>::iteratorなどと毎回書くのは大変なので、autoを使うと便利です。
	auto it2 = vec.begin();// std::vector<double>::iterator it2 = vec.begin();と同等です。
	auto end2 = vec.end();// std::vector<double>::iterator end2 = vec.end();と同等です。
	for (; it2 != end2; ++it2)
	{
		// 「*」によって、it2の指している要素の値を取得。
		double x = *it2;
		*it2 = 3 * x; // 代入も可能です。
		std::cout << std::format("{:.1f} -> {:.1f}\n", x, *it2);
	}


	// range-based for loop
	// 毎回std::vector<double>::iteratorなどと書くのは大変なので、
	// 全要素を走査する場合はもっと簡単な、range-based for loopと呼ばれる書き方が用意されています。
	// これは以下のように記述するもので、上のイテレータを使ったループと等価です。
	for (double x : vec)// for (auto x : vec)でも同等です。
	{
		std::cout << x << std::endl;
	}

	auto it = vec.begin();
	auto end = vec.end();
	for (; it != end; ++it)
	{
		double x = *it;
		std::cout << x << std::endl;
	}

	// もしvecの要素を修正したい場合は、double& xと書きましょう。
	for (double& x : vec)// for (auto& x : vec)でも同等です。
	{
		// 全ての要素を2倍にします。
		x *= 2;
	}
	// vecを修正しない場合は、const double&としても構いません。
	for (const double& x : vec)// for (const auto& x : vec)でも同等です。
	{
		std::cout << x << std::endl;
	}
	// constやら&やらの意味は「ポインタと参照」の回で説明します。多分。

	// イテレータやrange-based for loopを使ったループは、一般にint型のカウンタを使ったforループよりも高速です。
	// 用途に応じて使い分けましょう。
}

/*
 問題1
 30個の要素を持つstd::vector<int>型の変数を作成し、forループを使ってそれぞれに順に1～30の要素を持たせましょう。
 その後、イテレータを使ったループを用いて、全要素の和を計算してみましょう。
 結果が465になることを確認してください。

 問題2
 問題1のコードをrange-based for loopで書き直してみましょう。
*/