#include <iostream>// <- std::cout���g�����߂ɕK�v�B
#include <format>// <- std::format���g�����߂ɕK�v�B
#include <print>// <- std::println���g�����߂ɕK�v�B

int main()
{
	// C�����Hello World
	printf("Hello World!");


	//printf�͂����Â��B
	//C++�ł�std::cout��std::format���g�����B

	char hello[] = "Hello";
	char world[] = "World";
	std::cout << hello << " " << world << "!\n";

	std::cout << std::format(" {}!\n", hello, world);

	// ����
	int i = 1;
	std::cout << std::format("i == {}\n", i);//
	std::cout << std::format("i == {:0>3}\n", i);// 0���߁A�E�񂹁A3��
	//i == 003
	// 
	// ���������_
	double d = 3.141592653589793;
	std::cout << std::format("pi == {}\n", d);
	std::cout << std::format("pi == {:>4.2f}\n", d);// �E�񂹁A��4�A�����_�ȉ�2���Af�͎w���\�L�����Ȃ����Ƃ𖾎��B

	// std::cout << std::format���g������ɁAstd::print��std::println���g�����Ƃ��ł���B
	std::println("pi == {:>6.4f}", d);

	// std::format�Astd::println�͂ǂ�����������N�̊Ԃɓ������ꂽ�V�����@�\�̂��߁A�Â��R���p�C���ł͎g���Ȃ����Ƃ�����B
	// std::format���g���ɂ�Visual Studio 2019 16.10�ȍ~���K�v�ŁAC++����W����/std:c++20�܂���/std:c++latest�ɐݒ肷��K�v������B
	// std::println���g���ɂ�Visual Studio 2022 17.7�ȍ~���K�v�A����C++����W����/std:c++latest�ɐݒ肷��K�v������B

	return 0;
}

/* ���
int pl = 25;
int64_t rawid = 12345;
int ph = 220142;
double ax = 0.2446;
doulbe ay = -1.5907;
double x = 12605.2;
double y = 190451.0;
��L�̂悤�ȏ�������Basetrack������܂��B
����Basetrack�̏����A��������E�񂹂ŁA
pl:0���ߕ�3�Arawid:��10�Aph:��6�Aaxay:��7�ŏ�����4�ʂ܂ŁAxyz:��9�ŏ�����1�ʂ܂�
�Ƃ����t�H�[�}�b�g�ŕ\�������Ă݂܂��傤�B
���̂悤�ɕ\�����ꂽ�琳���ł��B
025      12345 220142  0.2446 -1.5907   12605.2  190451.0
*/