#include <format>
#include <string>
#include <vector>
#include <map>
#include <iostream>

std::string Replace(std::string str)
{
	size_t pos = str.find("Bonjour");
	if (pos != std::string::npos)
		str.replace(pos, 7, "Buon giorno");//Bonjourは7文字なので、7を指定。
	return str;

}

int main()
{
	// format
	int pl = 25;
	int64_t rawid = 12345;
	int ph = 220142;
	double ax = 0.2446;
	double ay = -1.5907;
	double x = 12605.2;
	double y = 190451.0;
	std::cout << std::format("{:0>3} {:>10} {:>6} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n", pl, rawid, ph, ax, ay, x, y);


	// string
	std::string test1 = "Hello Hola Bonjour Merhaba";
	std::string test2 = "Hej Hallo";
	std::cout << Replace(test1) << "\n";
	std::cout << Replace(test2) << "\n";

	return 0;
}