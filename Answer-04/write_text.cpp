#include <fstream>
#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <sstream>

std::from_chars_result Parse_impl(const char* pos, const char* last)
{
	return std::from_chars_result{ pos, std::errc{} };
}
template <class Value, class ...Values>
	requires std::is_arithmetic_v<Value>
std::from_chars_result Parse_impl(const char* pos, const char* last, Value& v, Values& ...vs)
{
	while (std::isspace(*pos)) ++pos;
	auto res = std::from_chars(pos, last, v);
	if (res.ec != std::errc{}) return res;
	if (res.ptr != last) return Parse_impl(res.ptr, last, vs...);
	return std::from_chars_result{ last, std::errc{} };
}
template <class ...Values>
std::from_chars_result Parse(const std::string& src, Values& ...vs)
{
	const char* pos = src.data();
	const char* last = pos + src.size();
	if constexpr (sizeof...(Values) > 0) return Parse_impl(pos, last, vs...);
	else return std::from_chars_result{ pos, std::errc{} };
}

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

int main()
{
	std::ifstream ifs("../read_text/basetracks.txt");
	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}
	Basetrack tmp;
	std::vector<Basetrack> btlist;
	std::string line;
	while (std::getline(ifs, line))
	{
		Parse(line, tmp.pl, tmp.rawid, tmp.ph, tmp.ax, tmp.ay, tmp.x, tmp.y, tmp.z);
		btlist.push_back(tmp);
	}
	//ここまで読み込み。

	//ここから出力。
	std::ofstream ofs("basetracks_out.txt");
	for (const auto& bt : btlist)
	{
		//PHが20未満の場合はcontinueで飛ばす。
		if (int(bt.ph / 10000) < 20) continue;
		std::print(ofs, "{:0>3} {:>10} {:>6} {:>7.4f} {:>7.4f} {:>9.1f} {:>9.1f}\n",
				   			bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y, bt.z);
	}
}