#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>
#include <format>

class Basetrack
{
public:
	Basetrack() = default;
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

class PosCut : public CutBase
{
public:
	PosCut(double xmin_, double xmax_, double ymin_, double ymax_)
		: xmin(xmin_), xmax(xmax_), ymin(ymin_), ymax(ymax_)
	{}
	virtual ~PosCut() = default;

	virtual bool Judge(const Basetrack& tracks) const override
	{
		return tracks.x >= xmin && tracks.x < xmax && tracks.y >= ymin && tracks.y < ymax;
	}

	double xmin, xmax, ymin, ymax;
};

std::vector<Basetrack> CutTracks(const std::vector<Basetrack>& tracks, const std::vector<std::unique_ptr<CutBase>>& cuts)
{
	std::vector<Basetrack> result;
	size_t size = tracks.size();
	for (size_t i = 0; i < size; ++i)
	{
		const Basetrack& track = tracks[i];
		bool satisfy = true;
		size_t csize = cuts.size();
		for (size_t j = 0; j < csize; ++j)
		{
			if (!cuts[j]->Judge(track))
			{
				satisfy = false;
				break;
			}
		}
		if (satisfy)
		{
			result.push_back(track);
		}
	}
	return result;
}

int main()
{
	std::vector<Basetrack> btlist;
	std::ifstream ifs("..\\read_text\\basetracks.txt");
	if (!ifs)
	{
		std::cerr << "File not found.\n";
		return -1;
	}

	std::string buf;
	while (std::getline(ifs, buf))
	{
		Basetrack bt;
		std::istringstream iss(buf);
		iss >> bt.pl >> bt.rawid >> bt.ph >> bt.ax >> bt.ay >> bt.x >> bt.y >> bt.z;
		btlist.push_back(bt);
	}

	std::vector<std::unique_ptr<CutBase>> cuts;
	cuts.push_back(std::make_unique<PHCut>(19));
	cuts.push_back(std::make_unique<AngCut>(0.0, 0.4));
	cuts.push_back(std::make_unique<PosCut>(30000.0, 40000.0, 40000.0, 50000.0));

	std::vector<Basetrack> btlist_cut = CutTracks(btlist, cuts);

	for (size_t i = 0; i < btlist_cut.size(); ++i)
	{
		const Basetrack& bt = btlist_cut[i];
		std::cout << std::format("{:>3} {:>10} {:>6} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f} {:>9.1f}\n",
								 bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y, bt.z);
	}

	return 0;
}