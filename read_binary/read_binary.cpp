#include <fstream>
#include <iostream>
#include <vector>
#include <format>

class Data
{
public:
	int a, b;
	double c, d;
};

int main()
{
	// バイナリ形式のファイルもstd::ifstreamで読み込むことが出来ます。
	// std::ios::binaryを指定するのを忘れないようにしてください。

	/*
	!!注意!!
	バイナリファイルを読み込む場合、書き込み側と型のサイズ、構造体の配置などが同じであることが前提となります。
	例えばここで、
	class Data2
	{
	public:
		int a;
		float b;
		double c;
	};
	のようなwrite_binary側で定義したDataと異なるクラスを定義してここに無理やり読み込むと、不正なデータが出来上がります。
	必ずwrite_binary側と同じ定義のクラスを用意してください。
	*/

	// 方法1. 1要素ずつ読み込む方法
	std::ifstream ifs_list1("../write_binary/data_list1.bin", std::ios::binary);
	if (!ifs_list1)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}
	std::vector<Data> vec1;
	Data tmp;
	while (ifs_list1.read(reinterpret_cast<char*>(&tmp), sizeof(Data)))
	{
		vec1.push_back(tmp);
	}
	// 読み込みエラーのチェック。
	if (ifs_list1.bad() || !ifs_list1.eof() || ifs_list1.gcount() != 0)
	{
		std::cerr << "Failed to read complete data.\n";
		return 1;
	}

	// 中身の確認
	for (const Data& d : vec1)
	{
		std::cout << std::format("a = {:>4}, b = {:>4}, c = {:>3.1f}, d = {:>3.1f}\n", d.a, d.b, d.c, d.d);
	}


	// 方法2. ファイルサイズを求めてまとめて読み込む方法
	std::ifstream ifs_list2("../write_binary/data_list1.bin", std::ios::binary);
	if (!ifs_list2)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	// ファイルサイズから要素数を求め、まとめて読み込みます。
	// seekgでファイルポインタを末尾に移動し、tellgで現在位置（=ファイルサイズ）を取得します。
	ifs_list2.seekg(0, std::ios::end);
	std::streamoff size = ifs_list2.tellg();
	ifs_list2.seekg(0, std::ios::beg); // 読み込み位置を先頭に戻す

	if (size % sizeof(Data) != 0)
	{
		// ファイルサイズがDataのサイズの倍数でない場合、ファイルが壊れているのでエラーとします。
		std::cerr << "File size is not a multiple of Data size." << std::endl;
		return 1;
	}

	std::vector<Data> vec2(size / sizeof(Data));
	// ifstream::read(先頭アドレス, バイト数)で、ファイルの中身を
	// 指定したアドレス以降のメモリにそのまま読み込みます。
	if (!ifs_list2.read(reinterpret_cast<char*>(vec2.data()), size))
	{
		// 読み込みに失敗した場合はエラーとします。
		std::cerr << "Failed to read data." << std::endl;
		return 1;
	}

	// 中身の確認
	for (const Data& d : vec2)
	{
		std::cout << std::format("a = {:>4}, b = {:>4}, c = {:>3.1f}, d = {:>3.1f}\n", d.a, d.b, d.c, d.d);
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
