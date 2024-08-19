#include <iostream>
#include <fstream> // <-- std::ifstreamを使うために必要
#include <format>
#include <string>
#include <charconv> // <-- Parse関数内でstd::from_charsを使うために必要

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
/*
 istringstreamは使いやすいですが、非常に遅いため、100MB以上のファイルを読むのに使うのは推奨しません。
 代わりの方法として、上記のようなParse関数を作ることができます。
 Visual Studioの場合、istringstreamよりもざっくり4～5倍速くなります。
 Parse関数には、第一引数に一行分の文字列が格納されたstringを、第二引数以降に数値を格納するための変数を渡します。
 C++を深く理解したい場合を除き、Parse関数の中身を理解する必要はありません。コピペして使いましょう。
*/

int main()
{
	std::ifstream ifs("text.txt");

	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	int a, b;
	double c, d;
	std::string buf;

	while (std::getline(ifs, buf))
	{
		// スペースやタブなどの空白文字区切りで数値が入っているstringから、各数値をa～dに格納しています。
		Parse(buf, a, b, c, d);
		std::cout << std::format("a = {}, b = {}, c = {}, d = {}\n", a, b, c, d);
	}
}

/*
 問題2
 問題1ではstd::istringstreamを使ってbasetrack.txtを読み込みましたが、
 これをParse関数に書き直してみましょう。
*/