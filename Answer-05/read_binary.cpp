#include <fstream>
#include <iostream>
#include <vector>
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
	// write_binary.cppを先に実行し、basetracks.datを作成しておいてください。
	std::ifstream ifs("basetracks.dat", std::ios::binary);
	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	ifs.seekg(0, std::ios::end);
	std::streamoff size = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::vector<Basetrack> btlist(size / sizeof(Basetrack));
	ifs.read(reinterpret_cast<char*>(btlist.data()), size);

	for (const auto& bt : btlist)
	{
		std::cout << std::format("pl = {}, rawid = {}, ph = {}, ax = {}, ay = {}, x = {}, y = {}, z = {}\n",
								  bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y, bt.z);
	}
}
