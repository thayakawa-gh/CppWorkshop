#include <iostream>
#include <format>

class MicrotrackSubset
{
public:
	MicrotrackSubset() : ax(0), ay(0), z(0), ph(0), pos(0), col(0), row(0), zone(0), isg(0), rawid(0) {}
	MicrotrackSubset(double ax_, double ay_, double z_, int ph_, int pos_, int col_, int row_, int zone_, int isg_, int64_t rawid_)
		: ax(ax_), ay(ay_), z(z_), ph(ph_), pos(pos_), col(col_), row(row_), zone(zone_), isg(isg_), rawid(rawid_)
	{}

	double ax, ay;
	double z;
	int ph;
	int pos, col, row, zone, isg;
	int64_t rawid;
};

class MicrotrackFull : public MicrotrackSubset
{
public:
	MicrotrackFull(double ax_, double ay_, double x_, double y_, double z_, double z1_, double z2_,
				   int ph_, int pos_, int col_, int row_, int zone_, int isg_, int64_t rawid_,
				   float px_, float py_)
		: MicrotrackSubset(ax_, ay_, z_, ph_, pos_, col_, row_, zone_, isg_, rawid_), x(x_), y(y_), z1(z1_), z2(z2_), px(px_), py(py_)
	{}

	double x, y;
	double z1, z2;
	float px, py;
};


int main_()
{
	MicrotrackFull mt(-0.1530, 4.1398, 59423.4, 90658.2, 53266, 53231, 53301,
					  120069, 1, 2, 3, 0, 0, 12345, 0.0, 0.0);
	std::cout << std::format("ax: {}, ay: {}, x: {}, y: {}, z: {}", mt.ax, mt.ay, mt.x, mt.y, mt.z) << std::endl;

	return 0;
}