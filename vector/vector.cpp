#include <iostream>
#include <vector> // <-- std:vectorを使うために必要

/*
 ##### std::vector #####
 std::vectorはC++標準ライブラリに含まれる、動的配列を扱う機能です。
 C言語では動的配列を扱うためにmallocやfreeを使う必要がありました。
 しかしstd::vectorを使えば、動的配列を簡単に、かつ安全に扱うことができます。

					C言語の配列										C++のstd::vector
  配列の作成			int* arr = (int*)malloc(5 * sizeof(int))		std::vector<int> vec(5)
  配列のアクセス		arr[2]											vec[2]
  長さ変更			-												vec.resize(6)
  末尾への追加		-												vec.pop_back()
  末尾要素の削除		-												vec.pop_back()
  サイズ取得			-												vec.size()
  挿入				-												vec.insert(vec.begin() + 3, 10)
  部分削除			-												vec.erase(vec.begin() + 3)
  全要素削除			-												vec.clear()
 */

int main()
{
	// ベクターの初期化
	// int型の1, 2, 3, 4, 5という要素を持つベクターを生成しています。
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	
	// vectorはintだけでなくdoubleやstringなど任意の型を格納することができます。
	std::vector<std::string> vec_str = { "Hello", "World" };

	// 出力
	std::cout << "vec: ";
	for (size_t i = 0, size = vec.size(); i < size; ++i)
	{
		// vectorの各要素には、配列と同じくvec[整数]でアクセスできます。
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";

	// いろいろな初期化方法
	std::vector<int> vec0; // 空のベクターを生成します。
	std::vector<int> vec1(5); // 5つの要素を0で初期化。vec1 = { 0, 0, 0, 0, 0 }と同じ結果になります。
	std::vector<int> vec2(5, 10); // 5つの要素を10で初期化。vec1 = { 10, 10, 10, 10, 10 }と同じ結果になります。

	// 要素の追加
	// push_back(6)によって、vecの末尾に6が追加されます。
	vec.push_back(6);
	std::cout << "After push_back(6): ";
	for (size_t i = 0, size = vec.size(); i < size; ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";

	// ベクターのリサイズ
	// vecの要素数を8に拡張し、増えた要素を0で初期化します。
	vec.resize(8);
	for (size_t i = 0, size = vec.size(); i < size; i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";
	// 要素数を6に戻します。その結果、要素は0～5番目までとなり、6番目と7番目の要素は消滅します。
	vec.resize(6);

	// ベクターの要素数
	std::cout << "Size of vec: " << vec.size() << std::endl;

	// 要素の挿入
	// 3番目に10を挿入します。もともと3番目以降にあった要素は1つずつ後ろに移動します。
	vec.insert(vec.begin() + 3, 10);
	std::cout << "After insert(10) at index 3: ";
	for (size_t i = 0, size = vec.size(); i < size; ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// 要素の削除
	// 3番目の要素を削除します。もともと4番目以降にあった要素は削除された領域を埋めるように前に移動します。
	vec.erase(vec.begin() + 3);
	std::cout << "After erase at index 3: ";
	for (size_t i = 0, size = vec.size(); i < size; ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// 要素のクリア
	// vecのすべての要素を削除し、要素数を0にします。
	vec.clear();
	std::cout << "After clear, size of vec: " << vec.size() << std::endl;

	return 0;
}

/*
 問題1
 空のstd::vector<int>を用意し、push_backを使って0～30を要素として順に追加してみましょう。
 0から30までをループするforループを使ってください。
 
 問題2
 問題1のコードを修正し、2、3、5、7、...と、30以下の素数を要素に持つstd::vector<int>を作成しましょう。
 なお、素数か否かの判定は次のIsPrimeを呼び出すことで判定できます。
*/

bool IsPrime(int n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; i * i <= n; i += 2)
	{
		if (n % i == 0) return false;
	}
	return true;
}