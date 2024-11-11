#include <iostream>
#include <format>
#include <fstream>
#include <sstream>
#include <vector>
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
	int pos;
	int64_t rawid;

	bool operator<(const PosRawidPair& other) const
	{
		// posが小さい順に並べ、posが同じならrawidが小さい順に並べる
		if (pos != other.pos) return pos < other.pos;
		else return rawid < other.rawid;
	}
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

	std::map<PosRawidPair, Microtrack> mtmap;
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
		std::map<PosRawidPair, Microtrack>::iterator it1 = mtmap.find(PosRawidPair{ bt.pl * 10 + 1, bt.rawid_m[0] });
		std::map<PosRawidPair, Microtrack>::iterator it2 = mtmap.find(PosRawidPair{ bt.pl * 10 + 2, bt.rawid_m[1] });
		if (it1 != mtmap.end() && it2 != mtmap.end())
		{
			double dax1 = it1->second.ax - bt.ax;
			double day1 = it1->second.ay - bt.ay;
			double dax2 = it2->second.ax - bt.ax;
			double day2 = it2->second.ay - bt.ay;
			if (std::abs(dax1) < 0.01 && std::abs(day1) < 0.01 && std::abs(dax2) < 0.01 && std::abs(day2) < 0.01)
				std::cout << std::format("pl:{:>3} rawid:{:>12} dax1:{:>7.4f}, day1:{:>7.4f}, dax2:{:>7.4f}, day2:{:>7.4f}\n",
										 bt.pl, bt.rawid, dax1, day1, dax2, day2);
		}
	}

	return 0;
}