#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <format>

// バイナリファイルとは、文字コードとして解釈されることを前提とせず、
// メモリ上のバイト列をそのままファイルに書き出したものです。
// 例えばint型の値123456は、テキストファイルでは'1','2','3','4','5','6'という6文字（6バイト）で表現されますが、
// バイナリファイルでは4バイトの整数値としてそのまま書き込まれます。
// 人間には読めなくなりますが、文字列への変換・パースが不要になるため高速です。
// double等の浮動小数点数を書き込んでも精度が劣化せず、またファイルサイズも多くの場合小さくなります。
// 小さな（例えば100MB以下）のデータであればテキストファイルでもそれほど問題ありませんが、
// 大きなデータを大量に処理しなければならない場合は、バイナリファイルの方が有利です。

class Data
{
public:
	int a, b;
	double c, d;
};

void ShowIntBits(int value)
{
	unsigned int bits = std::bit_cast<unsigned int>(value);
	std::cout << std::format("int: {}, Hex: {:0>8x}, Bin: {:0>32b}\n", value, bits, bits);
}
void ShowDoubleBits(double value)
{
	uint64_t bits(std::bit_cast<uint64_t>(value));
	std::cout << std::format("double: {}, Hex: {:0>16x}, Bin: {:0>64b}\n", value, bits, bits);
}

int main()
{
	Data d1{ 11, 12, 1.3, 1.4 };
	// プログラム中の整数や浮動小数点、文字列などの変数は、メモリ上では0と1のビット列として格納されています。
	// int型の変数は4バイト（32ビット）、double型の変数は8バイト（64ビット）です。
	// d1が持っている変数を16進数、2進数のビットの羅列として表示してみます。
	// （16進数は、0/1のビットを4つごとにグループ化し、0-9とa-fで表現します。a=10, b=11, c=12, d=13, e=14, f=15です。）
	ShowIntBits(d1.a);// int: 11, Hex: 0000000b, Bin: 00000000000000000000000000001011
	ShowIntBits(d1.b);// int: 12, Hex: 0000000c, Bin: 00000000000000000000000000001100
	ShowDoubleBits(d1.c);// double: 1.3, Hex: 3ff4cccccccccccd, Bin: 0011111111110100110011001100110011001100110011001100110011001101
	ShowDoubleBits(d1.d);// double: 1.4, Hex: 3ff6666666666666, Bin: 0011111111110110011001100110011001100110011001100110011001100110

	// データをバイナリモードで書き込むには、std::ios::binaryを指定します。
	std::ofstream ofs_int("data_int.bin", std::ios::binary);
	// ofstream::write(先頭アドレス, バイト数)を使うと、指定したアドレスから
	// 指定バイト数ぶんのメモリの中身を、解釈を挟まずそのままファイルに書き込めます。
	// 第1引数はconst char*型である必要があるため、reinterpret_castで変換します。そういうもの、と思ってください。
	ofs_int.write(reinterpret_cast<const char*>(&d1.a), sizeof(int));

	std::ofstream ofs_single("data_single.bin", std::ios::binary);
	ofs_single.write(reinterpret_cast<const char*>(&d1), sizeof(Data));

	// バイナリエディタを用いてこれらのファイルを開いてみましょう。VSCodeなら、拡張機能の「Hex Editor」を使えば開けます。
	// 次のように表示されると思います。
	// data_int.bin:
	// 0B 00 00 00
	// data_single.bin:
	// 0B 00 00 00 0C 00 00 00 CD CC CC CC CC CC F4 3F 66 66 66 66 66 66 F6 3F

	// data_singleは、0B 00 00 00（d1.a）、0C 00 00 00（d1.b）、CD CC CC CC CC CC F4 3F（d1.c）、66 66 66 66 66 66 F6 3F（d1.d）の順に並んでいます。

	// 実はメモリ上のビット列は、CPUのアーキテクチャによって、バイトの並び順が異なる場合があります。
	// 我々の使う一般的なPCはリトルエンディアンと呼ばれる方式で、1バイト（=8ビット）ずつ逆順に並んでいます。
	// 例えば、double型の1.3は16進数で3ff4cccccccccccdですが、メモリ上ではCD CC CC CC CC CC F4 3Fの順に並んでいます。
	// バイナリファイルを書き込むときもこの順番で書き込まれるため、バイナリエディタで表示すると逆順に見えます。
	// つまり、data_int.binもdata_single.binも、メモリ上のビット列がそのまま加工されずに書き込まれているわけです。


	// std::vectorのような配列の中身もバイナリファイルに書き出すことが出来ます。
	std::vector<Data> vec;
	for (int line = 1; line < 10; ++line)
	{
		vec.push_back(Data{ line * 10 + 1, line * 10 + 2, line + 0.3, line + 0.4 });
	}

	// 方法1. 1個ずつループで書き込む方法
	std::ofstream ofs_list1("data_list1.bin", std::ios::binary);
	if (!ofs_list1)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}
	for (const Data& d : vec)
	{
		ofs_list1.write(reinterpret_cast<const char*>(&d), sizeof(Data));
	}

	// 方法2. vector::data()を使ってまとめて書き込む方法
	// 一般にはこちらのような一括書き込みのほうが高速です。
	std::ofstream ofs_list2("data_list2.bin", std::ios::binary);
	if (!ofs_list2)
	{
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}
	ofs_list2.write(reinterpret_cast<const char*>(vec.data()), vec.size() * sizeof(Data));


	/*
	!!注意!!
	Dataのような単純な構造体はバイナリファイルにそのまま書き込むことが出来ますが、
	std::stringのような長さが変動するデータなど、単なるintやdouble等の集まりでないクラス、構造体は、
	バイナリファイルにそのまま書き込むことは出来ません。
	これは、std::stringの中身がポインタ（第7回あたりで扱います）を用いたもっと複雑な構造になっているためです。
	例えば以下のような処理は破綻します。
	struct Data2
	{
		int a, b;
		std::string c;
	};
	std::ofstream ofs("data_with_string.bin", std::ios::binary);
	...
	ofs.write(reinterpret_cast<const char*>(&d2), sizeof(Data2)); // Data2がstd::stringを含むため、これは期待される動作にならない。
	*/
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
