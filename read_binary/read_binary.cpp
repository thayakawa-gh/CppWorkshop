#include <fstream>
#include <iostream>
#include <vector>
#include <format>

struct Data
{
	int a, b;
	double c, d;
};

int main()
{
	// write_binaryを先に実行し、data.binを作成しておいてください。
	std::ifstream ifs("../write_binary/data.bin", std::ios::binary);
	if (!ifs)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	// ファイルサイズから要素数を求め、まとめて読み込みます。
	// seekgでファイルポインタを末尾に移動し、tellgで現在位置（=ファイルサイズ）を取得します。
	ifs.seekg(0, std::ios::end);
	std::streamoff size = ifs.tellg();
	ifs.seekg(0, std::ios::beg); // 読み込み位置を先頭に戻す

	std::vector<Data> vec(size / sizeof(Data));
	// ifstream::read(先頭アドレス, バイト数)で、ファイルの中身を
	// 指定したアドレス以降のメモリにそのまま読み込みます。
	ifs.read(reinterpret_cast<char*>(vec.data()), size);

	for (const Data& d : vec)
	{
		std::cout << std::format("a = {}, b = {}, c = {}, d = {}\n", d.a, d.b, d.c, d.d);
	}
}

/*
 演習
 write_binaryの演習で作成したbasetracks.datを読み込み、
 std::vector<Basetrack>に格納するプログラムを作成してください。
 読み込んだ内容をコンソールに出力し、basetracks.txt（第4回参照）の内容と
 一致することを確認してください。

 ヒント：
 上のコードのように、先にファイルサイズを取得して要素数を計算し、
 vector::resizeやコンストラクタでまとめて確保してから読み込むと簡単です。
 あるいは、以下のようにEOFに達するまで1個ずつ読み込んでいく方法もあります。

 Basetrack tmp;
 std::vector<Basetrack> btlist;
 while (ifs.read(reinterpret_cast<char*>(&tmp), sizeof(Basetrack)))
 {
 	btlist.push_back(tmp);
 }
*/
