#include <iostream>
#include <string> // <- std::stringクラスを使うために必要
#include <format>

std::string Replace(std::string str)
{
	size_t pos = str.find("Bonjour");
	if (pos != std::string::npos)
		str.replace(pos, 7, "Buon giorno");//Bonjourは7文字なので、7を指定。
	return str;
}

/*
 ##### std::string #####
 std::stringはC++標準ライブラリに含まれる、文字列を扱う機能。
 C言語のchar型配列とは異なり、=による代入、==での比較、+での結合などに対応している。
 文字列の長さを気にする必要もなく、非常に扱いやすい。

					C言語の配列							C++のstd::string
 文字列のコピー		strcpy(str, "Hello")				str = "Hello"
 文字列の比較		strcmp(str, "Hello") == 0			str == "Hello"
 文字列の結合		strcat(str, " World")				str += " World"
 文字列の長さ		strlen(str)							str.length()
 部分文字列の取得		-									std::string sub = str.substr(3, 2)//3文字目から2文字分を抽出 sub == "lo"
 文字列の検索		char* pos = strstr(str, "World")	size_t pos = str.find("World")
 文字列の置換		-									str.replace(6, 5, "Everyone")//6文字目から5文字分をEveryoneに置換
*/

int main()
{
	// 文字列の初期化
	std::string str1 = "Hello";
	std::string str2 = "World";

	// 出力
	std::cout << "str1 : " << str1 << std::endl;
	std::cout << "str2 : " << str2 << std::endl;

	// 文字列の比較
	if (str1 == "Hello")
		std::cout << "str1 == \"Hello\" : Yes" << std::endl;


	// 文字列の結合
	std::string str3 = str1 + " " + str2;
	std::cout << "str3 = str1 + \" \" + str2 : " << str3 << std::endl;

	// 文字列の追加
	str3 += "!";
	std::cout << "str3 += \"!\" : " << str3 << std::endl;

	// 部分文字列の抽出
	std::string str4 = str3.substr(6, 5);//Hello Worldの6文字目から5文字分を抽出。
	std::cout << "str4 = str3.substr(6, 5) : " << str4 << std::endl;

	// 文字列の長さ
	std::cout << "Length of str3 : " << str3.length() << std::endl;

	// 文字のアクセス
	char ch = str3[1];
	std::cout << "str3[1] : " << ch << std::endl;

	// 文字列の検索
	// Worldが見つかった場合、posには'W'の位置が入る。
	size_t pos = str3.find("World");
	if (pos != std::string::npos)//std::string::nposは文字列が見つからなかった場合の返り値
		std::cout << "str3.find(\"World\") :" << pos << std::endl;
	else
		std::cout << "\"World\" not found" << std::endl;

	// 文字列の置換
	// Hello Worldの6文字目から5文字分をEveryoneに置換。
	str3.replace(6, 5, "Everyone");
	std::cout << "str3.replace(6, 5, \"Everyone\") : " << str3 << std::endl;

	// 文字列の挿入
	// 5文字目と6文字目の間に','を挿入。
	str3.insert(5, ",");
	std::cout << "str3.insert(5, \",\") : " << str3 << std::endl;

	// 文字列の削除
	// 5文字目を削除。
	str3.erase(5, 1);
	std::cout << "str3.erase(5, 1) : " << str3 << std::endl;

	// 文字列のクリア
	str3.clear();
	std::cout << "str3.clear() : " << str3 << std::endl;
	if (str3.empty())
		std::cout << "str3.empty() : Yes" << std::endl;

	// std::formatを使った文字列のフォーマット
	str3 = std::format("{} {}", str1, str2);//実はstd::formatはstd::stringを返すので、文字列のフォーマットに使える。
	std::cout << "str3 = std::format(\"{} {}\", str1, str2) : " << str3 << std::endl;


	std::string test1 = "Hello Hola Bonjour Merhaba";
	std::string test2 = "Hej Merhaba";
	std::cout << Replace(test1) << "\n";
	std::cout << Replace(test2) << "\n";
	return 0;
}

/*
問題
std::string型の変数を受け取ってその中から"Bonjour"という文字列を検索し、
見つかった場合は"Buon giorno"に置換して返す、という関数を作ってみましょう。
find()、replace()を使ってください。
std::string Replace(std::string str)
{
	//ここに処理を書く。
	return str;
}

以下のtest1、test2を与えてみて、正しく動作しているか確認しましょう。
std::string test1 = "Hello Hola Bonjour Merhaba";
std::string test2 = "Hej Merhaba";
std::cout << Replace(test1) << "\n";
std::cout << Replace(test2) << "\n";
*/