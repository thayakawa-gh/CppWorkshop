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

 イテレータを使って要素を一つ一つ参照していくことを、一般に走査(traverse)と呼びます。
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
	// よって、イテレータでvectorの全要素を走査するためには、itがendに一致するまで++itで移動し続ければよいことになります。
	for (; it != end; ++it)
	{
		// 「*」によって、itの指している要素の値を取得。
		double x = *it;
		std::cout << x << " " << std::endl;
	}


	// range-based for loop
	// 毎回std::vector<double>::iteratorなどと書くのは大変なので、
	// 全要素を走査する場合はもっと簡単な、range-based for loopと呼ばれる書き方が用意されています。
	// これは以下のように記述するもので、上のイテレータを使ったループと等価です。
	for (double x : vec)
	{
		std::cout << x << " " << std::endl;
	}

	// もしvecの要素を修正したい場合は、double& xと書きましょう。
	for (double& x : vec)
	{
		// 全ての要素を2倍にします。
		x *= 2;
	}
	// vecを修正しない場合は、const double&としても構いません。
	for (const double& x : vec)
	{
		std::cout << x << " " << std::endl;
	}
	// constやら&やらの意味は「ポインタと参照」の回で説明します。多分。

	// イテレータやrange-based for loopを使ったループは、一般にint型のカウンタを使ったforループよりも高速です。
	// 用途に応じて使い分けましょう。
}

/*
 問題1
 30個の要素を持つstd::vector<int>型の変数を作成し、1～30の要素を持たせましょう。
 その後、イテレータを使ったループを用いて、全要素の和を計算してみましょう。
 結果が465になることを確認してください。

 問題2
 問題1のコードをrange-based for loopで書き直してみましょう。
*/