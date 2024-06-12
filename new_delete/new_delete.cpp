#include <iostream>
#include <format>

class Basetrack
{
public:
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}

	double GetAng() const { return std::sqrt(ax * ax + ay * ay); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};

/*
 #####�X�^�b�N�̈�ƃq�[�v�̈�#####
 �X�^�b�N�̈�̓v���O�������s���ɂ��炩���ߊ��蓖�Ă��郁�����̈�B
 �Ⴆ��int x = 4;�̂悤�Ƀ��[�J���ȕϐ���錾����ƁA�����̓X�^�b�N�̈�Ɋ��蓖�Ă��A�֐��𔲂���Ƃ��ȂǂɎ����I�ɊJ�������B
 �X�^�b�N�̈�̓������̊��蓖�Ă����������ł��邪�A���蓖�Ă��郁�����̃T�C�Y�̓R���p�C�����Ɍ��܂�i���ʂ͐�MB�j���߁A
 ���s���Ƀ������̃T�C�Y��ύX���邱�Ƃ͂ł��Ȃ����A����Ȕz��Ȃǂ��i�[���邱�Ƃ��o���Ȃ��B

 �q�[�v�̈�̓v���O�������s���ɕK�v���������I�Ɋm�ۂ���郁�����̈�B
 C����ł��Ȃ��݂�malloc/free�̓q�[�v�̈�Ƀ��������m��/�J������֐��ł���B
 �܂�C++�ɂ�new/delete�Ƃ������Z�q������A������q�[�v�̈�Ƀ��������m��/�J�����邽�߂Ɏg����B
 �X�^�b�N�̈�ƈقȂ�APC�ɓ��ڂ��ꂽ�������e�ʂ̌��E�܂Ń��������g�p���邱�Ƃ��ł���B
 ����A�q�[�v�̈�Ɋm�ۂ��ꂽ��������delete���g���ĉ�����Ȃ��ƃ��������[�N����������ȂǁA�Ǘ�������B
 ����Ƀq�[�v�̈�͊m�ہE�J�����x�����߁A���ՂɎg���ƃv���O�����̑��x�ቺ�Ɍq���肤��B

 ����std::string��std::vector�Astd::map�������I�ɂ̓q�[�v�̈�Ƀ��������m�ۂ��Ă���B
 ���̂��߁A�����͔��ɏ_��ő傫�ȃf�[�^�̊i�[���\�ł��邪�A���̕��������m�ہE�J���̃I�[�o�[�w�b�h������B
 �֐��̈����Ƃ���std::vector�Ȃǂ�n���Ƃ��ɎQ�Ɠn��������̂́A���̃q�[�v�̈�̍Ċm�ۂ�J���̃I�[�o�[�w�b�h������邽�߂ł���B
*/

int main()
{
	// new�ɂ����double�^�̕ϐ����q�[�v�̈�Ɋm�ۂ���B
	double* a = new double(3.14);
	std::cout << *a << "\n";

	// �q�[�v�̈�Ɋm�ۂ������������������Bnew�Ŋm�ۂ�����������delete�ŉ�����Ȃ��ƃ��������[�N����������B
	delete a;

	// �����Ő݌v�����N���X��new�Ŋm�ۂł���B
	// malloc�Ƃ̑傫�ȈႢ�́Anew��"�R���X�g���N�^���Ă�"�Ƃ����_�B
	Basetrack* bt = new Basetrack{ 25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0 };
	// bt�̃����o�ϐ��⃁���o�֐��ɃA�N�Z�X����ɂ̓A���[���Z�q���g���B
	std::cout << std::format("pl = {}, rawid = {}, ra = {}\n", bt->pl, bt->rawid, bt->GetAng());

	delete bt;

	//std::cout << bt->ax << "\n"; // bt�͂���delete����ď��ł��Ă���̂ŁA���̒��g�ɃA�N�Z�X���Ă͂����Ȃ��B
}