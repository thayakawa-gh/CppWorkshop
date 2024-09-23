#include <iostream>
#include <format>
#include <vector>

/*
 #####スタック領域とヒープ領域#####
 プログラムがメモリを使う際、メモリは大きく分けてスタック領域とヒープ領域に区分されます。

 スタック領域はプログラム実行時にあらかじめ割り当てられるメモリ領域です。
 例えばint x = 4;のようにローカルな変数を宣言すると、これらはスタック領域に割り当てられ、関数を抜けるときなどに自動的に開放されます。
 スタック領域はメモリの割り当てや解放が高速である一方、割り当てられるメモリのサイズはコンパイル時に決まる（普通は数MB）ため、
 実行時にメモリのサイズを変更することはできず、スタック領域のサイズを超える長大な配列などを格納することも出来ません。

 ヒープ領域はプログラム実行中に必要分だけ動的に確保されるメモリ領域です。
 C言語を使ったことのある人はmalloc/freeという関数に見覚えがあるかもしれません。これらはヒープ領域にメモリを確保/解放する関数です。
 C++にはnew/deleteという演算子が追加され、malloc/freeに代わりヒープ領域にメモリを確保/解放するために使わています。
 これらの手段を用いてヒープ領域にメモリを確保することを一般に「動的メモリ確保」と呼びます。
 ヒープ領域はスタック領域と異なり、PCに搭載されたメモリ容量（仮想メモリも含む）の限界までメモリを使用することができます。
 一方、ヒープ領域に確保されたメモリはdeleteを使って解放しないとメモリリークが発生するなど、管理が難しいという難点もあります。
 さらにヒープ領域は確保・解放が遅く、安易に使うとプログラムの速度低下に繋がるため、使い所を選ばなければなりません。

 実はstd::stringやstd::vectorなどは内部的にはヒープ領域にメモリを確保しています。
 そのため、これらは非常に柔軟で大きなデータの格納も可能なのですが、その分メモリ確保・解放のオーバーヘッドがあります。
 関数の引数としてstd::vectorなどを渡すときにコピーではなく参照渡しをするのは、このヒープ領域の再確保や解放のオーバーヘッドを避けるためです。
 コピーすると元のstd::vector等と同じ分のメモリをヒープ領域に確保する必要があるため、非常に時間がかかるのです。
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

class BasetrackPair
{
public:
	// Basetrack2本分の情報をヒープに確保して保有するクラス。
	// new/deleteをコンストラクタ、デストラクタで呼び出しています。

	BasetrackPair(const Basetrack& bt1, const Basetrack& bt2)
		: ptr{ new Basetrack(bt1), new Basetrack(bt2) }
	{}
	~BasetrackPair()
	{
		delete ptr[0];
		delete ptr[1];
	}

	// このようなクラスは、コピーコンストラクタ・コピー代入演算子を必ず実装、ないし削除しなければなりません。
	// 例えば、もしそれらを実装せずデフォルトの挙動を用いる場合、実質的には以下のようなコードが実行されることになります。
	// 
	// BasetrackPair(const BasetrackPair& other) : ptr{ other.ptr[0], other.ptr[1] } {}
	// BasetrackPair& operator=(const BasetrackPair& other) { ptr[0] = other.ptr[0]; ptr[1] = other.ptr[1]; return *this; }
	// 
	// この場合、ptr[0]とptr[1]はotherと同じBasetrackを指すことになります。
	// すると、それらのBasestrackは、自分自身のデストラクタと、otherのデストラクタの両方でdeleteされてしまいます。
	// つまり二重deleteが発生し、プログラムがクラッシュします。

	// これを避けるためには、コピーコンストラクタ・コピー代入演算子を自分で実装して、二重deleteを防ぐようにするか、
	// そもそもコピー不可能にしてしまう方法もあります。
	// (本当に良い実装にするならムーブコンストラクタ・ムーブ代入演算子も実装するべきですが、ここでは省略します。)

	// コピーそのものを禁止する場合、次のようにできます。
	// こうすると、次のようなコピーは不可能になり、結果的に二重deleteを防げます。
	// BasetrackPair btp1;
	// BasetrackPair btp2 = btp1; ... コンパイルエラー
	BasetrackPair(const BasetrackPair& other) = delete;
	BasetrackPair& operator=(const BasetrackPair& other) = delete;

	Basetrack* ptr[2];
};

int main()
{
	// newによってdouble型の変数をヒープ領域に確保しています。ヒープにメモリを確保することを一般に「動的メモリ確保」と呼びます。
	// この方法ならPCに搭載されたメモリを最大限利用できますが、
	// その代わりnew/deleteは非常に遅いので、使い所を選ぶ必要があります。
	double* a = new double(3.14);
	std::cout << *a << "\n";

	// ヒープ領域に確保したメモリをdeleteで解放しています。これをしないと、
	// 使用されなくなった変数がヒープ領域に確保されたまま残り続け、メモリを圧迫してしまいます（メモリリーク）。
	// プログラムを終了すればこのようなメモリも全部丸ごと解放されますが、飛跡処理はメモリ使用量との戦いになることも往々にしてあるので、
	// 無駄遣いしないためにも都度きちんと開放すべきです。
	delete a;

	// std::vectorなどのクラス、自分で設計したクラスなどもnewで確保できます。
	// newが呼ばれたとき、それがクラスである場合、コンストラクタも一緒に呼ばれます。
	Basetrack* bt = new Basetrack(25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0);
	std::cout << std::format("pl = {}, rawid = {}, ra = {}\n", bt->pl, bt->rawid, bt->GetAng());

	// deleteするとき、クラスの場合はデストラクタも呼ばれます。
	delete bt;
	//std::cout << bt->ax << "\n"; // btはもうdeleteされて消滅しているので、その中身にアクセスしてはいけません。



	// クラスのメンバ変数として持たせたポインタにnewでメモリを割り当てるという活用方法もあります。
	// この場合、BasetrackPairはポインタ2個分（16Bytes）の大きさを持ち、この16Bytes分のメモリはスタック領域に確保されます。
	// 一方、BasetrackPairが持つBasetrackはnewによってヒープ領域に確保されます。
	BasetrackPair pair{ Basetrack{ 25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 10331.6 },
						Basetrack{ 26, 67890, 200085, 0.2541, -1.6531, 12316.2, 191893.3, 10802.3 } };
	std::cout << pair.ptr[0]->pl << " " << pair.ptr[1]->pl << "\n";
	//BasetrackPair pair2(pair); ... コピーコンストラクタは削除されているので、コンパイルエラー。


	// std::vectorそれ自体は、実は24バイトの大きさしか持ちません（64bitの場合）。
	// 以下のようにstd::vectorを宣言すると、この24バイト分はスタック領域に確保されます。
	// ではstd::vectorが持つ長大な配列はどこにあるのかというと、ヒープ領域に確保されています。
	// std::vectorはあくまで、それらのヒープ領域に確保された配列の先頭要素へのポインタを持っているだけです。
	std::vector<double> vec1;
	vec1.resize(10, 0.0);// std::vectorに要素を格納すると、ヒープ領域のメモリ確保が行われます。

	// 以下のようにstd::vectorをコピーすると、vec2は新たにvec1と同じ要素数のメモリをヒープ領域に確保し、
	// さらにvec1の要素をvec2にコピーします。
	// このため、std::vectorのコピーは非常に遅く、プログラムのパフォーマンスに甚大な影響を与えることがあります。
	// だからこそ、std::vectorなどのクラスを関数の引数として渡すときは、コピーは必要なとき以外は避け、参照渡しをすることが推奨されているのです。
	std::vector<double> vec2 = vec1;
}

/*
 問題
 1. 以下のような処理を作成してください。
    * std::vector<double*> vecという変数を用意し、1.0から10.0までの10個のdouble型変数をnewで確保してvecに格納する。
    * その後、vecの要素を全てdeleteする。

 問題
 2. BasetrackPairクラスのコピーコンストラクタ・コピー代入演算子は、上の例では削除されていました。コピーするような
    このBasetrackPairのコピーコンストラクタ・コピー代入演算子を、新たに定義してください。
    このとき、二重deleteを避けるために、
	Basetrackのアドレスのコピーではなく、Basetrack変数自体をコピーするようにしてください。
*/