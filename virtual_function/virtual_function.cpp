#include <iostream>
#include <vector>
#include <algorithm>

class Basetrack
{
public:
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};

class CutBase
{
public:
	virtual bool Judge(const Basetrack& tracks) const = 0;
};
class PHCut : public CutBase
{
public:
	PHCut(int ph_thresshold_) : ph_thresshold(ph_thresshold_) {}

	virtual bool Judge(const Basetrack& tracks) const override
	{
		return tracks.ph >= ph_thresshold;
	}

	int ph_thresshold;
};
class IDCut : public CutBase
{
public:
	IDCut(const std::vector<int64_t>& rawid_list_)
		: rawid_list(rawid_list_)
	{
		std::sort(rawid_list.begin(), rawid_list.end());// rawid_list��id�̏����Ƀ\�[�g���Ă���B
	}

	virtual bool Judge(const Basetrack& tracks) const override
	{
		// ���O�ɗ^����rawid_list�Ɋ܂܂�Ă���track�Ȃ�true��Ԃ��B
		return std::binary_search(rawid_list.begin(), rawid_list.end(), tracks.rawid);
	}

	std::vector<int64_t> rawid_list;
};
class AngCut : public CutBase
{
	AngCut(double ang_min_, double ang_max) : ang_min(ang_min_), ang_max(ang_max) {}

	virtual bool Judge(const Basetrack& tracks) const override
	{
		double ang = std::hypot(tracks.ax, tracks.ay);
		return ang >= ang_min && ang < ang_max;
	}

	double ang_min, ang_max;
};

std::vector<Basetrack> CutTracks(const std::vector<Basetrack>& tracks, const CutBase& cut)
{
	std::vector<Basetrack> result;
	for (const auto& track : tracks)
	{
		if (cut.Judge(track))
		{
			result.push_back(track);
		}
	}
	return result;
}

int main()
{
	std::vector<Basetrack> btlist;
	std::vector<Basetrack> btlist_ph_over_10 = CutTracks(btlist, PHCut(10));// PH��10�ȏ��track�����𒊏o

	std::vector<int64_t> rawid_list = { 1, 10, 100 };
	std::vector<Basetrack> btlist_id_1_10_100 = CutTracks(btlist, IDCut(rawid_list));// rawid��1, 10, 100��track�����𒊏o
}

/* ���
 Lecture-04b�Ŏ������悤�ɁA�h���N���X�͊��N���X�̃|�C���^�Ŏw���������Ƃ��ł��܂��B
 �Ƃ������Ƃ́A�Ⴆ��CutBase�̔h���N���X��std::vector<std::unique_ptr<CutBase>>�ɂ������i�[���邱�Ƃ��ł��܂��B
 ������g���āACutTracks�֐����u�C�ӂ̕����̏��������ׂĖ�������Ղ𒊏o����v�悤�ɏ��������Ă݂܂��傤�B

*/