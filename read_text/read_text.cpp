#include <iostream>
#include <fstream> // <-- std::ifstreamを使うために必要
#include <format>
#include <string>
#include <sstream> // <-- std::istringstreamを使うために必要

int main()
{
	std::ifstream ifs("text.txt"); // カレントディレクトリにあるtext.txtを開きます。
	// 次のようにファイルの絶対/相対パスを指定することもできます。
	// std::ifstream ifs("C:/folder1/folder2/text.txt");

	// ファイルが存在するか、開くことができるかをチェックしています。
	if (!ifs)
	{
		// ファイルを開くのに失敗した場合は、エラーメッセージを出力して終了します。
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}

	int a, b;
	double c, d;
	std::string buf;

	// std::getlineでifsから1行分の文字列を読み込み、bufに格納しています。
	// while文はfor文とは異なるループ構文で、条件式が真の間ループを繰り返すものです。
	// for (; std::getline(ifs, buf); )と同じ。
	while (std::getline(ifs, buf))
	{
		// bufには"11 12 1.3 1.4"のように、1行分の文字列が入っています。
		// この文字列を空白文字で区切り、それぞれの部分を>>を用いて変数a～dに格納しています。
		std::istringstream iss(buf);
		iss >> a >> b >> c >> d;
		std::cout << std::format("a = {}, b = {}, c = {}, d = {}\n", a, b, c, d);
	}
}

/*
 問題
 basetrack.txtに、以下のように1行あたり1本、全20本のBasetrackの情報が記録されています。
 067    123456 240105  0.2376  1.5982  126489.1  166005.3       0.0
 左から、Basetrackのpl、rawid、ph、ax、ay、x、y、zです。
 これを前回の勉強会で作成したBasetrackクラスに読み込み、全てのBasetrack情報をstd::vector<Basetrack>に格納してみましょう。
 その後、正しく読み込めたか確認するために、全てのBasetrack情報をforループとstd::cout/std::print等を使って画面に表示してみましょう。

 ヒント:

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
	??????
	Basetrack tmp;
	std::vector<Basetrack> btlist;
	while (??????)
	{
		??????
 		btlist.push_back(tmp);
	}
	??????
}
*/