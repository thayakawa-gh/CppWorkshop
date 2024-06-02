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
		std::sort(rawid_list.begin(), rawid_list.end());// rawid_listをidの昇順にソートしている。
	}

	virtual bool Judge(const Basetrack& tracks) const override
	{
		// 事前に与えたrawid_listに含まれているtrackならtrueを返す。
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
	std::vector<Basetrack> btlist_ph_over_10 = CutTracks(btlist, PHCut(10));// PHが10以上のtrackだけを抽出

	std::vector<int64_t> rawid_list = { 1, 10, 100 };
	std::vector<Basetrack> btlist_id_1_10_100 = CutTracks(btlist, IDCut(rawid_list));// rawidが1, 10, 100のtrackだけを抽出
}

/* 問題
 Lecture-04bで示したように、派生クラスは基底クラスのポインタで指し示すことができます。
 ということは、例えばCutBaseの派生クラスをstd::vector<std::unique_ptr<CutBase>>にいくつも格納することもできます。
 これを使って、CutTracks関数を「任意の複数の条件をすべて満たす飛跡を抽出する」ように書き換えてみましょう。

*/