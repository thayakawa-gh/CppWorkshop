#include <format>
#include <string>
#include <vector>
#include <map>
#include <iostream>

std::string Replace(std::string str)
{
	size_t pos = str.find("Bonjour");
	if (pos != std::string::npos)
		str.replace(pos, 7, "Buon giorno");//Bonjour‚Í7•¶š‚È‚Ì‚ÅA7‚ğw’èB
	return str;

}
bool IsPrime(int n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; i * i <= n; i += 2)
	{
		if (n % i == 0) return false;
	}
	return true;
}

int main()
{
	// Lecture-01a
	int pl = 25;
	int64_t rawid = 12345;
	int ph = 220142;
	double ax = 0.2446;
	double ay = -1.5907;
	double x = 12605.2;
	double y = 190451.0;
	std::cout << std::format("{:0>3} {:<10} {:<6} {:<7.4f} {:<7.4f} {:<9.1f} {:<9.1f}\n", pl, rawid, ph, ax, ay, x, y);


	// Lecture-01b
	std::string test1 = "Hello Hola Bonjour Merhaba";
	std::string test2 = "Hej Hallo";
	std::cout << Replace(test1) << "\n";
	std::cout << Replace(test2) << "\n";


	// Lecture-01c
	std::vector<int> v;
	for (int i = 0; i <= 30; ++i)
	{
		if (IsPrime(i))
		{
			v.push_back(i);
		}
	}
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
}