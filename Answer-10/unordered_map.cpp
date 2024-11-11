#include <iostream>
#include <format>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>


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
	std::vector<Basetrack> btlist;
	std::ifstream ifs("../map_with_any_type/basetrack_pl49.txt");
	if (!ifs)
	{
		std::cerr << "Error: file not found." << std::endl;
		return -1;
	}
	std::string buf;
	while (std::getline(ifs, buf))
	{
		Basetrack b;
		std::istringstream iss(buf);
		iss >> b.pl >> b.rawid >> b.ph >> b.ax >> b.ay >> b.x >> b.y >> b.z >> b.rawid_m[0] >> b.rawid_m[1];
		btlist.push_back(b);
	}

	std::unordered_map<PosRawidPair, Microtrack, HasherForPosRawidPair> mtmap;
	std::ifstream ifs2("../map_with_any_type/microtrack_pl49.txt");
	if (!ifs2)
	{
		std::cerr << "Error: file not found." << std::endl;
		return -1;
	}
	while (std::getline(ifs2, buf))
	{
		Microtrack m;
		std::istringstream iss(buf);
		iss >> m.pos >> m.rawid >> m.ph >> m.ax >> m.ay >> m.x >> m.y >> m.z;
		mtmap.insert(std::make_pair(PosRawidPair{ m.pos, m.rawid }, m));
	}

	std::vector<Basetrack> res;
	for (const Basetrack& bt : btlist)
	{
		std::unordered_map<PosRawidPair, Microtrack>::iterator it1 = mtmap.find(PosRawidPair{ bt.pl * 10 + 1, bt.rawid_m[0] });
		std::unordered_map<PosRawidPair, Microtrack>::iterator it2 = mtmap.find(PosRawidPair{ bt.pl * 10 + 2, bt.rawid_m[1] });
		if (it1 != mtmap.end() && it2 != mtmap.end())
		{
			double dax1 = it1->second.ax - bt.ax;
			double day1 = it1->second.ay - bt.ay;
			double dax2 = it2->second.ax - bt.ax;
			double day2 = it2->second.ay - bt.ay;
			if (std::abs(dax1) < 0.01 && std::abs(day1) < 0.01 && std::abs(dax2) < 0.01 && std::abs(day2) < 0.01)
				std::cout << std::format("unordered_map ... pl:{:>3} rawid:{:>12} dax1:{:>7.4f}, day1:{:>7.4f}, dax2:{:>7.4f}, day2:{:>7.4f}\n",
										 bt.pl, bt.rawid, dax1, day1, dax2, day2);
		}
	}

	return 0;
}