#include <iostream>
#include <vector>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono> //<- 処理時間計測のために必要。
#include <algorithm> //<- sortのために必要。

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
	// ハッシュ化するのは上流側のPL49（z座標の小さい方）とし、PL48と49の中央面に飛跡を外挿してハッシュ化します。
	Hash(double xmin_, double xmax_, double xwbin_, double ymin_, double ymax_, double ywbin_, double dz_)
		: xmin(xmin_), ymin(ymin_), xwbin(xwbin_), ywbin(ywbin_), xnbin(0), ynbin(0), dz(dz_) // ここではdzは1000/2 = 500umです。
	{
		xnbin = int((xmax_ - xmin) / xwbin + 1);
		ynbin = int((ymax_ - ymin) / ywbin + 1);
		table.resize(xnbin * ynbin);
	}

	int GetIndex(int ix, int iy) const
	{
		return ix + iy * xnbin;
	}

	// 下流側（PL48）飛跡の座標と角度を受け取り、PL49との中央面まで外挿し、その座標に相当するビンのインデックスを返します。
	std::pair<int, int> GetIxIyFromDownPL(double x, double y, double ax, double ay) const
	{
		double cx = x - dz * ax;
		double cy = y - dz * ay;
		int ix = int((cx - xmin) / xwbin);
		int iy = int((cy - ymin) / ywbin);
		return { ix, iy };
	}
	// こちらは逆に上流側（PL49）の飛跡の座標と角度を受け取ってビンのインデックスに変換します。
	// 外挿の向きが異なるので、dzの符号が逆になっています。
	std::pair<int, int> GetIxIyFromUpPL(double x, double y, double ax, double ay) const
	{
		double cx = x + dz * ax;
		double cy = y + dz * ay;
		int ix = int((cx - xmin) / xwbin);
		int iy = int((cy - ymin) / ywbin);
		return { ix, iy };
	}

	// 下流側（PL48）飛跡から、接続判定を行うべきビンのリストを受け取るための関数です。
	// このとき外挿した座標cx、cyを含むビンを中心とする3x3個のビンが選択されます。
	void GetBinList(double x, double y, double ax, double ay, std::vector<std::pair<int, int>>& binlist) const
	{
		binlist.clear();
		std::pair<int, int> ixiy = GetIxIyFromDownPL(x, y, ax, ay);
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

	// あるビンix, iyに含まれる上流側（PL49）飛跡のリストを取得する関数です。
	const std::vector<Track>& GetTrackList(int ix, int iy) const
	{
		int index = GetIndex(ix, iy);
		return table[index];
	}
	// 上流側（PL49）の飛跡をハッシュテーブルに追加する関数です。
	void Insert(const Track& t)
	{
		std::pair<int, int> ixiy = GetIxIyFromUpPL(t.x, t.y, t.ax, t.ay);
		int index = GetIndex(ixiy.first, ixiy.second);
		table[index].push_back(t);
	}

	double xmin;
	double ymin;
	double xwbin;
	double ywbin;
	int xnbin;
	int ynbin;
	double dz;
	std::vector<std::vector<Track>> table;//table[ix + iy * xnbin]にix, iyのビンに含まれる飛跡が格納されます。
};

int main()
{
	// PL49の飛跡を読み込みます。
	std::vector<Basetrack> btlist49;
	std::ifstream ifs("../hash_with_pos_and_ang/basetrack_pl49.txt");
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
		double cx = b.x + 500 * b.ax;
		double cy = b.y + 500 * b.ay;
		xmin = std::min(xmin, cx);
		xmax = std::max(xmax, cx);
		ymin = std::min(ymin, cy);
		ymax = std::max(ymax, cy);
		btlist49.push_back(b);
	}

	// PL48の飛跡を読み込みます。
	ifs.close();
	std::vector<Basetrack> btlist48;
	ifs.open("../hash_with_pos_and_ang/basetrack_pl48.txt");// ifsを再利用するため、一度closeしてからopenしています。
	if (!ifs)
	{
		std::cerr << "Error: file not found" << std::endl;
		return 1;
	}
	while (std::getline(ifs, buf))
	{
		Basetrack b;
		std::istringstream iss(buf);
		iss >> b.pl >> b.rawid >> b.ph >> b.ax >> b.ay >> b.x >> b.y >> b.z;
		btlist48.push_back(b);
	}

	bool broute_force = true;
	bool hash_table = true;

	std::vector<std::pair<Basetrack, Basetrack>> bf_linklet;
	std::vector<std::pair<Basetrack, Basetrack>> ht_linklet;

	// ここからGhost filter。
	// ハッシュテーブルを用いた高速版と、総当たりによる方式との時間を計測し、
	// どの程度の速度差が生じるかを比較してみます。

	// ghostの判定に用いる許容誤差を設定します。
	double err_x = 50.0;
	double err_y = 50.0;
	double err_ax = 0.2;
	double err_ay = 0.2;

	if (broute_force)
	{
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (const Basetrack& bt1 : btlist48)
		{
			bool found = false;
			for (const Basetrack& bt2 : btlist49)
			{
				// z中央面まで飛跡を外挿したとき、位置ずれがerr_x, err_y以内であることを要求します。
				if (std::abs((bt1.x - 500 * bt1.ax) - (bt2.x + 500 * bt2.ax)) > err_x) continue;
				if (std::abs((bt1.y - 500 * bt1.ay) - (bt2.y + 500 * bt2.ay)) > err_y) continue;
				// 角度ずれがerr_ax, err_ay以内であることを要求します。
				if (std::abs(bt1.ax - bt2.ax) > err_ax) continue;
				if (std::abs(bt1.ay - bt2.ay) > err_ay) continue;
				// 座標、角度差が許容範囲内ならlinkletとして保存します。
				bf_linklet.push_back({ bt1, bt2 });
				//std::cout << std::format("linklet: {:>7.4f} {:>7.4f} {:>9.1f} {:9.1f} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
				//						 bt1.ax, bt1.ay, bt1.x, bt1.y, bt2.ax, bt2.ay, bt2.x, bt2.y);
			}
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
		Hash<Basetrack> hash(xmin, xmax, err_x, ymin, ymax, err_y, 500);
		for (const Basetrack& b : btlist49) hash.Insert(b);

		std::vector<std::pair<int, int>> binlist;
		binlist.reserve(9);
		for (const Basetrack& bt1 : btlist48)
		{
			// PL48の飛跡の座標からlinklet接続判定を行うべきビンのリストを取得し、btlistに格納しています。
			// このとき、座標bt1.x, bt1.yを含むビンを中心とする3x3個のビンが取得されます。
			// ビン幅はerr_x、err_yを設定しているので、3x3の探索が必要最小限です。
			hash.GetBinList(bt1.x, bt1.y, bt1.ax, bt1.ay, binlist);
			for (const std::pair<int, int>& bin : binlist)
			{
				// bin.first、bin.secondはそれぞれビンのx, y方向のインデックスです。
				// このビンに含まれる飛跡のリストを取得し、ghost判定を行います。
				const std::vector<Basetrack>& btlist49_bin = hash.GetTrackList(bin.first, bin.second);
				bool found = false;
				for (const Basetrack& bt2 : btlist49_bin)
				{
					// z中央面まで飛跡を外挿したとき、位置ずれがerr_x, err_y以内であることを要求します。
					if (std::abs((bt1.x - 500 * bt1.ax) - (bt2.x + 500 * bt2.ax)) > err_x) continue;
					if (std::abs((bt1.y - 500 * bt1.ay) - (bt2.y + 500 * bt2.ay)) > err_y) continue;
					// 角度ずれがerr_ax, err_ay以内であることを要求します。
					if (std::abs(bt1.ax - bt2.ax) > err_ax) continue;
					if (std::abs(bt1.ay - bt2.ay) > err_ay) continue;
					// 座標、角度差が許容範囲内ならlinkletとして保存します。
					ht_linklet.push_back({ bt1, bt2 });
					//std::cout << std::format("linklet: {:>7.4f} {:>7.4f} {:>9.1f} {:9.1f} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
					//						 bt1.ax, bt1.ay, bt1.x, bt1.y, bt2.ax, bt2.ay, bt2.x, bt2.y);
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
		// ハッシュテーブルと総当たりの結果を比較し、
		// 両者が完全一致することを確認します。

		if (ht_linklet.size() != bf_linklet.size())
		{
			std::cerr << std::format("Error: t2l failed, size mismatch: ht_linklet = {}, bf_linklet = {}\n",
									 ht_linklet.size(), bf_linklet.size());
		}
		// linkletの中身が一致するかを確認します。
		// が、PL49側の飛跡の並び順がハッシュテーブルと総当りの場合で一致しないので、事前にソートしています。
		// compareはラムダ式と呼ばれる機能ですが、詳細な説明は省略します。
		auto compare = [](const auto& a, const auto& b)
		{
			return a.first.rawid != b.first.rawid ? a.first.rawid < b.first.rawid : a.second.rawid < b.second.rawid;
		};
		std::sort(ht_linklet.begin(), ht_linklet.end(), compare);
		std::sort(bf_linklet.begin(), bf_linklet.end(), compare);
		size_t min = std::min(ht_linklet.size(), bf_linklet.size());
		for (size_t i = 0; i < min; ++i)
		{
			if (ht_linklet[i].first.rawid != bf_linklet[i].first.rawid)
			{
				std::cerr << std::format("Error: t2l failed, linklet mismatch: ht_linklet[{}] != bf_linklet[{}]\n",
										 ht_linklet[i].first.rawid, bf_linklet[i].first.rawid);
				std::cerr << std::format("{:>7.4f} {:>7.4f} {:>9.1f} {:9.1f} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
										 ht_linklet[i].first.ax, ht_linklet[i].first.ay, ht_linklet[i].first.x, ht_linklet[i].first.y,
										 bf_linklet[i].first.ax, bf_linklet[i].first.ay, bf_linklet[i].first.x, bf_linklet[i].first.y);
			}
		}
		std::cout << "t2l success" << std::endl;
	}
	return 0;
}
