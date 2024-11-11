#include <iostream>
#include <format>
#include <unordered_map>

/*
 ######std::unordered_mapについて######
 std::unordered_mapは、std::mapと同様にキーと値をペアで格納するコンテナです。
 その機能はstd::mapに非常によく似ており、挿入、検索、走査などほとんど同じ使い方が可能です。
 ただし、いくつかの点で違いがあります。

 まず、std::unordered_mapは二分木探索を使いません。ハッシュテーブルによる検索を行います。
 ハッシュテーブルとは、キーの値をハッシュ関数によってハッシュ値（64bit整数値など）に変換し、
 そのハッシュ値を配列のインデックスとして利用することで高速に検索する手法です。
 一般には二分木探索よりも検索速度が早く、O(1)、つまり要素数にかかわらず定数時間での検索が可能とされています。

 また、std::unordered_mapは二分木探索でないため、要素がキーの大小関係に従ってソートされていません。
 forループなどで走査を行うと、てんでバラバラな順序でアクセスすることになります。

 さらに、キーに要求されるのは比較演算子<ではなく、ハッシュ関数と等値比較演算子==です。
 intやstd::stringなどのありふれた方はこれらがすでに定義されているので特殊なことは必要ないのですが、
 PosRawidPairのような独自クラスなどをキーにする場合は、これらの演算子等を適切に定義しておく必要があります。


 なお、実のところ標準ライブラリに搭載されているstd::unordered_mapは、それほど高速ではありません。
 std::mapよりは概ね優れていますが、ハッシュテーブルとして見ると、世の中にはもっと高速な実装が多数あります。
 データ解析で要求される程度の速度ならstd::mapやstd::unordered_mapでも問題ないと思いますが、
 もっと高速なハッシュテーブルを使いたい場合はサードパーティのライブラリを探してみるとよいかもしれません。
 私はankerl::unordered_dense::mapを時々使っています。std::unordered_mapとほぼ同じ使い方で、ずっと高速な走査、検索を実現しています。
 （その代わり要素の削除が遅いという欠点があります。）
*/


class Microtrack
{
public:
	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
	int64_t rawid_m[2];
};

class PosRawidPair
{
public:

	// std::unordered_mapは、キーの比較に<演算子ではなく、==演算子を使います。
	bool operator==(const PosRawidPair& other) const
	{
		return pos == other.pos && rawid == other.rawid;
	}

	int pos;
	int64_t rawid;
};

// PosRawidPairのためのハッシュ関数を定義します。
class HasherForPosRawidPair
{
public:

	// ハッシュ関数本体の定義です。
	// 基本的に、キーの値を疑似乱数生成のようにほぼランダムな整数値に変換することが望ましいとされています。
	// 様々な方法がありますが、ここではその一例を紹介します。
	size_t operator()(const PosRawidPair& p) const
	{
		return std::hash<int>()(p.pos) ^ std::hash<int64_t>()(p.rawid);
	}
	// operator()は関数呼び出し演算子のオーバーロードで、関数オブジェクトに関わる重要な技法なのですが、ここでは説明はしません。
};

int main()
{
	Basetrack bt1{ 49, 3331242, 220070, -1.4348, -1.7940, 123929.2, 120950.0, 0.0, 470229401, 185065316 };

	// std::mapとほぼ同様の使い方ができます。
	// ただし、独自クラスなどをキーにする場合は、ハッシュ関数を定義したクラスをテンプレート引数の最後に指定する必要があります。
	std::unordered_map<PosRawidPair, Microtrack, HasherForPosRawidPair> mtmap;
	mtmap.insert(std::make_pair(PosRawidPair{ 491, 470214727 }, Microtrack{ 491, 470214727, 100029, 0.5756, 0.4590, 122685.1, 120705.1, 0.0 }));
	mtmap.insert(std::make_pair(PosRawidPair{ 491, 470229401 }, Microtrack{ 491, 470229401, 100039, -1.5306, -1.9042, 123929.2, 120950.0, 0.0 }));
	mtmap.insert(std::make_pair(PosRawidPair{ 492, 185065316 }, Microtrack{ 492, 185065316, 120031, -1.5466, -1.9229, 123642.2, 120591.2, 200.0 }));
	mtmap.insert(std::make_pair(PosRawidPair{ 492, 185125757 }, Microtrack{ 492, 185125757, 90007, 0.4430, 1.5083, 124813.5, 120957.7, 200.0 }));

	std::unordered_map<PosRawidPair, Microtrack>::iterator it1 = mtmap.find(PosRawidPair{ bt1.pl * 10 + 1, bt1.rawid_m[0] });
	std::unordered_map<PosRawidPair, Microtrack>::iterator it2 = mtmap.find(PosRawidPair{ bt1.pl * 10 + 2, bt1.rawid_m[1] });
	std::cout << std::format("unordered_map ... dax1:{}, day1:{}, dax2:{}, day2:{}\n", it1->second.ax - bt1.ax, it1->second.ay - bt1.ay, it2->second.ax - bt1.ax, it2->second.ay - bt1.ay);
}

/*
 問題
 map_with_any_typeで解いた問題を、std::unordered_mapに書き換えてみましょう。
 さらに、std::mapを使ったときと同様の結果になることを確認しましょう。
*/