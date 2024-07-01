#include <fstream>
#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <sstream>

int main()
{
	// std::ofstreamを使ってテキストファイルに書き込むことができます。
	std::ofstream ofs("output.txt");
	if (!ofs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	for (int line = 1; line < 10; ++line)
	{
		int a = line * 10 + 1;
		int b = line * 10 + 2;
		double c = line + 0.3;
		double d = line + 0.4;
		ofs << a << " " << b << " " << c << " " << d << "\n";
	}

	for (int line = 10; line < 20; ++line)
	{
		int a = line * 10 + 1;
		int b = line * 10 + 2;
		double c = line + 0.3;
		double d = line + 0.4;
		std::print(ofs, "{:>4} {:>4} {:>6.2f} {:>6.2f}\n", a, b, c, d);
	}
}