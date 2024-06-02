#include <iostream>// <- std::cout���g�����߂ɕK�v�B
#include <format>// <- std::format���g�����߂ɕK�v�B
#include <print>// <- std::print���g�����߂ɕK�v�B

int main()
{
	//printf�͂����Â��B
	//C++�ł�std::cout��std::format���g�����B

	char hello[] = "Hello";
	char world[] = "World";
	std::cout << hello << " " << world << "!\n";

	std::cout << std::format("{} {}!\n", hello, world);

	// ����
	int i = 1;
	std::cout << std::format("i == {}\n", i);
	std::cout << std::format("i == {:0>3}\n", i);// 0���߁A�E�񂹁A3��

	// ���������_
	double d = 3.141592653589793;
	std::cout << std::format("pi == {}\n", d);
	std::cout << std::format("pi == {:>4.2f}\n", d);// �E�񂹁A��4�A�����_�ȉ�2���Af�͎w���\�L�����Ȃ����Ƃ𖾎��B

	// std::cout << std::format���g������ɁAstd::print���g�����Ƃ��ł���B
	std::print("pi == {:>6.4f}\n", d);

	// std::format�Astd::print�͂ǂ�����������N�̊Ԃɓ������ꂽ�V�����@�\�̂��߁A�Â��R���p�C���ł͎g���Ȃ����Ƃ�����B
	// std::format���g���ɂ�Visual Studio 2019�ȍ~���K�v�ŁAC++����W����/std:c++20�܂���/std:c++latest�ɐݒ肷��K�v������B
	// std::print���g���ɂ�Visual Studio 2022 Update 7�ȍ~���K�v�A����C++����W����/std:c++latest�ɐݒ肷��K�v������B
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
����Basetrack�̏����A
pl:0���ߕ�3�Arawid:��10�Aph:��6�Aaxay:��7�ŏ�����4�ʂ܂ŁAxyz:��9�ŏ�����1�ʂ܂�
�Ƃ����t�H�[�}�b�g�ŕ\�������Ă݂܂��傤�B
���̂悤�ɕ\�����ꂽ�琳���ł��B
025      12345 220142  0.2446 -1.5907   12605.2  190451.0
*/