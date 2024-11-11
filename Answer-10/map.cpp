#include <iostream>
#include <format>
#include <map>
#include <string>

int main()
{
	std::map<std::string, int> shu;
	shu.insert(std::make_pair("�Δj��", 221));
	shu.insert(std::make_pair("��c���F", 151));
	shu.insert(std::make_pair("�n��L�K", 38));
	shu.insert(std::make_pair("�ʖؗY��Y", 28));
	shu.insert(std::make_pair("�R�{���Y", 9));
	shu.insert(std::make_pair("�c���q�q", 8));
	shu.insert(std::make_pair("�g�ǏB�i", 4));
	shu.insert(std::make_pair("�_�J�@��", 3));
	shu.insert(std::make_pair("�͑�������", 3));

	std::map<std::string, int> san;
	san.insert(std::make_pair("�Δj��", 142));
	san.insert(std::make_pair("��c���F", 46));
	san.insert(std::make_pair("�n��L�K", 18));
	san.insert(std::make_pair("�ʖؗY��Y", 11));
	san.insert(std::make_pair("�c���q�q", 11));
	san.insert(std::make_pair("�R�{���Y", 5));
	san.insert(std::make_pair("�ɓ��F�b", 1));
	san.insert(std::make_pair("�_�J�@��", 1));
	san.insert(std::make_pair("�����M��", 1));
	san.insert(std::make_pair("�g�ǏB�i", 1));
	san.insert(std::make_pair("�Ζؕq�[", 1));

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