#include <memory>
#include <iostream>
#include <fstream>
#include <format>
#include <vector>
#include <string>
#include <sstream>

class Basetrack
{
public:

	double GetAng() const { return std::sqrt(ax * ax + ay * ay); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};
class BasetrackPair
{
public:

	BasetrackPair() : ptr{ nullptr, nullptr } {}
	BasetrackPair(const Basetrack& bt1, const Basetrack& bt2)
	{
		ptr[0] = std::make_shared<Basetrack>(bt1);
		ptr[1] = std::make_shared<Basetrack>(bt2);
	}
	~BasetrackPair() = default;
	std::shared_ptr<Basetrack> ptr[2];
};


int main()
{
	std::ifstream ifs("../smart_pointer/linklets.txt");
	if (!ifs)
	{
		std::cerr << "File not found\n";
		return -1;
	}

	std::vector<BasetrackPair> btpairs;
	std::string line;
	while (std::getline(ifs, line))
	{
		std::istringstream iss(line);
		Basetrack bt0, bt1;
		iss >> bt0.pl >> bt0.rawid >> bt0.ph >> bt0.ax >> bt0.ay >> bt0.x >> bt0.y >> bt0.z;
		iss >> bt1.pl >> bt1.rawid >> bt1.ph >> bt1.ax >> bt1.ay >> bt1.x >> bt1.y >> bt1.z;

		BasetrackPair tmp;
		for (const BasetrackPair& p : btpairs)
		{
			if (p.ptr[0]->pl == bt0.pl && p.ptr[0]->rawid == bt0.rawid)
			{
				tmp.ptr[0] = p.ptr[0];
			}
			if (p.ptr[1]->pl == bt1.pl && p.ptr[1]->rawid == bt1.rawid)
			{
				tmp.ptr[1] = p.ptr[1];
			}
			if (tmp.ptr[0] && tmp.ptr[1])
			{
				break;
			}
		}

		if (!tmp.ptr[0])
		{
			tmp.ptr[0] = std::make_shared<Basetrack>(bt0);
		}
		if (!tmp.ptr[1])
		{
			tmp.ptr[1] = std::make_shared<Basetrack>(bt1);
		}
		btpairs.emplace_back(tmp);
	}

	size_t count0 = 0;
	size_t count1 = 0;
	for (const BasetrackPair& p : btpairs)
	{
		if (p.ptr[0].use_count() == 1)
		{
			count0++;
		}
		if (p.ptr[1].use_count() == 1)
		{
			count1++;
		}
	}
	std::cout << std::format("count0: {}, count1: {}\n", count0, count1);
}