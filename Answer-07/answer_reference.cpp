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

class AffineParam
{
public:
	double a, b, c, d, p, q;
};

int CountPH20(const std::vector<Basetrack>& btlist)
{
	int count = 0;
	for (const Basetrack& bt : btlist)
	{
		if (int(bt.ph / 10000) >= 20) ++count;
	}
	return count;
}

void TransAffine(std::vector<Basetrack>& btlist, const AffineParam& aff)
{
	for (Basetrack& bt : btlist)
	{
		//ä‘à·Ç¢
		bt.x = bt.x * aff.a + bt.y * aff.b + aff.p;
		bt.y = bt.x * aff.c + bt.y * aff.d + aff.q;
		bt.ax = bt.ax * aff.a + bt.ay * aff.b;
		bt.ay = bt.ax * aff.c + bt.ay * aff.d;

		//ê≥ÇµÇ¢
		double x_ = bt.x * aff.a + bt.y * aff.b + aff.p;
		double y_ = bt.x * aff.c + bt.y * aff.d + aff.q;
		double ax_ = bt.ax * aff.a + bt.ay * aff.b;
		double ay_ = bt.ax * aff.c + bt.ay * aff.d;
		bt.x = x_;
		bt.y = y_;
		bt.ax = ax_;
		bt.ay = ay_;
	}
}

int main()
{
	std::ifstream ifs("../read_text/basetracks.txt");
	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	std::string buf;
	std::vector<Basetrack> btlist;
	while (std::getline(ifs, buf))
	{
		Basetrack bt;
		std::istringstream iss(buf);
		iss >> bt.pl >> bt.rawid >> bt.ph >> bt.ax >> bt.ay >> bt.x >> bt.y >> bt.z;
		btlist.push_back(bt);
	}

	std::cout << CountPH20(btlist) << std::endl;//502

	AffineParam aff{ 0.9978, 0.0031, -0.0035, 0.9894, 1359.1, -403.7 };
	TransAffine(btlist, aff);
	for (const auto& bt : btlist)
	{
		std::cout << std::format("{:0>3} {:>10} {:>6} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
			bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y);
	}
}