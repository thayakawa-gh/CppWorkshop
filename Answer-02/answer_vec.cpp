#include <vector>
#include <iostream>
#include <format>

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
	// vector 問題1
	std::vector<int> v1;
	for (int i = 0; i <= 30; ++i)
	{
		v1.push_back(i);
	}


	// vector 問題2
	std::vector<int> v2;
	for (int i = 0; i <= 30; ++i)
	{
		if (IsPrime(i))
		{
			v2.push_back(i);
		}
	}
	for (int i = 0; i < v2.size(); ++i)
	{
		std::cout << v2[i] << " ";
	}
	std::cout << "\n";



	// iterator 問題1
	std::vector<int> v3(30);
	int i = 1;
	for (std::vector<int>::iterator it = v3.begin(); it != v3.end(); ++it, ++i)
	{
		*it = i;
	}
	int sum = 0;
	for (std::vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
	{
		sum += *it;
	}
	std::cout << sum << "\n";

	// iterator 問題2
	std::vector<int> v4(30);
	i = 0;
	for (int& x : v4)
	{
		x = i;
		++i;
	}
	sum = 0;
	for (int x : v4)
	{
		sum += x;
	}
	std::cout << sum << "\n";
}