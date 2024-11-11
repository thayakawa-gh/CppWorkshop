#include <iostream>
#include <format>
#include <map>

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

	// std::mapのキーとして利用するために、比較演算子<を定義しておきます。
	bool operator<(const PosRawidPair& other) const
	{
		// posが小さい順に並べ、posが同じならrawidが小さい順に並べる
		if (pos != other.pos) return pos < other.pos;
		else return rawid < other.rawid;
	}

	int pos;
	int64_t rawid;
};

int main()
{
	// std::mapのキーには任意のクラスを使うことができます。
	// ただし、そのクラスには比較演算子<が定義されている必要があります。
	Basetrack bt1{ 49, 3331242, 220070, -1.4348, -1.7940, 123929.2, 120950.0, 0.0, 470229401, 185065316 };

	std::map<PosRawidPair, Microtrack> mtmap;
	mtmap.insert(std::make_pair(PosRawidPair{ 491, 470214727 }, Microtrack{ 491, 470214727, 100029, 0.5756, 0.4590, 122685.1, 120705.1, 0.0 }));
	mtmap.insert(std::make_pair(PosRawidPair{ 491, 470229401 }, Microtrack{ 491, 470229401, 100039, -1.5306, -1.9042, 123929.2, 120950.0, 0.0 }));
	mtmap.insert(std::make_pair(PosRawidPair{ 492, 185065316 }, Microtrack{ 492, 185065316, 120031, -1.5466, -1.9229, 123642.2, 120591.2, 200.0 }));
	mtmap.insert(std::make_pair(PosRawidPair{ 492, 185125757 }, Microtrack{ 492, 185125757, 90007, 0.4430, 1.5083, 124813.5, 120957.7, 200.0 }));

	std::map<PosRawidPair, Microtrack>::iterator it1 = mtmap.find(PosRawidPair{ bt1.pl * 10 + 1, bt1.rawid_m[0] });
	std::map<PosRawidPair, Microtrack>::iterator it2 = mtmap.find(PosRawidPair{ bt1.pl * 10 + 2, bt1.rawid_m[1] });
	std::cout << std::format("dax1:{}, day1:{}, dax2:{}, day2:{}\n", it1->second.ax - bt1.ax, it1->second.ay - bt1.ay, it2->second.ax - bt1.ax, it2->second.ay - bt1.ay);
}

/*
 問題
 basetracks_pl49.txt、microtracks_pl49.txtという2つのファイルを用意しています。
 概ね今までと同じフォーマットですが、basetracks_pl49.txtにはface1、face2のMicrotrackのrawidが追記されています。
 これらの情報を、Basetrackはstd::vectorに、Microtrackはposとrawidをキーとするstd::mapに格納してください。
 その後、全Basetrackについてface1、face2のMicrotrackをstd::mapから検索し両面のdax、dayを求め、
 角度差がすべて0.01未満のBasetrackのみを選出してください。

 こちらで試した限り、下記の4本のBasetrackが生き残りました。
 pl: 49 rawid:     3330963 dax1: 0.0009, day1:-0.0009, dax2: 0.0056, day2:-0.0075
 pl: 49 rawid:     3331537 dax1: 0.0047, day1:-0.0064, dax2: 0.0027, day2:-0.0054
 pl: 49 rawid:     3537113 dax1: 0.0024, day1: 0.0059, dax2:-0.0004, day2:-0.0019
 pl: 49 rawid:     3962312 dax1: 0.0032, day1:-0.0049, dax2: 0.0013, day2: 0.0043
*/