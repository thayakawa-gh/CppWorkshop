#include <memory>//<---�X�}�[�g�|�C���^���g�����߂ɕK�v�B
#include <iostream>
#include <format>

/*
 ######�X�}�[�g�|�C���^�ɂ���######
 new/delete�̑傫�Ȍ��_�́Anew������������K��delete���Ȃ���΂Ȃ�Ȃ��Ƃ����_�ł��B
 �P���ȃv���O�����Ȃ炻��ȃ~�X�͂��Ȃ���������܂��񂪁A�v���O���������G������Ɛ����ł��̂悤�ȏ������������A
 delete���Y�ꂽ��A�t�ɓ�d��delete���Ă��܂�����Ƃ������o�O���������₷���Ȃ�܂��B

 ���̖����������邽�߂ɁA��r�I�V����C++�ł̓X�}�[�g�|�C���^�Ƃ����@�\����������Ă��܂��B
 �ȒP�Ɍ����΁Adelete���ׂ����������珟���delete���Ă����|�C���^�̂��Ƃł��B
 ���݂ł�new/delete�͎g�킸�A�󋵂ɉ����ăX�}�[�g�|�C���^���g�������邱�Ƃ���������Ă��܂��B

*/

class Basetrack
{
public:

	Basetrack()
	{
		std::cout << "Basetrack constructor\n";
	}
	Basetrack(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z)
		: pl{ pl }, rawid{ rawid }, ph{ ph }, ax{ ax }, ay{ ay }, x{ x }, y{ y }, z{ z }
	{
		std::cout << "Basetrack constructor\n";
	}
	~Basetrack()
	{
		std::cout << "Basetrack destructor\n";
	}

	double GetAng() const { return std::sqrt(ax * ax + ay * ay); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};

int main()
{
	std::cout << "\n------std::shared_ptr------\n";

	// std::shared_ptr��p�������I�������m�ہB
	// std::shared_ptr��std::unique_ptr�Ɠ��l��delete�������I�ɍs���Ă���܂����A
	// std::unique_ptr�ƈقȂ�A������std::shared_ptr�������A�h���X���w�����Ƃ��ł��܂��B
	std::shared_ptr<Basetrack> sptr1 = std::make_shared<Basetrack>(28, 67892, 200087, 0.2543, -1.6533, 12316.4, 191893.5, 10802.5);
	std::shared_ptr<Basetrack> sptr2 = sptr1;
	// ���Asptr1��sptr2�͓���Basetrack�̃A�h���X���w���A����Basetrack�����L������Ԃɂ���܂��B���̂��߁Asptr1��ύX�����sptr2���ύX���ꂽ�悤�Ɍ����܂��B
	sptr1->ax += 0.030;//ax��0.030�����Z
	std::cout << std::format("sptr1->ax == {}, sptr2->ax == {}\n", sptr1->ax, sptr2->ax);

	// std::shared_ptr�͎Q�ƃJ�E���g�Ƃ����ϐ��������Ă��܂��B����́A�����A�h���X���w��std::shared_ptr���������邩���������̂ł��B
	// �Ⴆ�΁Asptr1��sptr2�������A�h���X���w���Ă���̂ŁA�Q�ƃJ�E���g�͂ǂ����2�ł��B
	// use_count�֐��ŎQ�ƃJ�E���g���擾�ł��܂��B
	std::cout << std::format("sptr1.use_count() == {}, sptr2.use_count() == {}\n", sptr1.use_count(), sptr2.use_count());

	// ������sptr2�̕���reset���Ă݂܂��B�����sptr2��sptr1�Ƃ̋��L����������nullptr�ɂȂ�܂����A
	// sptr1���܂�����Basetrack���w�������Ă��邽�߁ABasetrack���̂͂܂�delete����܂���B
	// ����A����Basetrack���Q�Ƃ���shared_ptr��1���������ƂŁAsptr1�̎Q�ƃJ�E���g��1�ɂȂ�܂��B
	sptr2.reset();
	std::cout << std::format("sptr1->ax == {}\n", sptr1->ax);
	std::cout << std::format("sptr1.use_count() == {}, sptr2.use_count() == {}\n", sptr1.use_count(), sptr2.use_count());

	// sptr1��reset����ƁA����Basetrack���w���Ă���shaded_ptr�����݂��Ȃ��Ȃ邽�߁ABasetrack���̂�delete����܂��B
	sptr1.reset();
	std::cout << std::format("sptr1.use_count() == {}, sptr2.use_count() == {}\n", sptr1.use_count(), sptr2.use_count());

	// �Q�ƃJ�E���g�́Areset������Ashared_ptr���X�R�[�v�𔲂��ăf�X�g���N�^���Ă΂ꂽ�肷�邱�ƂŌ������܂��B
	// �Q�ƃJ�E���g��0�ɂȂ������_�ŁA���߂�shared_ptr����������Basetrack��delete���s����̂ł��B

	std::cout << "\n";
}

/*
 ���
 shared_ptr�t�H���_����linklets.txt�Ƃ����t�@�C��������܂��B
 ���̒��ɂ�Linklet�ɂȂ���2�{��Basetrack�̑g�ib0�Ab1�j���A���̃t�H�[�}�b�g�ŋL�^����Ă��܂��B
 pl0 rawid0 ax0 ay0 x0 y0 z0 pl1 rawid1 ax1 ay1 x1 y1 z1
 �i����̃t�@�C����pl0���S��73�Apl1��74�ƂȂ��Ă��܂��B�j
 �����std::shared_ptr�ɓǂݍ���ł݂܂��傤�B
 �܂��ABasetrackPair��std::shared_ptr���g���ď��������Ă��������B���̂Ƃ��R�s�[�R���X�g���N�^�ƃR�s�[������Z�q�͒�`�����f�t�H���g�̂܂܂ɂ��Ă��������B
 ���ɁAlinklets.txt��ǂ݁Astd::vector<BasetrackPair>�Ɋi�[���Ă��������B
 �������A�������ɓǂݍ��܂ꂽBasetrackPair�̒��œ����Basetrack�����݂���ꍇ�Astd::shared_ptr�����L���Ă��������B
 �Ō��use_count�֐����g���āA������Linklet�ɋ��L����Ă��Ȃ�
 �i�܂�1�{��Linklet�ɂ����g�p����Ă��Ȃ��jBasetrack�����{���邩�����Ă݂܂��傤�B
*/