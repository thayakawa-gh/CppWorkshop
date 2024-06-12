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

std::vector<Basetrack> PHCut(const std::vector<Basetrack>& tracks, int ph_min)
{
	std::vector<Basetrack> result;
	for (int i = 0; i < tracks.size(); ++i)
	{
		const Basetrack& track = tracks[i];
		if (track.ph >= ph_min)
		{
			result.push_back(track);
		}
	}
	return result;
}
std::vector<Basetrack> IDCut(const std::vector<Basetrack>& tracks, const std::vector<int64_t>& rawid_list)
{
	std::vector<Basetrack> result;
	for (int i = 0; i < tracks.size(); ++i)
	{
		const Basetrack& track = tracks[i];
		if (std::binary_search(rawid_list.begin(), rawid_list.end(), track.rawid))
		{
			result.push_back(track);
		}
	}
	return result;
}
std::vector<Basetrack> AngCut(const std::vector<Basetrack>& tracks, double ang_min, double ang_max)
{
	std::vector<Basetrack> result;
	for (int i = 0; i < tracks.size(); ++i)
	{
		const Basetrack& track = tracks[i];
		double ang = std::sqrt(track.ax * track.ax + track.ay * track.ay);
		if (ang >= ang_min && ang <= ang_max)
		{
			result.push_back(track);
		}
	}
	return result;
}

int main()
{
	std::vector<Basetrack> btlist;

	// ... btlist��track��ǉ����鏈��

	std::vector<Basetrack> btlist_ph = PHCut(btlist, 10);// PH��10�ȏ��track�����𒊏o

	std::vector<int64_t> rawid_list = { 12345, 67890, 23456, 78901 };
	std::vector<Basetrack> btlist_id = IDCut(btlist, rawid_list);// rawid��rawid_list�Ɋ܂܂�Ă���track�����𒊏o

	std::vector<Basetrack> btlist_ang = AngCut(btlist, 0.2, 0.4);// �p�x��0.0�ȏ�0.2������track�����𒊏o

	// PHCut�AIDCut�AAngCut��if���ɂ�锻��ȊO�͑S�������B�Ȃ̂ɁA�킴�킴3�̊֐��ɕ����Ē�`���Ă���B
	// ��������ƐF�X�ȃJ�b�g�������o�Ă����Ƃ��ɁA���ꂼ��̃J�b�g�����ɑΉ�����֐������̂͑�ρB
	// ��̊֐��ɂ܂Ƃ߂邱�Ƃ͏o���Ȃ����낤���H
}
