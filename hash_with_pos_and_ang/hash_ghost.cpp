#include <iostream>
#include <vector>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono> //<- 処理時間計測のために必要。

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

// Basetrack、Microtrackをどちらも扱えるようクラステンプレートにしています。
template <class Track>
class Hash
{
public:

	// 飛跡の座標の最大値、最小値、ビン幅を受け取り、
	// ハッシュテーブルを初期化しておきます。
	Hash(double xmin_, double xmax_, double xwbin_, double ymin_, double ymax_, double ywbin_)
		: xmin(xmin_), ymin(ymin_), xwbin(xwbin_), ywbin(ywbin_), xnbin(0), ynbin(0)
	{
		xnbin = int((xmax_ - xmin) / xwbin) + 1;
		ynbin = int((ymax_ - ymin) / ywbin) + 1;
		table.resize(xnbin * ynbin);
	}

	int GetIndex(int ix, int iy) const
	{
		return ix + iy * xnbin;
	}

	std::pair<int, int> GetIxIy(double x, double y) const
	{
		int ix = int((x - xmin) / xwbin);
		int iy = int((y - ymin) / ywbin);
		return { ix, iy };
	}

	// あるTrackのx, y座標から、ghost判定を行うべきビンのリストを受け取るための関数です。
	// このとき座標x、yを含むビンを中心とする3x3個のビンが選択されます。
	void GetBinList(double x, double y, std::vector<std::pair<int, int>>& binlist) const
	{
		binlist.clear();//clearはvectorの中身をすべて削除しますが、メモリを開放しないので、それほどオーバーヘッドはありません。
		std::pair<int, int> ixiy = GetIxIy(x, y);
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				int ix = ixiy.first + i;
				int iy = ixiy.second + j;
				// 範囲外のビンは無視します。
				if (ix < 0 || ix >= xnbin || iy < 0 || iy >= ynbin) continue;
				binlist.push_back({ ix, iy });
			}
		}
	}

	// あるビンix, iyに含まれる飛跡のリストを取得する関数です。
	const std::vector<Track>& GetTrackList(int ix, int iy) const
	{
		int index = GetIndex(ix, iy);
		return table[index];
	}
	// あるTrackをハッシュテーブルに追加する関数です。
	void Insert(const Track& t)
	{
		std::pair<int, int> ixiy = GetIxIy(t.x, t.y);
		int index = GetIndex(ixiy.first, ixiy.second);
		table[index].push_back(t);
	}

	double xmin;
	double ymin;
	double xwbin;
	double ywbin;
	int xnbin;
	int ynbin;
	std::vector<std::vector<Track>> table;//table[ix + iy * xnbin]にix, iyのビンに含まれる飛跡が格納される。
};

int main()
{
	std::vector<Basetrack> btlist;
	std::ifstream ifs("basetrack_pl49.txt");
	if (!ifs)
	{
		std::cerr << "Error: file not found" << std::endl;
		return 1;
	}
	double xmin = std::numeric_limits<double>::max();//std::numeric_limits<double>::max()はdouble型が取りうる最大値を返します。
	double xmax = -std::numeric_limits<double>::max();
	double ymin = std::numeric_limits<double>::max();
	double ymax = -std::numeric_limits<double>::max();
	std::string buf;
	while (std::getline(ifs, buf))
	{
		// Basetrackの読み込みと座標の最大最小値の取得を同時に行っています。
		Basetrack b;
		std::istringstream iss(buf);
		iss >> b.pl >> b.rawid >> b.ph >> b.ax >> b.ay >> b.x >> b.y >> b.z;
		xmin = std::min(xmin, b.x);
		xmax = std::max(xmax, b.x);
		ymin = std::min(ymin, b.y);
		ymax = std::max(ymax, b.y);
		btlist.push_back(b);
	}

	bool broute_force = true;
	bool hash_table = true;

	std::vector<Basetrack> bf_deleted;
	std::vector<Basetrack> ht_deleted;

	// ここからGhost filter。
	// ハッシュテーブルを用いた高速版と、総当たりによる方式との時間を計測し、
	// どの程度の速度差が生じるかを比較してみます。

	// ghostの判定に用いる許容誤差を設定します。
	double err_x = 10.0;
	double err_y = 10.0;
	double err_ax = 0.02;
	double err_ay = 0.02;

	if (broute_force)
	{
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (const Basetrack& bt1 : btlist)
		{
			bool found = false;
			for (const Basetrack& bt2 : btlist)
			{
				// 自分自身は無視します。
				if (bt1.rawid == bt2.rawid) continue;
				// 座標、角度が誤差内でなければ、ghostではないと判定します。
				if (std::abs(bt1.x - bt2.x) > err_x) continue;
				if (std::abs(bt1.y - bt2.y) > err_y) continue;
				if (std::abs(bt1.ax - bt2.ax) > err_ax) continue;
				if (std::abs(bt1.ay - bt2.ay) > err_ay) continue;
				// ph（vol含む）が自身より小さければ、自身はghostではないと見做します。
				if (bt1.ph >= bt2.ph) continue;
				// すべての条件を満たした場合、bt1はbt2のghostであると判定します。
				found = true;
				break;
			}
			if (found) bf_deleted.push_back(bt1);
		}
		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << std::format("process time (broute force): {} (s)\n", elapsed.count());
	}

	if (hash_table)
	{
		// ハッシュテーブルの作成

		// 処理時間の計測のために、現在時刻を変数startに保存しておきます。
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

		// ハッシュテーブルを作成します。
		// 一般には、許容誤差の最大値をビン幅として用いるのが効率的であろうと思います。
		// ただし、ghost filterくらいビン幅が狭くなってしまうと、
		// ハッシュテーブルとして使っているstd::vectorのビン数が極端に増え、却って速度を悪化させてしまう可能性もあります。
		Hash<Basetrack> hash(xmin, xmax, err_x, ymin, ymax, err_y);
		for (const Basetrack& b : btlist) hash.Insert(b);

		std::vector<std::pair<int, int>> binlist;
		binlist.reserve(9);// 3x3=9個のビンが取得されるので、事前にメモリを9個分確保しておきます。
		for (const Basetrack& bt1 : btlist)
		{
			// bt1の座標からghost判定を行うべきビンのリストを取得し、btlistに格納しています。
			// このとき、座標bt1.x, bt1.yを含むビンを中心とする3x3個のビンが取得されます。
			// ビン幅はerr_x、err_yを設定しているので、3x3の探索が必要最小限です。
			hash.GetBinList(bt1.x, bt1.y, binlist);
			for (const std::pair<int, int>& bin : binlist)
			{
				// bin.first、bin.secondはそれぞれビンのx, y方向のインデックスです。
				// このビンに含まれる飛跡のリストを取得し、ghost判定を行います。
				const std::vector<Basetrack>& bt2list = hash.GetTrackList(bin.first, bin.second);
				bool found = false;
				for (const Basetrack& bt2 : bt2list)
				{
					// ここは総当たりのときと同じです。自身と似た座標、角度で、自身よりphが大きい飛跡を探します。
					if (bt1.rawid == bt2.rawid) continue;
					if (std::abs(bt1.x - bt2.x) > err_x) continue;
					if (std::abs(bt1.y - bt2.y) > err_y) continue;
					if (std::abs(bt1.ax - bt2.ax) > err_ax) continue;
					if (std::abs(bt1.ay - bt2.ay) > err_ay) continue;
					if (bt1.ph >= bt2.ph) continue;
					found = true;
					break;
				}
				if (found)
				{
					ht_deleted.push_back(bt1);
					break;
				}
			}
		}
		// 処理完了時の時刻をendに保存し、startからendまでの時間を処理に要した時間とします。
		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << std::format("process time (hash table): {} (s)\n", elapsed.count());
	}

	if (hash_table && broute_force)
	{
		// ハッシュテーブルによる削除とbroute forceによる削除の結果を比較し、
		// 両者が完全一致することを確認しています。

		if (ht_deleted.size() != bf_deleted.size())
		{
			std::cerr << std::format("Error: size mismatch: ht_deleted = {}, bf_deleted = {}\n", ht_deleted.size(), bf_deleted.size());
		}
		size_t min = std::min(ht_deleted.size(), bf_deleted.size());
		for (size_t i = 0; i < min; ++i)
		{
			if (ht_deleted[i].rawid != bf_deleted[i].rawid)
			{
				std::cerr << std::format("Error: rawid mismatch: ht_deleted[{}] = {}, bf_deleted[{}] = {}\n", i, ht_deleted[i].rawid, i, bf_deleted[i].rawid);
				std::cerr << std::format("{:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
					ht_deleted[i].ax, ht_deleted[i].ay, ht_deleted[i].x, ht_deleted[i].y,
					bf_deleted[i].ax, bf_deleted[i].ay, bf_deleted[i].x, bf_deleted[i].y);
			}
		}
		std::cout << "ghost filter success" << std::endl;
	}
	return 0;
}

/*
 問題
 上のコードはGhost filterを意図したハッシュ化となっています。
 これをt2lのようにLinkletを生成するコードに修正してみましょう。

 あっという間にできてしまった人は、ax、ayを組み込んだ4次元ハッシュ化に挑戦してみましょう。

 通常t2lの際は相対corrmap（corrmap-align.lstなど）に記録された区画ごとに異なるaffine parameterを与えて座標変換を行うため、
 飛跡の読み込み、座標変換、ハッシュ化、接続処理は区画ごとに逐一行うべきですが、
 今回は簡単のため全飛跡が単一の区画に収まるものと考え、かつ座標変換もz座標以外は適用済みとみなします。
 z座標については1000umのギャップがあるものとします（z_at_pl48 == z_at_pl49 + 1000）。

*/