#include <format>
#include <iostream>

class Microtrack
{
public:
	Microtrack()
		: pos(0), rawid(0), ph(0), ax(0.0), ay(0.0)
	{
		std::cout << "microtrack default constructor" << std::endl;
	}
	Microtrack(int pos, int64_t rawid, int ph, double ax, double ay)
		: pos(pos), rawid(rawid), ph(ph), ax(ax), ay(ay)
	{
		std::cout << "microtrack constructor" << std::endl;
	}
	Microtrack(const Microtrack& mt)
		: pos(mt.pos), rawid(mt.rawid), ph(mt.ph), ax(mt.ax), ay(mt.ay)
	{
		std::cout << "microtrack copy constructor" << std::endl;
	}
	~Microtrack()
	{
		std::cout << "microtrack destructor" << std::endl;
	}
	Microtrack& operator=(const Microtrack& mt)
	{
		std::cout << "microtrack assignment operator" << std::endl;
		pos = mt.pos;
		rawid = mt.rawid;
		ph = mt.ph;
		ax = mt.ax;
		ay = mt.ay;
		return *this;
	}

	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
};

class Basetrack
{
public:
	Basetrack()
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)//mt�𖾎��I�ɏ��������Ȃ��ꍇ�A�����Microtrack�̃f�t�H���g�R���X�g���N�^���Ă΂��B
	{
		std::cout << "basetrack default constructor" << std::endl;
	}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)//mt�𖾎��I�ɏ��������Ȃ��ꍇ�A�����Microtrack�̃f�t�H���g�R���X�g���N�^���Ă΂��B
	{
		std::cout << "basetrack constructor 1" << std::endl;
	}
	Basetrack(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z,
		int pos_m1, int64_t rawid_m1, int ph_m1, double ax_m1, double ay_m1,
		int pos_m2, int64_t rawid_m2, int ph_m2, double ax_m2, double ay_m2)
		: pl(pl), rawid(rawid), ph(ph), ax(ax), ay(ay), x(x), y(y), z(z),
		mt{ { pos_m1, rawid_m1, ph_m1, ax_m1, ay_m1 }, { pos_m2, rawid_m2, ph_m2, ax_m2, ay_m2 } }
	{
		std::cout << "basetrack constructor 2" << std::endl;
	}

	Basetrack(const Basetrack& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z),
		mt{ bt.mt[0], bt.mt[1] }
	{
		std::cout << "basetrack copy constructor" << std::endl;
	}
	~Basetrack()
	{
		std::cout << "basetrack destructor" << std::endl;
	}
	Basetrack& operator=(const Basetrack& bt)
	{
		std::cout << "basetrack assignment operator" << std::endl;
		pl = bt.pl;
		rawid = bt.rawid;
		ph = bt.ph;
		ax = bt.ax;
		ay = bt.ay;
		x = bt.x;
		y = bt.y;
		z = bt.z;
		mt[0] = bt.mt[0];
		mt[1] = bt.mt[1];
		return *this;
	}

	// ���[�u�R���X�g���N�^�ƃ��[�u������Z�q�͊T�O����₱�������߁A����͏ȗ�����B
	// ���[�u�Z�}���e�B�N�X�̉񂪗����炻�̎��ɁB

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
	Microtrack mt[2];
};

/*
 #####�R���X�g���N�^�ƃf�X�g���N�^#####
 �R���X�g���N�^�̓N���X�̃C���X�^���X�����������Ƃ��ɌĂ΂�����Ȋ֐��ŁA�C���X�^���X�̏�������S���B
 �f�X�g���N�^�͂��̋t�ŁA�C���X�^���X����������Ƃ��ɌĂ΂�A�C���X�^���X�̒��g�̌�n�����s���B
 ��) �C���X�^���X�Ƃ́A���炩�̃N���X��ϐ��^�̎��̂̂��ƁBBasetrack bt;�̂悤�ɐ錾�����Ƃ��A"bt"��Basetrack�N���X�̃C���X�^���X�ł���B

 �R���X�g���N�^�ɂ���������ނ�����B

 * �f�t�H���g�R���X�g���N�^
 �����������Ȃ��R���X�g���N�^�B�����Ȃ��ŃC���X�^���X�𐶐�����Ƃ��ɌĂ΂��B
 �Ⴆ�΁ABasetrack bt;�̂悤�ɏ����ƁABasetrack�N���X�̃f�t�H���g�R���X�g���N�^���Ă΂��B

 * ��������R���X�g���N�^
 ���炩�̈��������A����炩��C���X�^���X������������R���X�g���N�^�B

 * �R�s�[�R���X�g���N�^
 ���̃C���X�^���X�������Ɏ��R���X�g���N�^�B�C���X�^���X�̃R�s�[�𐶐�����Ƃ��ɌĂ΂��B
 Basetrack bt2(bt);�̂悤�ɂ���ƁAbt2��Basetrack�N���X�̃R�s�[�R���X�g���N�^�ɂ���ď����������B

 * �R�s�[������Z�q
 �R�s�[�R���X�g���N�^�Ǝ��Ă��邪�A������Z�q�͊��ɏ��������ꂽ�C���X�^���X�ɐV���ȃC���X�^���X���đ������Ƃ��ɌĂ΂��B

 * �f�X�g���N�^
 �C���X�^���X���j�������Ƃ��ɌĂ΂��֐��B�C���X�^���X�̌�n�����s���B


 ��������̃R���X�g���N�^�ȊO�́A�R���p�C���̎��������𗊂��Ă��悢�B
 �R�s�[�R���X�g���N�^��R�s�[������Z�q������`�̏ꍇ�A
 �R���p�C���͎����I��"�S�ʏ�ϐ����R�s�[����"�����̃R�s�[�R���X�g���N�^/������Z�q�𐶐�����B
 �f�X�g���N�^�����l�ɁA"�S�ʏ�ϐ��̃f�X�g���N�^���Ă�"�����̃f�X�g���N�^�𐶐�����B
*/
int main()
{
	// bt1���������B�f�t�H���g�R���X�g���N�^���Ă΂��B
	Basetrack bt1;

	std::cout << "----------------\n";

	// bt1���������B��������̃R���X�g���N�^���Ă΂��B
	Basetrack bt2(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	std::cout << "----------------\n";

	// bt2���������B�R�s�[�R���X�g���N�^�ɂ����bt1�̒l���R�s�[�����B
	Basetrack bt3(bt2);

	std::cout << "----------------\n";

	// bt3��bt2�̒l�����B������Z�q���Ă΂��B
	bt3 = bt2;

	std::cout << "----------------\n";

	Basetrack bt4(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0,
		251, 123456, 130077, -0.1571, 2.5793,
		252, 123456, 120051, -0.1322, 2.8038);

	std::cout << "----------------\n";

	// main�֐��𔲂���Ƃ��A�p�ς݂ƂȂ���bt1�`bt4�̃f�X�g���N�^���Ă΂��B
	return 0;
}