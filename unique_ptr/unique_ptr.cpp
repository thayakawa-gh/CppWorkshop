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
	std::cout << "\n------std::unique_ptr------\n";
	// std::unique_ptr��p�������I�������m�ہB
	// std::unique_ptr�́A���[�U�[�������I��delete�����Ƃ��A�f�X�g���N�^���Ă΂��Ƃ��Ɋm����delete���Ă����A���S�ȃ|�C���^�ł��B
	std::unique_ptr<Basetrack> uptr1 = std::make_unique<Basetrack>(26, 67890, 200085, 0.2541, -1.6531, 12316.2, 191893.3, 10802.3);

	// std::make_unique�ŏ��������Ȃ��ꍇ�Astd::unique_ptr��nullptr�ɂȂ�܂��B
	std::unique_ptr<Basetrack> uptr2;
	if (uptr2 == nullptr) // if (!ptr2) �ł������Ӗ��ł��B
	{
		std::cout << "ptr2 is nullptr\n";
	}
	// std::make_unique�Ŋ�����std::unique_ptr�����������Ă��\���܂���B
	// ���̂Ƃ��A�����������ptr2��nullptr�łȂ��ꍇ�Aptr2�̒��g�͎����I��delete����܂��B
	uptr2 = std::make_unique<Basetrack>(27, 67891, 200086, 0.2542, -1.6532, 12316.3, 191893.4, 10802.4);
	if (uptr2 != nullptr) // if (ptr2) �ł������Ӗ��ł��B
	{
		std::cout << std::format("ptr2 is not nullptr, rawid == {}\n", uptr2->pl);
	}
	uptr2 = std::make_unique<Basetrack>(26, 67890, 200085, 0.2541, -1.6531, 12316.2, 191893.3, 10802.3);
	// std::unique_ptr�̓R�s�[�ł��܂���BBasetrackPair�Ɠ������A�R�s�[�R���X�g���N�^�E�R�s�[������Z�q��delete����Ă��邽�߂ł��B
	// uptr2 = uptr1; //... �R���p�C���G���[

	// std::unique_ptr��delete����K�v������܂���B�X�R�[�v{}�𔲂���Ƃ��ɏ����delete����܂��B
	// �������Areset�֐��ɂ���Ė����I��delete���邱�Ƃ��ł��܂��B
	// ���̏ꍇ�Astd::unique_ptr��nullptr�ɂȂ�܂��B
	uptr1.reset();
	if (uptr1 == nullptr)
	{
		std::cout << "ptr1 is nullptr\n";
	}
}

/*
 ���
 new_delete.cpp��BasetrackPair�N���X��std::unique_ptr���g���ď��������Ă��������B
 �܂��ABasetrackPair�̃R�s�[�R���X�g���N�^�ƃR�s�[������Z�q���ABasetrack�𕡐�����悤�ɐV���ɒ�`���Ă��������B
 �Ō�ɁA���ۂ�BasetrackPair���R�s�[���Ă݂āA�R�s�[���ƃR�s�[��Ŋe�����o�ϐ��̒l����v���邱�ƁA
 ���҂̃A�h���X���قȂ邱�Ƃ��m�F���Ă��������B
 �Ȃ��A�X�}�[�g�|�C���^�̃A�h���X��ptr.get()�Ŏ擾�ł��܂��B
 �킴�킴get()�Ŏ擾���Ȃ��Ƃ��A==���Z�q�Œ��ڔ�r���邱�ƂŃA�h���X�̈�v���m�F���邱�Ƃ��ł��܂��B

*/