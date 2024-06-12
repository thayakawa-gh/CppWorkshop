#include <iostream>
#include <string> // <- std::string�N���X���g�����߂ɕK�v
#include <format>

std::string Replace(std::string str)
{
	size_t pos = str.find("Bonjour");
	if (pos != std::string::npos)
		str.replace(pos, 7, "Buon giorno");//Bonjour��7�����Ȃ̂ŁA7���w��B
	return str;
}

/*
 ##### std::string #####
 std::string��C++�W�����C�u�����Ɋ܂܂��A������������@�\�B
 C�����char�^�z��Ƃ͈قȂ�A=�ɂ�����A==�ł̔�r�A+�ł̌����ȂǂɑΉ����Ă���B
 ������̒������C�ɂ���K�v���Ȃ��A���Ɉ����₷���B

					C����̔z��							C++��std::string
 ������̃R�s�[		strcpy(str, "Hello")				str = "Hello"
 ������̔�r		strcmp(str, "Hello") == 0			str == "Hello"
 ������̌���		strcat(str, " World")				str += " World"
 ������̒���		strlen(str)							str.length()
 ����������̎擾		-									std::string sub = str.substr(3, 2)//3�����ڂ���2�������𒊏o sub == "lo"
 ������̌���		char* pos = strstr(str, "World")	size_t pos = str.find("World")
 ������̒u��		-									str.replace(6, 5, "Everyone")//6�����ڂ���5��������Everyone�ɒu��
*/

int main()
{
	// ������̏�����
	std::string str1 = "Hello";
	std::string str2 = "World";

	// �o��
	std::cout << "str1 : " << str1 << std::endl;
	std::cout << "str2 : " << str2 << std::endl;

	// ������̔�r
	if (str1 == "Hello")
		std::cout << "str1 == \"Hello\" : Yes" << std::endl;


	// ������̌���
	std::string str3 = str1 + " " + str2;
	std::cout << "str3 = str1 + \" \" + str2 : " << str3 << std::endl;

	// ������̒ǉ�
	str3 += "!";
	std::cout << "str3 += \"!\" : " << str3 << std::endl;

	// ����������̒��o
	std::string str4 = str3.substr(6, 5);//Hello World��6�����ڂ���5�������𒊏o�B
	std::cout << "str4 = str3.substr(6, 5) : " << str4 << std::endl;

	// ������̒���
	std::cout << "Length of str3 : " << str3.length() << std::endl;

	// �����̃A�N�Z�X
	char ch = str3[1];
	std::cout << "str3[1] : " << ch << std::endl;

	// ������̌���
	// World�����������ꍇ�Apos�ɂ�'W'�̈ʒu������B
	size_t pos = str3.find("World");
	if (pos != std::string::npos)//std::string::npos�͕����񂪌�����Ȃ������ꍇ�̕Ԃ�l
		std::cout << "str3.find(\"World\") :" << pos << std::endl;
	else
		std::cout << "\"World\" not found" << std::endl;

	// ������̒u��
	// Hello World��6�����ڂ���5��������Everyone�ɒu���B
	str3.replace(6, 5, "Everyone");
	std::cout << "str3.replace(6, 5, \"Everyone\") : " << str3 << std::endl;

	// ������̑}��
	// 5�����ڂ�6�����ڂ̊Ԃ�','��}���B
	str3.insert(5, ",");
	std::cout << "str3.insert(5, \",\") : " << str3 << std::endl;

	// ������̍폜
	// 5�����ڂ��폜�B
	str3.erase(5, 1);
	std::cout << "str3.erase(5, 1) : " << str3 << std::endl;

	// ������̃N���A
	str3.clear();
	std::cout << "str3.clear() : " << str3 << std::endl;
	if (str3.empty())
		std::cout << "str3.empty() : Yes" << std::endl;

	// std::format���g����������̃t�H�[�}�b�g
	str3 = std::format("{} {}", str1, str2);//����std::format��std::string��Ԃ��̂ŁA������̃t�H�[�}�b�g�Ɏg����B
	std::cout << "str3 = std::format(\"{} {}\", str1, str2) : " << str3 << std::endl;


	std::string test1 = "Hello Hola Bonjour Merhaba";
	std::string test2 = "Hej Merhaba";
	std::cout << Replace(test1) << "\n";
	std::cout << Replace(test2) << "\n";
	return 0;
}

/*
���
std::string�^�̕ϐ����󂯎���Ă��̒�����"Bonjour"�Ƃ�����������������A
���������ꍇ��"Buon giorno"�ɒu�����ĕԂ��A�Ƃ����֐�������Ă݂܂��傤�B
find()�Areplace()���g���Ă��������B
std::string Replace(std::string str)
{
	//�����ɏ����������B
	return str;
}

�ȉ���test1�Atest2��^���Ă݂āA���������삵�Ă��邩�m�F���܂��傤�B
std::string test1 = "Hello Hola Bonjour Merhaba";
std::string test2 = "Hej Merhaba";
std::cout << Replace(test1) << "\n";
std::cout << Replace(test2) << "\n";
*/