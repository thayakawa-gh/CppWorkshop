#include <fstream>
#include <iostream>
#include <vector>
#include <format>

// バイナリファイルとは、文字コードとして解釈されることを前提とせず、
// メモリ上のバイト列をそのままファイルに書き出したものです。
// 例えばint型の値100は、テキストファイルでは'1','0','0'という3文字（3バイト）で表現されますが、
// バイナリファイルでは4バイトの整数値としてそのまま書き込まれます。
// 人間には読めなくなりますが、文字列への変換・パースが不要になるため高速で、
// double等の浮動小数点数を書き込んでも桁落ちが起きません。また、ファイルサイズも小さくなります。

struct Data
{
	int a, b;
	double c, d;
};

int main()
{
	std::vector<Data> vec;
	for (int line = 1; line < 10; ++line)
	{
		vec.push_back(Data{ line * 10 + 1, line * 10 + 2, line + 0.3, line + 0.4 });
	}

	// std::ios::binaryを付けてファイルを開きます。
	// これを付けずに開くと、Windows環境では書き込んだデータの中の0x0Aというバイトが
	// 勝手に0x0D 0x0A（\r\n）に変換されてしまうことがあり、バイナリデータが壊れます。
	std::ofstream ofs("data.bin", std::ios::binary);
	if (!ofs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	// ofstream::write(先頭アドレス, バイト数)を使うと、指定したアドレスから
	// 指定バイト数ぶんのメモリの中身を、解釈を挟まずそのままファイルに書き込めます。
	// 第1引数はconst char*型である必要があるため、reinterpret_castで変換します。
	for (const Data& d : vec)
	{
		ofs.write(reinterpret_cast<const char*>(&d), sizeof(Data));
	}

	std::cout << std::format("Wrote {} elements ({} bytes each) to data.bin\n", vec.size(), sizeof(Data));
}

/*
 演習
 第4回の演習で作成したBasetrackクラスと、basetracks.txtを読み込んで作った
 std::vector<Basetrack> btlistを使って、その中身をバイナリファイルbasetracks.datとして
 書き出すプログラムを作成してください。

 ヒント：
 std::vector<Basetrack>のように複数の要素をまとめて書き込みたい場合、
 上のコードのように1個ずつループで書き込む以外に、vector::data()を使って
 一度にまとめて書き込むこともできます。

 ofs.write(reinterpret_cast<const char*>(btlist.data()), btlist.size() * sizeof(Basetrack));
*/
