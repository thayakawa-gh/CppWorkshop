#include <format>
#include <iostream>

class Basetrack
{
public:
	Basetrack()
		: pl(0), rawid(0), ph(0), ax(0.0), ay(0.0), x(0.0), y(0.0), z(0.0)
	{}
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}

	Basetrack(const Basetrack& bt)
		: pl(bt.pl), rawid(bt.rawid), ph(bt.ph), ax(bt.ax), ay(bt.ay), x(bt.x), y(bt.y), z(bt.z)
	{}
	~Basetrack()
	{}
	Basetrack& operator=(const Basetrack& bt)
	{
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

	double GetRadialAngle() const
	{
		return std::sqrt(ax * ax + ay * ay);
		//return std::hypot(ax, ay);�ł��悢�B
	}
	int GetPH() const
	{
		return (int)(ph / 10000);
	}
	int GetVPH() const
	{
		return (int)(ph % 10000);
	}

	void SetAngle(double ax_, double ay_)
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

int main()
{
	// bt1���������B��������̃R���X�g���N�^���Ă΂��B
	Basetrack bt1(30, 12345, 250128, -0.1454, 2.6841, 235616.1, 96732.4, 0.0);

	std::cout << std::format("Radial angle: {}\n", bt1.GetRadialAngle());
	std::cout << std::format("PH: {}\n", bt1.GetPH());
	std::cout << std::format("VPH: {}\n", bt1.GetVPH());
}

/* ���
Lecture-02a�A02b�ō쐬����Microtrack��������Basetrack�N���X�̒��ɁAbase-micro�p�x�����v�Z���ĕԂ��֐���ǉ����Ă݂܂��傤�B

*/