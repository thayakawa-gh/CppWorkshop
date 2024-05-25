#include <format>
#include <iostream>

class Basetrack
{
public:
	Basetrack()
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)
	{
		std::cout << "default constructor" << std::endl;
	}
	Basetrack(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z)
		: pl(pl), rawid(rawid), ph(ph), ax(ax), ay(ay), x(x), y(y), z(z)
	{
		std::cout << "constructor" << std::endl;
	}

	Basetrack(const Basetrack& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z)
	{
		std::cout << "copy constructor" << std::endl;
	}
	~Basetrack()
	{
		std::cout << "destructor" << std::endl;
	}
	Basetrack& operator=(const Basetrack& bt)
	{
		std::cout << "assignment operator" << std::endl;
		pl = bt.pl;
		rawid = bt.rawid;
		ph = bt.ph;
		ax = bt.ax;
		ay = bt.ay;
		x = bt.x;
		y = bt.y;
		z = bt.z;
		return *this;
	}

	// ���[�u�R���X�g���N�^�ƃ��[�u������Z�q�͊T�O����₱�������߁A����͏ȗ�����B
	// ���[�u�Z�}���e�B�N�X�̉񂪗����炻�̎��ɁB

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

int main()
{
	// bt1���������B��������̃R���X�g���N�^���Ă΂��B
	Basetrack bt1(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	// bt2���������B�R�s�[�R���X�g���N�^�ɂ����bt1�̒l���R�s�[�����B
	Basetrack bt2(bt1);

	// main�֐��𔲂���Ƃ��A�p�ς݂ƂȂ���bt1, bt2�̃f�X�g���N�^���Ă΂��B
}