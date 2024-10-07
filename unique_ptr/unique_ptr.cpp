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
	uptr2 = std::make_unique<Basetrack>(26, 67890, 200085, 0.2541, -1.6531, 12316.2, 191893.3, 10802.3);
	// std::unique_ptrはコピーできません。BasetrackPairと同じく、コピーコンストラクタ・コピー代入演算子がdeleteされているためです。
	// uptr2 = uptr1; //... コンパイルエラー

	// std::unique_ptrはdeleteする必要がありません。スコープ{}を抜けるときに勝手にdeleteされます。
	// しかし、reset関数によって明示的にdeleteすることもできます。
	// この場合、std::unique_ptrはnullptrになります。
	uptr1.reset();
	if (uptr1 == nullptr)
	{
		std::cout << "ptr1 is nullptr\n";
	}
}

/*
 問題
 new_delete.cppのBasetrackPairクラスをstd::unique_ptrを使って書き換えてください。
 また、BasetrackPairのコピーコンストラクタとコピー代入演算子を、Basetrackを複製するように新たに定義してください。
 最後に、実際にBasetrackPairをコピーしてみて、コピー元とコピー先で各メンバ変数の値が一致すること、
 両者のアドレスが異なることを確認してください。
 なお、スマートポインタのアドレスはptr.get()で取得できます。
 わざわざget()で取得しなくとも、==演算子で直接比較することでアドレスの一致を確認することもできます。

*/