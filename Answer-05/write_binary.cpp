#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <format>

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
		return 1;
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

	std::ofstream ofs("basetracks.dat", std::ios::binary);
	if (!ofs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}
	ofs.write(reinterpret_cast<const char*>(btlist.data()), btlist.size() * sizeof(Basetrack));

	std::cout << std::format("Wrote {} basetracks to basetracks.dat\n", btlist.size());
}
