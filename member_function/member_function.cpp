#include <format>
#include <iostream>

class Basetrack
{
public:
	Basetrack() = default; //default�Ƃ���ƁA�R���p�C�����f�t�H���g�R���X�g���N�^��������������B
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}

	double GetRadialAngle() const //<-- const�́u�����o�ϐ���ύX���Ȃ��v�Ƃ����Ӗ�
	{
		return std::sqrt(ax * ax + ay * ay);
		//return std::hypot(ax, ay);�ł��悢�B
	}

	// �錾�ƒ�`�𕪂������ꍇ�B
	int GetPH() const;
	int GetVPH() const;

	void SetAngle(double ax_, double ay_) //<-- �����o�ϐ���ύX����̂�const�͂��Ȃ�
	{
		ax = ax_;
		ay = ay_;
	}

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

// �N���X��`���ł͐錾�݂̂ɂ��āA��`���N���X�X�R�[�v�̊O���ɏ������Ƃ��ł���B
// �R���X�g���N�^�����l�B

int Basetrack::GetPH() const
{
	return (int)(ph / 10000);
}
int Basetrack::GetVPH() const
{
	return (int)(ph % 10000);
}

int main()
{
	// bt1���������B��������̃R���X�g���N�^���Ă΂��B
	Basetrack bt1(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	bt1.SetAngle(bt1.ax * 0.951, bt1.ay * 0.951);

	std::cout << std::format("Radial angle: {}\n", bt1.GetRadialAngle());
	std::cout << std::format("PH: {}\n", bt1.GetPH());
	std::cout << std::format("VPH: {}\n", bt1.GetVPH());
}

/* ���
 Lecture-02a�A02b�ō쐬����Microtrack��������Basetrack�N���X�̒��ɁAbase-micro�p�x�����v�Z���ĕԂ��֐���ǉ����Ă݂܂��傤�B
 ax��ay�A�\�Ȃ�radial�Alateral���ꂼ����B
*/