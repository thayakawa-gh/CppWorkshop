#include <memory>//<---スマートポインタを使うために必要。
#include <iostream>
#include <format>

/*
 ######スマートポインタについて######
 new/deleteの大きな欠点は、newしたメモリを必ずdeleteしなければならないという点です。
 単純なプログラムならそんなミスはしないかもしれませんが、プログラムが複雑化すると随所でこのような処理が発生し、
 deleteし忘れたり、逆に二重にdeleteしてしまったりといったバグが発生しやすくなります。

 この問題を解決するために、比較的新しいC++ではスマートポインタという機能が導入されています。
 簡単に言えば、deleteすべき時が来たら勝手にdeleteしてくれるポインタのことです。
 現在ではnew/deleteは使わず、状況に応じてスマートポインタを使い分けることが推奨されています。

*/

class Basetrack
{
public:

	Basetrack()
	{
		std::cout << "Basetrack constructor\n";
	}
	Basetrack(int pl, int64_t rawid, int ph, double ax, double ay, double x, double y, double z)
		: pl{ pl }, rawid{ rawid }, ph{ ph }, ax{ ax }, ay{ ay }, x{ x }, y{ y }, z{ z }
	{
		std::cout << "Basetrack constructor\n";
	}
	~Basetrack()
	{
		std::cout << "Basetrack destructor\n";
	}

	double GetAng() const { return std::sqrt(ax * ax + ay * ay); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};

int main()
{
	std::cout << "\n------std::unique_ptr------\n";
	// std::unique_ptrを用いた動的メモリ確保。
	// std::unique_ptrは、ユーザーが明示的にdeleteせずとも、デストラクタが呼ばれるときに確実にdeleteしてくれる、安全なポインタです。
	std::unique_ptr<Basetrack> uptr1 = std::make_unique<Basetrack>(26, 67890, 200085, 0.2541, -1.6531, 12316.2, 191893.3, 10802.3);

	// std::make_uniqueで初期化しない場合、std::unique_ptrはnullptrになります。
	std::unique_ptr<Basetrack> uptr2;
	if (uptr2 == nullptr) // if (!ptr2) でも同じ意味です。
	{
		std::cout << "ptr2 is nullptr\n";
	}
	// std::make_uniqueで既存のstd::unique_ptrを初期化しても構いません。
	// このとき、もし代入するptr2がnullptrでない場合、ptr2の中身は自動的にdeleteされます。
	uptr2 = std::make_unique<Basetrack>(27, 67891, 200086, 0.2542, -1.6532, 12316.3, 191893.4, 10802.4);
	if (uptr2 != nullptr) // if (ptr2) でも同じ意味です。
	{
		std::cout << std::format("ptr2 is not nullptr, rawid == {}\n", uptr2->pl);
	}

	// std::unique_ptrはコピーできません。BasetrackPairと同じく、コピーコンストラクタ・コピー代入演算子がdeleteされているためです。
	// uptr2 = uptr1; ... コンパイルエラー

	// std::unique_ptrはdeleteする必要がありません。しかし、reset関数によって明示的にdeleteすることもできます。
	// この場合、std::unique_ptrはnullptrになります。
	uptr1.reset();
	if (uptr1 == nullptr)
	{
		std::cout << "ptr1 is nullptr\n";
	}


	std::cout << "\n------std::shared_ptr------\n";

	// std::shared_ptrを用いた動的メモリ確保。
	// std::shared_ptrはstd::unique_ptrと同様にdeleteを自動的に行ってくれますが、
	// std::unique_ptrと異なり、複数のstd::shared_ptrが同じアドレスを指すことができます。
	std::shared_ptr<Basetrack> sptr1 = std::make_shared<Basetrack>(28, 67892, 200087, 0.2543, -1.6533, 12316.4, 191893.5, 10802.5);
	std::shared_ptr<Basetrack> sptr2 = sptr1;
	// 今、sptr1とsptr2は同じBasetrackのアドレスを指し、同じBasetrackを共有した状態にあります。そのため、sptr1を変更するとsptr2も変更されたように見えます。
	sptr1->ax += 0.030;//axに0.030を加算
	std::cout << std::format("sptr1->ax == {}, sptr2->ax == {}\n", sptr1->ax, sptr2->ax);

	// std::shared_ptrは参照カウントという変数を持っています。これは、同じアドレスを指すstd::shared_ptrがいくつあるかを示すものです。
	// 例えば、sptr1とsptr2が同じアドレスを指しているので、参照カウントはどちらも2です。
	// use_count関数で参照カウントを取得できます。
	std::cout << std::format("sptr1.use_count() == {}, sptr2.use_count() == {}\n", sptr1.use_count(), sptr2.use_count());

	// ここでsptr2の方をresetしてみます。するとsptr2はsptr1との共有が解消されnullptrになりますが、
	// sptr1がまだ元のBasetrackを指し続けているため、Basetrack自体はまだdeleteされません。
	// 一方、このBasetrackを参照するshared_ptrが1個減ったことで、sptr1の参照カウントが1になります。
	sptr2.reset();
	std::cout << std::format("sptr1->ax == {}\n", sptr1->ax);
	std::cout << std::format("sptr1.use_count() == {}, sptr2.use_count() == {}\n", sptr1.use_count(), sptr2.use_count());

	// sptr1もresetすると、元のBasetrackを指しているshaded_ptrが存在しなくなるため、Basetrack自体がdeleteされます。
	sptr1.reset();
	std::cout << std::format("sptr1.use_count() == {}, sptr2.use_count() == {}\n", sptr1.use_count(), sptr2.use_count());

	// 参照カウントは、resetしたり、shared_ptrがスコープを抜けてデストラクタが呼ばれたりすることで減少します。
	// 参照カウントが0になった時点で、初めてshared_ptrが内蔵するBasetrackのdeleteが行われるのです。

	std::cout << "\n";
}

/*
 問題
 1. new_delete.cppのBasetrackPairクラスをstd::unique_ptrを使って書き換えてください。
    また、BasetrackPairのコピーコンストラクタとコピー代入演算子を、Basetrackを複製するように新たに定義してください。
    最後に、実際にBasetrackPairをコピーしてみて、コピー元とコピー先で各メンバ変数の値が一致すること、
    両者のアドレスが異なることを確認してください。
    なお、スマートポインタのアドレスはptr.get()で取得できます。
    わざわざget()で取得しなくとも、==演算子で直接比較することでアドレスの一致を確認することもできます。

 2. smart_pointerフォルダ下にlinklets.txtというファイルがあります。
    この中にはLinkletになった2本のBasetrackの組（b0、b1）が、次のフォーマットで記録されています。
    pl0 rawid0 ax0 ay0 x0 y0 z0 pl1 rawid1 ax1 ay1 x1 y1 z1
    （今回のファイルはpl0が全て73、pl1が74となっています。これを前提としてコーディングしても構いません。）
    これをstd::shared_ptrに読み込んでみましょう。
    まず、BasetrackPairをstd::shared_ptrを使って書き換えてください。このときコピーコンストラクタとコピー代入演算子は定義せずデフォルトのままにしてください。
    次に、linklets.txtを読み、std::vector<BasetrackPair>に格納してください。
    ただし、もし既に読み込まれたBasetrackPairの中で同一のBasetrackが存在する場合、std::shared_ptrを共有してください。
    最後にuse_count関数を使って、複数のLinkletに共有されていない
    （つまり1本のLinkletにしか使用されていない）Basetrackが何本あるか数えてみましょう。
*/