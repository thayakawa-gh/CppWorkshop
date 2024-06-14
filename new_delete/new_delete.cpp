#include <iostream>
#include <format>

class Basetrack
{
public:
	Basetrack(int pl_, int64_t rawid_, int ph_, double ax_, double ay_, double x_, double y_, double z_)
		: pl(pl_), rawid(rawid_), ph(ph_), ax(ax_), ay(ay_), x(x_), y(y_), z(z_)
	{}

	double GetAng() const { return std::sqrt(ax * ax + ay * ay); }

	int pl;
	int64_t rawid;
	int ph;
	double ax, ay, x, y, z;
};

/*
 #####スタック領域とヒープ領域#####
 スタック領域はプログラム実行時にあらかじめ割り当てられるメモリ領域。
 例えばint x = 4;のようにローカルな変数を宣言すると、これらはスタック領域に割り当てられ、関数を抜けるときなどに自動的に開放される。
 スタック領域はメモリの割り当てや解放が高速であるが、割り当てられるメモリのサイズはコンパイル時に決まる（普通は数MB）ため、
 実行時にメモリのサイズを変更することはできないし、長大な配列などを格納することも出来ない。

 ヒープ領域はプログラム実行中に必要分だけ動的に確保されるメモリ領域。
 C言語でおなじみのmalloc/freeはヒープ領域にメモリを確保/解放する関数である。
 またC++にはnew/deleteという演算子があり、これもヒープ領域にメモリを確保/解放するために使われる。
 スタック領域と異なり、PCに搭載されたメモリ容量の限界までメモリを使用することができる。
 一方、ヒープ領域に確保されたメモリはdeleteを使って解放しないとメモリリークが発生するなど、管理が難しい。
 さらにヒープ領域は確保・解放が遅いため、安易に使うとプログラムの速度低下に繋がりうる。

 実はstd::stringやstd::vector、std::mapも内部的にはヒープ領域にメモリを確保している。
 そのため、これらは非常に柔軟で大きなデータの格納も可能であるが、その分メモリ確保・解放のオーバーヘッドがある。
 関数の引数としてstd::vectorなどを渡すときに参照渡しをするのは、このヒープ領域の再確保や解放のオーバーヘッドを避けるためである。
*/

int main()
{
	// newによってdouble型の変数をヒープ領域に確保する。
	double* a = new double(3.14);
	std::cout << *a << "\n";

	// ヒープ領域に確保したメモリを解放する。newで確保したメモリはdeleteで解放しないとメモリリークが発生する。
	delete a;

	// 自分で設計したクラスもnewで確保できる。
	// mallocとの大きな違いは、newは"コンストラクタを呼ぶ"という点。
	Basetrack* bt = new Basetrack{ 25, 12345, 220142, 0.2446, -1.5907, 12605.2, 190451.0, 0.0 };
	// btのメンバ変数やメンバ関数にアクセスするにはアロー演算子を使う。
	std::cout << std::format("pl = {}, rawid = {}, ra = {}\n", bt->pl, bt->rawid, bt->GetAng());

	delete bt;

	//std::cout << bt->ax << "\n"; // btはもうdeleteされて消滅しているので、その中身にアクセスしてはいけない。
}