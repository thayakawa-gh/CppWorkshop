#include <iostream>
#include <fstream>
#include <vector>
#include <format>
#include <string>
#include <sstream>

class Microtrack
{
public:
	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

template <class Track1, class Track2>
class Linklet
{
public:

	//Track1とTrack2を接続したLinkletクラス。
	Linklet() {}
	Linklet(const Track1& t1_, const Track2& t2_)
		: t1(t1_), t2(t2_)
	{}

	int ph() const { return t1.ph + t2.ph; }
	double x() const { return (t1.x + t2.x) / 2; }
	double y() const { return (t1.y + t2.y) / 2; }
	double z() const { return (t1.z + t2.z) / 2; }
	double ax() const { return (t1.x - t2.x) / (t1.z - t2.z); }
	double ay() const { return (t1.y - t2.y) / (t1.z - t2.z); }

	double dx() const
	{
		double cz = (t1.z + t2.z) / 2;
		double x1 = t1.x + (cz - t1.z) * t1.ax;
	}
	double dax() const { return t1.ax - t2.ax; }
	double day() const { return t1.ay - t2.ay; }

	Track1 t1;
	Track2 t2;
};

std::vector<Basetrack> ReadBasetracks(const std::string& filename)
{
	std::vector<Basetrack> bt;
	std::ifstream ifs(filename);
	if (!ifs)
	{
		std::cerr << "Error: file not found." << std::endl;
		return bt;
	}
	std::string buf;
	while (std::getline(ifs, buf))
	{
		Basetrack b;
		std::istringstream iss(buf);
		iss >> b.pl >> b.rawid >> b.ph >> b.ax >> b.ay >> b.x >> b.y >> b.z;
		bt.push_back(b);
	}
	return bt;
}
std::vector<Microtrack> ReadMicrotracks(const std::string& filename)
{
	std::vector<Microtrack> mt;
	std::ifstream ifs(filename);
	if (!ifs)
	{
		std::cerr << "Error: file not found." << std::endl;
		return mt;
	}
	std::string buf;
	while (std::getline(ifs, buf))
	{
		Microtrack m;
		std::istringstream iss(buf);
		iss >> m.pos >> m.rawid >> m.ph >> m.ax >> m.ay >> m.x >> m.y >> m.z;
		mt.push_back(m);
	}
	return mt;
}
template <class Track>
void TransAffine(std::vector<Track>& list, double a, double b, double c, double d, double p, double q, double dz)
{
	for (Track& bt : list)
	{
		double x_ = bt.x * a + bt.y * b + p;
		double y_ = bt.x * c + bt.y * d + q;
		double ax_ = bt.ax * a + bt.ay * b;
		double ay_ = bt.ax * c + bt.ay * d;
		bt.x = x_;
		bt.y = y_;
		bt.ax = ax_;
		bt.ay = ay_;
		bt.z += dz;
	}
}

template <class Track1, class Track2>
bool JudgeConnection(const Track1& t1, const Track2& t2)
{
	if (std::abs(t1.ax - t2.ax) > 0.2) return false;
	if (std::abs(t1.ay - t2.ay) > 0.2) return false;
	double z = (t1.z + t2.z) / 2;
	double x1 = t1.x + (z - t1.z) * t1.ax;
	double x2 = t2.x + (z - t2.z) * t2.ax;
	if (std::abs(x1 - x2) > 200) return false;
	double y1 = t1.y + (z - t1.z) * t1.ay;
	double y2 = t2.y + (z - t2.z) * t2.ay;
	if (std::abs(y1 - y2) > 200) return false;
	return true;
}
template <class Track1, class Track2>
std::vector<Linklet<Track1, Track2>> Connect(const std::vector<Track1>& list1, const std::vector<Track2>& list2)
{
	std::vector<Linklet<Track1, Track2>> lt;
	for (const Track1& t1 : list1)
	{
		for (const Track2& t2 : list2)
		{
			if (!JudgeConnection(t1, t2)) continue;
			lt.push_back(Linklet<Track1, Track2>(t1, t2));
		}
	}
	return lt;
}

class DposDang
{
public:
	template <class Track1, class Track2>
	bool JudgeConnection(const Track1& t1, const Track2& t2)
	{
		if (std::abs(t1.ax - t2.ax) > 0.2) return false;
		if (std::abs(t1.ay - t2.ay) > 0.2) return false;
		double z = (t1.z + t2.z) / 2;
		double x1 = t1.x + (z - t1.z) * t1.ax;
		double x2 = t2.x + (z - t2.z) * t2.ax;
		if (std::abs(x1 - x2) > 200) return false;
		double y1 = t1.y + (z - t1.z) * t1.ay;
		double y2 = t2.y + (z - t2.z) * t2.ay;
		if (std::abs(y1 - y2) > 200) return false;
		return true;
	}
};
class DposDangPH
{
public:
	DposDangPH(int ph, double dpos, double dang)
		: ph_threshold(ph), dpos_threshold(dpos), dang_threshold(dang)
	{}

	template <class Track1, class Track2>
	bool JudgeConnection(const Track1& t1, const Track2& t2)
	{
		if (int((t1.ph + t2.ph) / 10000) < ph_threshold) return false;
		if (std::abs(t1.ax - t2.ax) > dang_threshold) return false;
		if (std::abs(t1.ay - t2.ay) > dang_threshold) return false;
		double z = (t1.z + t2.z) / 2;
		double x1 = t1.x + (z - t1.z) * t1.ax;
		double x2 = t2.x + (z - t2.z) * t2.ax;
		if (std::abs(x1 - x2) > dpos_threshold) return false;
		double y1 = t1.y + (z - t1.z) * t1.ay;
		double y2 = t2.y + (z - t2.z) * t2.ay;
		if (std::abs(y1 - y2) > dpos_threshold) return false;
		return true;
	}
	int ph_threshold;
	double dpos_threshold;
	double dang_threshold;
};
template <class Track1, class Track2, class Cut>
std::vector<Linklet<Track1, Track2>> Connect(const std::vector<Track1>& list1, const std::vector<Track2>& list2, const Cut& cut)
{
	std::vector<Linklet<Track1, Track2>> lt;
	for (const Track1& t1 : list1)
	{
		for (const Track2& t2 : list2)
		{
			if (!cut.JudgeConnection(t1, t2)) continue;
			lt.push_back(Linklet<Track1, Track2>(t1, t2));
		}
	}
	return lt;
}

int main()
{
	std::vector<Basetrack> bt_pl48 = ReadBasetracks("../class_template/basetracks_pl48.txt");
	std::vector<Basetrack> bt_pl49 = ReadBasetracks("../class_template/basetracks_pl49.txt");
	std::vector<Microtrack> mt_pl49 = ReadMicrotracks("../class_template/microtracks_pl49.txt");

	double a = 1.001610, b = -0.002939, c = 0.002939, d = 1.001610, p = -675.4, q = -43.3, dz = -814.0;
	TransAffine(bt_pl49, a, b, c, d, p, q, dz);
	TransAffine(mt_pl49, a, b, c, d, p, q, dz);

	std::vector<Linklet<Basetrack, Basetrack>> ltbb = Connect(bt_pl48, bt_pl49);
	for (const Linklet<Basetrack, Basetrack>& lt : ltbb)
	{
		std::cout << std::format("{:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f} {:>9.1f} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f} {:>9.1f}\n",
								 lt.t1.ax, lt.t1.ay, lt.t1.x, lt.t1.y, lt.t1.z, lt.t2.ax, lt.t2.ay, lt.t2.x, lt.t2.y, lt.t2.z);
	}
	std::cout << std::endl;
	std::vector<Linklet<Basetrack, Microtrack>> ltbm = Connect(bt_pl48, mt_pl49);
	for (const Linklet<Basetrack, Microtrack>& lt : ltbm)
	{
		std::cout << std::format("{:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f} {:>9.1f} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f} {:>9.1f}\n",
								 lt.t1.ax, lt.t1.ay, lt.t1.x, lt.t1.y, lt.t1.z, lt.t2.ax, lt.t2.ay, lt.t2.x, lt.t2.y, lt.t2.z);
	}
}