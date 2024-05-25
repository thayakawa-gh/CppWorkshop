#include <iostream>
#include <vector>
#include <algorithm>  // std::find

int main()
{
	// ベクターの初期化
	// int型の1, 2, 3, 4, 5という要素を持つベクターを作成する
	std::vector<int> vec = { 1, 2, 3, 4, 5 };

	// いろいろな初期化方法
	std::vector<int> vec0;  // 空のベクター
	std::vector<int> vec1(5);  // 5つの要素を0で初期化
	std::vector<int> vec2(5, 10);  // 5つの要素を10で初期化

	// 出力
	std::cout << "vec: ";
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// 要素の追加
	vec.push_back(6);
	std::cout << "After push_back(6): ";
	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// 要素へのアクセス
	std::cout << "Element at index 2: " << vec[2] << std::endl;

	// ベクターのサイズ
	std::cout << "Size of vec: " << vec.size() << std::endl;

	// 要素の挿入
	vec.insert(vec.begin() + 3, 10);  // インデックス3の位置に10を挿入
	std::cout << "After insert(10) at index 3: ";
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// 要素の削除
	vec.erase(vec.begin() + 3);  // インデックス3の要素を削除
	std::cout << "After erase at index 3: ";
	for (int val : vec) {
		std::cout << val << " ";
	}
	std::cout << std::endl;

	// 要素のクリア
	vec.clear();
	std::cout << "After clear, is vec empty? " << (vec.empty() ? "Yes" : "No") << std::endl;

	// 初期化してサイズを指定
	std::vector<int> vec2(5, 100);  // 5つの要素を100で初期化
	std::cout << "vec2: ";
	for (int val : vec2) {
		std::cout << val << " ";
	}
	std::cout << std::endl;

	return 0;
}

/*
問題
2、3、5、7、...と、30以下の素数を要素に持つstd::vector<int>を作成しましょう。
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