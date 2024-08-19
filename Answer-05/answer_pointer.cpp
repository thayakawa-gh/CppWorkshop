#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <string>
#include <sstream>

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

class BasetrackPair
{
	public:
	BasetrackPair() : ptr{ nullptr, nullptr } {}
	BasetrackPair(Basetrack* bt1, Basetrack* bt2) : ptr{ bt1, bt2 } {}

	Basetrack* ptr[2];// ポインタ型の配列。ptr[0]、ptr[1]がそれぞれ2本のBasetrack型変数へのアドレスを持っています。
};

int main()
{
	std::ifstream ifs("../read_text/basetracks.txt");
	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	std::string buf;
	std::vector<Basetrack> bts;
	while (std::getline(ifs, buf))
	{
		Basetrack bt;
		std::istringstream iss(buf);
		iss >> bt.pl >> bt.rawid >> bt.ph >> bt.ax >> bt.ay >> bt.x >> bt.y >> bt.z;
		bts.push_back(bt);
	}


	// 方法1 添字i、jでループする場合
	size_t size = bts.size();
	std::vector<BasetrackPair> btpairs;
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			if (std::abs(bts[i].x - bts[j].x) > 500.0) continue;
			if (std::abs(bts[i].y - bts[j].y) > 500.0) continue;
			if (std::abs(bts[i].ax - bts[j].ax) > 0.1) continue;
			if (std::abs(bts[i].ay - bts[j].ay) > 0.1) continue;
			btpairs.push_back(BasetrackPair{ &bts[i], &bts[j] });
		}
	}

	std::cout << std::format("Found {} pairs.\n", btpairs.size());
	for (const BasetrackPair& btp : btpairs)
	{
		std::cout << std::format("({:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}) - ({:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f})\n",
								 btp.ptr[0]->ax, btp.ptr[0]->ay, btp.ptr[0]->x, btp.ptr[0]->y,
								 btp.ptr[1]->ax, btp.ptr[1]->ay, btp.ptr[1]->x, btp.ptr[1]->y);
	}

	btpairs.clear();

	// 方法2 イテレータでループする場合
	for (std::vector<Basetrack>::iterator it1 = bts.begin(); it1 != bts.end(); ++it1)
	{
		for (std::vector<Basetrack>::iterator it2 = it1 + 1; it2 != bts.end(); ++it2)
		{
			if (std::abs(it1->x - it2->x) > 500.0) continue;
			if (std::abs(it1->y - it2->y) > 500.0) continue;
			if (std::abs(it1->ax - it2->ax) > 0.1) continue;
			if (std::abs(it1->ay - it2->ay) > 0.1) continue;
			btpairs.push_back(BasetrackPair{ &(*it1), &(*it2) });
		}
	}
}