#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

int main()
{
	std::ifstream ifs("../read_text/basetracks.txt");
	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}
	Basetrack tmp;
	std::vector<Basetrack> btlist;
	std::string line;
	while (std::getline(ifs, line))
	{
		std::istringstream iss(line);
		iss >> tmp.pl >> tmp.rawid >> tmp.ph >> tmp.ax >> tmp.ay >> tmp.x >> tmp.y >> tmp.z;
		btlist.push_back(tmp);
	}

	for (const auto& bt : btlist)
	{
		std::cout << std::format("pl = {}, rawid = {}, ph = {}, ax = {}, ay = {}, x = {}, y = {}, z = {}\n",
								 			bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y, bt.z);
	}
}