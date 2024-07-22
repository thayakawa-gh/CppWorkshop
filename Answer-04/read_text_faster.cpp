#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

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

	for (const auto& bt : btlist)
	{
		std::cout << std::format("pl = {}, rawid = {}, ph = {}, ax = {}, ay = {}, x = {}, y = {}, z = {}\n",
								 bt.pl, bt.rawid, bt.ph, bt.ax, bt.ay, bt.x, bt.y, bt.z);
	}
}