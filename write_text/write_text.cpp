#include <fstream>
#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <sstream>

int main()
{
	// std::ofstreamを使ってテキストファイルに書き込むことができます。
	std::ofstream ofs("output.txt");
	if (!ofs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	for (int line = 1; line < 10; ++line)
	{
		int a = line * 10 + 1;
		int b = line * 10 + 2;
		double c = line + 0.3;
		double d = line + 0.4;
		//簡易的には、ofsに<<で次々と値を書き込むこともできます。
		//ただし、テキストの整形が非常に大変（std::iomanipを使えばできなくはない）な上、
		//std::printに比べて遅いです。
		ofs << a << " " << b << " " << c << " " << d << "\n";
	}

	for (int line = 10; line < 20; ++line)
	{
		int a = line * 10 + 1;
		int b = line * 10 + 2;
		double c = line + 0.3;
		double d = line + 0.4;
		//新しいVisual Studioを使っているのなら、std::printを使うことで簡単にフォーマットでき、
		//ofs << ...よりも高速に動作します。
		std::print(ofs, "{:>4} {:>4} {:>6.2f} {:>6.2f}\n", a, b, c, d);
	}
}

/*
 問題3
 問題1、2でbasetracks.txtを読み込みstd::vector<Basetrack>を作るところまではできたと思います。
 では、このstd::vector<Basetrack>のうち、PHが20以上のBasetrackのみを抽出して、
 テキストファイルに出力するコードを追加してみましょう。
*/