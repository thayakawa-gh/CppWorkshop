#include <iostream>
#include <format>
#include <map> //<- std::mapを使うために必要

/*
 ######std::mapについて######
 std::mapは、std::vectorやstd::stringなどと同様に、C++標準ライブラリのSTL（Standard Template Library）に含まれるコンテナの一つです。
 std::vectorは任意の型の要素を0から順に番号を付与して格納するもの、std::stringは文字列格納に特化したものでした。
 一方でstd::mapは、キーと要素をペアで格納するコンテナです。
 std::vectorは「0始まりの番号」と「要素」を対応させるものでしたが、std::mapは「キー」と「要素」を対応させるものです。

 std::mapの大きな特徴は、キーが0から連続した整数である必要がなく、キーを用いた要素検索が二分木探索によって行われる点です。
 二分木探索とは簡単に言うと、辞書を引くときのように、今参照している場所より手前か後かを見ながら、目的のキーを探す方法です。
 二分木探索はstd::vectorの線形探索よりも遥かに高速で、
 std::vectorの検索時間が要素数Nに比例する（O(N)と表されます）のに対し、std::mapの検索時間はO(logN)となります。
 したがって、何らかの検索を行うときにはstd::mapを使うことで高速化が期待できます。

 std::mapはその探索の性質上、すべての要素がキーの大小関係に従ってソートされています。
 そのため、std::mapの要素を順番に取り出すと、insertを行った順とは無関係にキーの昇順になります。
*/

int main()
{
	std::map<int, std::string> m;

	// 1. 添字演算子[]を用いた要素の挿入とアクセス（濫用はおすすめしません）
	// std::mapでは、存在しないキーにアクセスするとその要素が自動的に作成されます。
	// 今、10というキーに対応する要素は存在しませんが、m[10]のようにアクセスすることで、勝手に要素が挿入され、"ten"が代入されます。
	m[10] = "ten";
	// 逆に、存在するキーにアクセスすると、その要素の値を取得できます。
	std::cout << m[10] << std::endl; // ten


	// 2. insertメンバ関数を用いた要素の挿入
	// 添字演算子を用いる場合、キーに対応する要素が存在しない場合に勝手に要素が挿入されてしまいます。
	// この動作が望ましくない場合、insert関数を使うことができます。
	m.insert(std::make_pair(20, "twenty"));// key 20, value "twenty"を挿入

	// ちなみに、insertの戻り値を受け取ることもできます。
	// 挿入に成功した場合、res.firstには挿入された要素のイテレータが、res.secondにはtrueが入ります。
	std::pair<std::map<int, std::string>::iterator, bool> res = m.insert(std::make_pair(30, "thirty"));// key 30, value "thirty"を挿入
	if (res.second) std::cout << "Insertion succeeded, key is " << res.first->first << ", value is " << res.first->second << std::endl;
	// 一方すでにキーが存在していた場合挿入は行われず、res.secondにはfalseが入り、当該キーの要素へのイテレータがres.firstに入ります。
	std::pair<std::map<int, std::string>::iterator, bool> res2 = m.insert(std::make_pair(30, "THIRTY"));// キー30はすでに存在しているため、挿入に失敗します。
	if (!res2.second) std::cout << "Insertion failed, key is " << res2.first->first << ", value is " << res2.first->second << std::endl;


	// 3. findメンバ関数による検索
	// findメンバ関数は、指定したキーが存在するかどうかを調べ、存在する場合はそのイテレータを返します。
	// もし存在しなかった場合、イテレータはm.end()と一致します。
	// さらにこのイテレータからは、キーはit->first、値はit->secondで取得できます。
	// 添字演算子と異なり存在しないキーの要素を勝手に生成されることがないので、純粋に検索したい場合にはこちらを使いましょう。
	std::map<int, std::string>::iterator it = m.find(10);
	if (it == m.end()) std::cout << "Key " << it->first << " not found" << std::endl;
	else std::cout << "Key " << it->first << " found, value is " << it->second << std::endl;

	std::map<int, std::string>::iterator it2 = m.find(40);
	if (it2 == m.end()) std::cout << "Key 40 not found" << std::endl;
	else std::cout << "Key 40 found, value is " << it2->second << std::endl;

	// 4. for文による要素の走査
	// std::mapの要素は、すべてキーの昇順に並べられています。挿入順は関係ありません。
	for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
	{
		std::cout << "Key " << it->first << ", value " << it->second << std::endl;
		// Key 10, value ten
		// Key 20, value twenty
		// Key 30, value thirty
	}
	// 例えばここで新たにキー0を挿入したとしても、for文の出力結果はキーの昇順になので、キー0が最初に表示されます。
	m.insert(std::make_pair(0, "zero"));
	for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
	{
		std::cout << "Key " << it->first << ", value " << it->second << std::endl;
		// Key 0, value zero
		// Key 10, value ten
		// Key 20, value twenty
		// Key 30, value thirty
	}


	// 5. 非整数のキー
	// std::mapはキーに整数を使う必要はありません。例えば、std::stringをキーにすることもできます。
	// 正確に言えば、比較演算子 "<" で大小関係を求められる型であれば、何でもキーとして使えます。
	std::map<std::string, int> m2;
	m2.insert(std::make_pair("apple", 180));
	m2.insert(std::make_pair("banana", 250));

	std::map<std::string, int>::iterator it3 = m2.find("apple");
	if (it3 != m2.end()) std::cout << it3->first << " is " << it3->second << " yen" << std::endl;
}

/*
 問題
 以下は2024年11月11日に行われた第103代首相の首相指名選挙における衆議院、参議院それぞれの投票結果です。
 衆議院、参議院の結果を別々に、名前をキー、得票数を値とするstd::map<std::string, int>にinsertメンバ関数を用いて格納してください。
 その後、参議院の被指名者の一覧に対して衆議院のstd::mapから得票数をfindメンバ関数で検索し、
 参議院の全被投票者の名前、参議院での得票数、衆議院での得票数を表示してください。
 std::mapに存在しなかった場合は得票数は0と表示してください。

 衆議院
石破茂 221
野田佳彦 151
馬場伸幸 38
玉木雄一郎 28
山本太郎 9
田村智子 8
吉良州司 4
神谷宗幣 3
河村たかし 3

 参議院
石破茂 142
野田佳彦 46
馬場伸幸 18
玉木雄一郎 11
田村智子 11
山本太郎 5
伊藤孝恵 1
神谷宗幣 1
末松信介 1
吉良州司 1
茂木敏充 1

*/