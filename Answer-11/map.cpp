#include <iostream>
#include <format>
#include <map>
#include <string>

int main()
{
	std::map<std::string, int> shu;
	shu.insert(std::make_pair("Î”j–Î", 221));
	shu.insert(std::make_pair("–ì“c‰À•F", 151));
	shu.insert(std::make_pair("”nêLK", 38));
	shu.insert(std::make_pair("‹Ê–Ø—Yˆê˜Y", 28));
	shu.insert(std::make_pair("R–{‘¾˜Y", 9));
	shu.insert(std::make_pair("“c‘º’qq", 8));
	shu.insert(std::make_pair("‹g—ÇBi", 4));
	shu.insert(std::make_pair("_’J@•¼", 3));
	shu.insert(std::make_pair("‰Í‘º‚½‚©‚µ", 3));

	std::map<std::string, int> san;
	san.insert(std::make_pair("Î”j–Î", 142));
	san.insert(std::make_pair("–ì“c‰À•F", 46));
	san.insert(std::make_pair("”nêLK", 18));
	san.insert(std::make_pair("‹Ê–Ø—Yˆê˜Y", 11));
	san.insert(std::make_pair("“c‘º’qq", 11));
	san.insert(std::make_pair("R–{‘¾˜Y", 5));
	san.insert(std::make_pair("ˆÉ“¡FŒb", 1));
	san.insert(std::make_pair("_’J@•¼", 1));
	san.insert(std::make_pair("––¼M‰î", 1));
	san.insert(std::make_pair("‹g—ÇBi", 1));
	san.insert(std::make_pair("–Î–Ø•q[", 1));

	for (std::map<std::string, int>::iterator sanit = san.begin(); sanit != san.end(); ++sanit)
	{
		std::map<std::string, int>::iterator shuit = shu.find(sanit->first);
		if (shuit != shu.end())
		{
			std::cout << sanit->first << " " << sanit->second << " " << shuit->second << std::endl;
		}
		else
		{
			std::cout << sanit->first << " " << sanit->second << " 0" << std::endl;
		}
	}
}