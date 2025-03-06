#define YAML_CPP_STATIC_DEFINE // <- おまじない。必須です。
#include <yaml-cpp/yaml.h> // <- おまじない。yaml-cppのヘッダファイルをインクルードします。
#include <iostream>
#include <string>
#include <format>

// #### Yamlファイルを用いて外からパラメータを与える方法。
// プログラムの複雑な挙動を制御するためのパラメータは、時にコマンドライン引数だけではとても足りないくらい大量になってしまうこともあります。
// 例えば、0<tanθ<2の範囲で0.2刻みでradial lateralそれぞれの角度精度を与える場合、計20個ものパラメータを与える必要がありますが、
// これをいちいちコマンドライン引数で指定するなんて馬鹿げたことはとてもできません。
// このような場合、大抵はパラメータのリストをテキストファイルなどに書き込み、そのファイル名をコマンドライン引数で指定することが一般的です。
// このときのテキストファイルは、例えばNETSCANだとRuncardという独自形式、HTSなどではJSONファイルを使っていますが、
// 私としては、より記述性、可読性、可搬性に優れたYAMLファイルがよいと思っています。
// YAMLはJSONの上位互換と呼べるもので、JSONファイルをYAMLファイル扱いで読み込むこともでき、かつYAML独自の記法も持っています。
// 何より、コメントを記述できることはJSONにはない絶対的な利点です。

// #### yaml-cpp概要
// YAMLファイルをC++で扱うためのライブラリとしてyaml-cppがあります。以下のGitHubリポジトリで公開されています。
// https://github.com/jbeder/yaml-cpp
// 速度は遅いので数十、数百MB以上のデータを読ませるには不向きですが、非常に使いやすいライブラリです。
// （どうしても速度が欲しければrapidyamlというライブラリもありますが、使いにくいので初心者にはちょっと勧められません）。

// 導入方法（Visual Studioの場合） リソースファイルの画像（yamlcpp1.png、yamlcpp2.png）も参照。
// 1. E:\udd\hayakawa\prg\ThirdPartyにあるyaml-cpp-0.8.0フォルダを、任意のローカルなフォルダなどにコピペする。もちろんGitHubから直接入手しても良い。
// 2. Visual Studioでyaml-cppを使いたいプロジェクトを開く。
// 3. ソリューションエクスプローラー（大抵はVisual Studioのウィンドウ右側にあります）から、プロジェクト名を右クリックし、プロパティを選択。
// 4. 「構成プロパティ」→「VC++ ディレクトリ」→「インクルードディレクトリ」に、コピーしたyaml-cppフォルダ内のincludeフォルダへのパスを追加する。
// 5. 「構成プロパティ」→「VC++ ディレクトリ」→「ライブラリディレクトリ」に、コピーしたyaml-cppフォルダ内のlibフォルダへのパスを追加する。
// 6. 「構成プロパティ」→「リンカー」→「入力」→「追加の依存ファイル」にて、
//    左上をDebugにした状態でyaml-cppd.libを追加し右下の「適用」をクリック、その後左上をReleaseに変更してyaml-cpp.libを追加する。
// 7. 「構成プロパティ」→「C/C++」→「言語」→「C++言語標準」→「/std:c++17」ないし数字が17以上のものを選択。/std:c++20以上か/std:c++latestを推奨。

struct Material
{
	std::string name;
	double thickness;
	double radiation_length;
};
struct Parts
{
	std::string name;
	std::vector<std::string> structure;
};

int main()
{
	double thr_chi_square = 30;
	std::string cut_mode;
	std::vector<std::string> ecc_dirs;
	std::vector<double> rad_acc;
	std::vector<double> lat_acc;
	Material emulsion;

	std::vector<Material> vmat;
	std::vector<Parts> vparts;
	try
	{
		// ----------YAMLファイルの読み込み----------
		YAML::Node params = YAML::LoadFile("params.yaml");

		// ----------YAMLファイル中のパラメータの取得----------
		thr_chi_square = params["ThrChiSquare"].as<double>();
		cut_mode = params["CutMode"].as<std::string>();

		ecc_dirs = params["ECCDirs"].as<std::vector<std::string>>();

		rad_acc = params["RadAngAccuracy"].as<std::vector<double>>();
		lat_acc = params["LatAngAccuracy"].as<std::vector<double>>();

		YAML::Node materials = params["Materials"];
		YAML::Node emul = materials["Emulsion"];
		emulsion.thickness = emul["Thickness"].as<double>();
		emulsion.radiation_length = emul["RadiationLength"].as<double>();


		// ----------ちょっと高度なパラメータ取得----------

		// map全体をループしながら取得することもできます。
		for (const auto& n : materials)
		{
			//n.firstで"Base"、"Emulsuon"などのキー、n.secondでそのノードを取得できます。
			Material m;
			m.name = n.first.as<std::string>();
			m.thickness = n.second["Thickness"].as<double>();
			m.radiation_length = n.second["RadiationLength"].as<double>();
			vmat.emplace_back(std::move(m));
		}

		// 同様にsequenceもループしながら取得することができます。
		YAML::Node parts = params["Parts"];
		for (const auto& n : parts)
		{
			Parts p;
			p.name = n["Name"].as<std::string>();
			p.structure = n["Structure"].as<std::vector<std::string>>();
			vparts.emplace_back(std::move(p));
		}

		// ある名前のキーを持つノードが存在するかどうかを調べることもできます。
		if (materials["Air"]) std::cout << "Air exists\n";
		else std::cout << "Air does not exist\n";

		if (materials["Iron"]) std::cout << "Iron exists\n";
		else std::cout << "Iron does not exist\n";
	}
	catch (const YAML::Exception& e)
	{
		// もしYAMLファイルの読み込みでエラーが発生した場合、エラーメッセージを表示してプログラムを終了する。
		std::cerr << e.what() << std::endl;
		exit(-1);
	}

	// ----------取得したパラメータの表示----------
	std::cout << "ThrChiSquare: " << thr_chi_square << std::endl;
	std::cout << "CutMode: " << cut_mode << std::endl;
	for (const auto& ecc_dir : ecc_dirs) std::cout << ecc_dir << std::endl;
	std::cout << " ang rad_acc lat_acc\n";
	for (int i = 0; i < rad_acc.size(); ++i)
	{
		double ang = i * 0.2 + 0.1;
		std::cout << std::format("{:>4.1f} {:>7.4f} {:>7.4f}\n", ang, rad_acc[i], lat_acc[i]);
	}
	std::cout << std::format("Emulsion: thickness {:>.1f}, radiation_length {:>.1f}", emulsion.thickness, emulsion.radiation_length) << std::endl;
	for (const auto& m : vmat)
	{
		std::cout << std::format("Material: name {:>12}, thickness {:>7.1f}, radiation_length {:>7.1f}\n", m.name, m.thickness, m.radiation_length);
	}

	// これ以降に自分の処理を書く。
}