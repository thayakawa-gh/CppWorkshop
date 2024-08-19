#include <iostream>
#include <fstream> // <-- std::ifstream���g�����߂ɕK�v
#include <format>
#include <string>
#include <sstream> // <-- std::istringstream���g�����߂ɕK�v

int main()
{
	std::ifstream ifs("text.txt"); // �J�����g�f�B���N�g���ɂ���text.txt���J���܂��B
	// ���̂悤�Ƀt�@�C���̐��/���΃p�X���w�肷�邱�Ƃ��ł��܂��B
	// std::ifstream ifs("C:/folder1/folder2/text.txt");

	// �t�@�C�������݂��邩�A�J�����Ƃ��ł��邩���`�F�b�N���Ă��܂��B
	if (!ifs)
	{
		// �t�@�C�����J���̂Ɏ��s�����ꍇ�́A�G���[���b�Z�[�W���o�͂��ďI�����܂��B
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}

	int a, b;
	double c, d;
	std::string buf;

	// std::getline��ifs����1�s���̕������ǂݍ��݁Abuf�Ɋi�[���Ă��܂��B
	// while����for���Ƃ͈قȂ郋�[�v�\���ŁA���������^�̊ԃ��[�v���J��Ԃ����̂ł��B
	// for (; std::getline(ifs, buf); )�Ɠ����B
	while (std::getline(ifs, buf))
	{
		// buf�ɂ�"11 12 1.3 1.4"�̂悤�ɁA1�s���̕����񂪓����Ă��܂��B
		// ���̕�������󔒕����ŋ�؂�A���ꂼ��̕�����>>��p���ĕϐ�a�`d�Ɋi�[���Ă��܂��B
		std::istringstream iss(buf);
		iss >> a >> b >> c >> d;
		std::cout << std::format("a = {}, b = {}, c = {}, d = {}\n", a, b, c, d);
	}
}

/*
 ���
 basetrack.txt�ɁA�ȉ��̂悤��1�s������1�{�A�S20�{��Basetrack�̏�񂪋L�^����Ă��܂��B
 067    123456 240105  0.2376  1.5982  126489.1  166005.3       0.0
 ������ABasetrack��pl�Arawid�Aph�Aax�Aay�Ax�Ay�Az�ł��B
 �����O��̕׋���ō쐬����Basetrack�N���X�ɓǂݍ��݁A�S�Ă�Basetrack����std::vector<Basetrack>�Ɋi�[���Ă݂܂��傤�B
 ���̌�A�������ǂݍ��߂����m�F���邽�߂ɁA�S�Ă�Basetrack����for���[�v��std::cout/std::print�����g���ĉ�ʂɕ\�����Ă݂܂��傤�B

 �q���g:

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

int main()
{
	??????
	Basetrack tmp;
	std::vector<Basetrack> btlist;
	while (??????)
	{
		??????
 		btlist.push_back(tmp);
	}
	??????
}
*/