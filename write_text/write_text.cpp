#include <fstream>
#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <sstream>

int main()
{
	// read_textと同じように、ファイルを読み込んでいます。
	std::ifstream ifs("text.txt");
	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	int a, b;
	double c, d;
	std::string buf;

	while (std::getline(ifs, buf))
	{
		std::istringstream iss(buf);
		iss >> a >> b >> c >> d;
		std::cout << std::format("a = {}, b = {}, c = {}, d = {}\n", a, b, c, d);
	}
}