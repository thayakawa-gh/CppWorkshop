#include <iostream>
#include <vector>
#include <algorithm>

class Basetrack
{
public:
	Basetrack()
		: pl(0), rawid(0), ph(0), ax(0), ay(0), x(0), y(0), z(0)
	{}
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
	virtual ~CutBase() = default;
	virtual bool Judge(const Basetrack& tracks) const = 0;
};
class PHCut : public CutBase
{
public:
	PHCut(int ph_thresshold_)
		: ph_thresshold(ph_thresshold_)
	{}
	virtual ~PHCut() = default;

	virtual bool Judge(const Basetrack& tracks) const override
	{
		return int(tracks.ph / 10000) >= ph_thresshold;
	}

	int ph_thresshold;
};
class AngCut : public CutBase
{
public:
	AngCut(double ang_min_, double ang_max)
		: ang_min(ang_min_), ang_max(ang_max)
	{}
	virtual ~AngCut() = default;

	virtual bool Judge(const Basetrack& tracks) const override
	{
		double ang = std::hypot(tracks.ax, tracks.ay);
		return ang >= ang_min && ang < ang_max;
	}

	double ang_min, ang_max;
};
std::vector<Basetrack> CutTracks(const std::vector<Basetrack>& tracks, const std::unique_ptr<CutBase>& cut)
{
	std::vector<Basetrack> result;
	size_t size = result.size();
	for (const Basetrack& track : tracks)
	{
		if (cut->Judge(track))
		{
			result.push_back(track);
		}
	}
	return result;
}

int maijhrn()
{
	// こちらのCutTracksは、どのようなカットを行うかを内部では定義していません。
	// あくまで、引数として受け取ったcutの仮想関数越しに判断させています。

	std::vector<Basetrack> btlist;
	// ... btlistにtrackを追加する処理

	std::unique_ptr<CutBase> ph_cut = std::make_unique<PHCut>(10);
	std::vector<Basetrack> btlist_ph_over_10 = CutTracks(btlist, ph_cut);// PHが10以上のtrackだけを抽出

	std::unique_ptr<CutBase> ang_cut = std::make_unique<AngCut>(0.2, 0.4);
	std::vector<Basetrack> btlist_id_1_10_100 = CutTracks(btlist, ang_cut);// radial angleが0.2-0.4のtrackだけを抽出

	return 0;
}

/* 問題
 1. xmin、xmax、ymin、ymaxを指定して矩形にカットするPosCutクラスを作成してください。
 
 2. Lecture-04bで示したように、派生クラスは基底クラスのポインタで指し示すことができます。
    ということは、例えばCutBaseの派生クラスをstd::vector<std::unique_ptr<CutBase>>にいくつも格納することもできます。
    std::vector<std::unique_ptr<CutBase>> cuts;
    cuts.push_back(std::make_unique<PHCut>(10));
    cuts.push_back(std::make_unique<PosCut>(30000.0, 40000.0, 120000.0, 130000.0));
    cuts[0]->Judge(track);// PHCut::Judgeが呼ばれます。

    これを使って、CutTracks関数を「任意の複数の条件をすべて満たす飛跡を抽出する」ように書き換えてみましょう。
    また、Lecture-04のbasetracks.txtに対して以下の条件を適用し、実際に任意の組み合わせのカットが機能するかを確認してみましょう。
    PH>=19
    0.0 <= radial angle < 0.4
    30000.0 <= x < 40000.0 && 40000.0 <= y < 50000.0
    この条件下では6本のBasetrackが生き残ると思います。

    その他、自分で自由に条件を組み合わせて、動作を見てみましょう。
*/