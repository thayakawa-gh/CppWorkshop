#include <argparse/argparse.hpp>
#include <iostream>

// #### 動機
// プログラム実行時に与えるコマンドライン引数を読み込み、プログラムの挙動を調整する方法。
// 何らかのプログラムを実行するとき、そのプログラムに対してパラメータを与えて挙動を調整したくなることがしばしばあります。
// シンプルな例で言えば、あるBasetrackのファイルを読み込み、PHカットをかけて残ったBasetrackを出力したいと考えたとき、
// このPH閾値をプログラム中に直接書いてしまうと、PH閾値を外から変更できなくなってしまいます。
// しかし例えば以下のように、実行時に外からコマンドライン引数として閾値を渡すことができれば、いちいちコードを修正しなくても閾値の変更が可能です。
// program_name.exe --ph_cut 20
// これを実現する方法は色々とありますが、ここでは早川がよく使う方法を紹介します。

// #### argparse概要
// C++には、コマンドライン引数をシンプルに扱うための機能が標準で用意されていません。
// NETSCANなどは結構な力業でこれを実装していますが、応用性の低さを思うと良い方法ではないでしょう。
// そこで、argparseというライブラリを使うことをお勧めします。
// argparseはサードパーティ製ライブラリで、以下のGitHubリポジトリで公開されています。
// https://github.com/p-ranav/argparse
// コマンドライン引数として受け取った値を解読し、パラメータを簡単に取り出せるようにする便利なライブラリです。
// シングルヘッダのため導入しやすく、使い方もシンプルです。

// 導入方法（Visual Studioの場合） リソースファイルの画像（argparse.png）も参照。
// 1. E:\udd\hayakawa\prg\ThirdPartyにあるargparse-3.2フォルダを、任意のローカルなフォルダなどにコピペする。もちろんGitHubから直接入手しても良い。
// 2. Visual Studioでargparseを使いたいプロジェクトを開く。
// 3. ソリューションエクスプローラー（大抵はVisual Studioのウィンドウ右側にあります）から、プロジェクト名を右クリックし、プロパティを選択。
// 4. 「構成プロパティ」→「VC++ ディレクトリ」→「インクルードディレクトリ」に、argparseのコピー先フォルダを追加する。
// 5. 「構成プロパティ」→「C/C++」→「言語」→「C++言語標準」→「/std:c++17」ないし数字が17以上のものを選択。/std:c++20以上か/std:c++latestを推奨。

int main(char argc, char* argv[])
{
	argparse::ArgumentParser parser("This is a test program.");

	parser.add_argument("input_filename").help("input file name");
	parser.add_argument("output_filename").help("output file name");

	// 整数型を受け取りたいときはscan<'i', int>()を使う。
	parser.add_argument("--ph_cut").help("PH cut threshold").scan<'i', int>().default_value(20);
	// 浮動小数点型を受け取りたいときはscan<'f', double>()を使う。
	// また複数の値を受け取りたい場合、nargs(num)ないしnargs(min, max)のように数を指定する。
	parser.add_argument("--xrange").help("xmin xmax").scan<'f', double>().default_value(std::vector<double>()).nargs(2);
	parser.add_argument("--rem_tracks").help("output filename for removed track list").default_value(std::string());

	// 上記の引数定義だと、次のようにこのプログラムを実行することができます。
	// program_name.exe input.txt output.txt --ph_cut 20 --rem_tracks removed_tracks.txt --xrange 350000 400000
	// input.txtとoutput.txtは必須で、program_name.exeに続けて指定する必要があります。
	// --ph_cut、--xrange、--rem_tracksは省略可能かつ指定順序任意で、省略した場合はそれぞれデフォルト値が使われます。

	try
	{
		// コマンドライン引数を解析する。
		parser.parse_args(argc, argv);
	}
	catch (const std::exception& err)
	{
		// もし引数解析でエラーが発生した場合（大抵は引数の与え方が間違っていた場合）、
		// エラーメッセージを表示し、ヘルプを表示してプログラムを終了する。
		std::cerr << err.what() << std::endl;
		std::cerr << parser;
		std::exit(1);
	}

	std::string input_filename = parser.get<std::string>("input_filename");
	std::string output_filename = parser.get<std::string>("output_filename");
	int ph_cut = parser.get<int>("ph_cut");
	std::vector<double> xrange = parser.get<std::vector<double>>("xrange");
	std::string rem_tracks = parser.get<std::string>("rem_tracks");

	std::cout << std::format("input_filename: {}\n", input_filename);
	std::cout << std::format("output_filename: {}\n", output_filename);
	std::cout << std::format("ph_cut: {}\n", ph_cut);
	if (xrange.size() != 2) std::cout << "xrange:\n";
	else std::cout << std::format("xrange: {:>.1f} {:>.1f}\n", xrange[0], xrange[1]);
	std::cout << std::format("rem_tracks: {}\n", rem_tracks);
}