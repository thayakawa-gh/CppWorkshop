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
	for (const Basetrack& t : tracks)
	{
		if (int(t.ph / 10000) >= ph_min)
		{
			result.push_back(t);
		}
	}
	return result;
}
std::vector<Basetrack> AngCut(const std::vector<Basetrack>& tracks, double ang_min, double ang_max)
{
	std::vector<Basetrack> result;
	for (const Basetrack& t : tracks)
	{
		double ang = std::sqrt(t.ax * t.ax + t.ay * t.ay);
		if (ang >= ang_min && ang <= ang_max)
		{
			result.push_back(t);
		}
	}
	return result;
}
std::vector<Basetrack> IDCut(const std::vector<Basetrack>& tracks, const std::vector<int64_t>& ids)
{
	std::vector<Basetrack> result;
	for (const Basetrack& t : tracks)
	{
		bool found = false;
		for (int64_t id : ids)
		{
			if (t.rawid == id)
			{
				found = true;
				break;
			}
		}
		if (!found) result.push_back(t);
	}
	return result;
}

int mawefin()
{
	std::vector<Basetrack> btlist;

	// ... btlistにtrackを追加する処理

	std::vector<Basetrack> btlist_ph = PHCut(btlist, 20);// PHが20以上のtrackだけを抽出

	std::vector<Basetrack> btlist_ang = AngCut(btlist, 0.2, 0.4);// 角度が0.0以上0.2未満のtrackだけを抽出

	std::vector<int64_t> ids = { 123456, 234567, 345678, 456789, 567890 };
	std::vector<Basetrack> btlist_id = IDCut(btlist, ids);// rawidがidsに含まれるtrackを除去

	return 0;

	// PHCut、AngCutはif文による判定以外は全く同じ。なのに、わざわざ3つの関数に分けて定義しています。
	// 今後もっと色々なカット条件が出てきたときに、それぞれのカット条件に対応する関数を作るのは大変でしょう。
	// 今回は単一のforループを回すだけのシンプルな処理なので、コピペしてもそれほど問題はないかもしれませんが、
	// 例えばlinkletを作るときに、接続先PLの特定のエリアだけを抜き出し、それらとの接続判定のための二重ループを書いて……などとしていくと、
	// 到底コピペする気になれないようなコード量になってきたりします。
	// こういうとき、“カット条件だけを外から与える”ことはできないものでしょうか？
	// ほとんどの共通処理は1個の関数にまとめてしまって、カット部分だけを外から与えることができれば、
	// 今後の拡張性とメンテナンス性が格段に向上するでしょう。
}
