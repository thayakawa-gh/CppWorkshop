#include <memory>
#include <iostream>
#include <format>

class B;
class A
{
public:

	~A()
	{
		std::cout << "A destructor\n";
	}

	std::shared_ptr<B> ptr;
};
class B
{
public:
	~B()
	{
		std::cout << "B destructor\n";
	}

	std::shared_ptr<A> ptr;
};


/*
 ######std::shared_ptrの循環参照について######
 std::shared_ptrは参照カウントを用いてメモリ管理を行います。
 ここで、2個のstd::shared_ptrが互いに参照し合うような状況を考えてみましょう。
 実は、このようなshared_ptrの使い方はメモリリークを起こすことで知られています。
*/

int main()
{
	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();

	// 2つのshared_ptrが互いに参照し合うように設定
	a->ptr = b;
	b->ptr = a;

	return 0;

	// ここでreturnすれば、aとbはスコープを抜けてデストラクタが呼ばれるはずですが、
	// 循環参照をしてしまうとA、Bのdeleteが呼ばれなくなり、正しくメモリを解放してくれません。

	// 何が起きているか、処理を一つずつ追いかけてみましょう。
	// まず、return 0となったことで、aとbのデストラクタが呼ばれます。AやBのdeleteやデストラクタはまだ呼ばれません。あくまでshared_ptrのデストラクタです。
	// まずaから考えてみます。
	// aのデストラクタが呼ばれたことで、Aを参照しているshared_ptrが1個減り、Aへの参照カウントが1になります。
	// 一方、bの参照カウントは2のままです。aのデストラクタを呼んでも、A自体はb.ptrが参照しているため削除されず、
	// b.ptr->ptrが現在もB自身を参照してしまっているからです。
	// この状況でbのデストラクタが呼ばれると、b自身はnullptrになり、Bへの参照カウントが1減りますが、
	// Bが内包していたb.ptr->ptrがまだB自身を参照し続けており、参照カウントが1残ってしまいます。
	// ということは、Bのデストラクタが呼ばれません。
	// BはAへの参照をも持っているため、Bが残る限りAのデストラクタも呼ばれません。

	/*
	const A& aref = *a;
	const B& bref = *b;
	std::cout << std::format("a.use_conut() = {}, a.ptr.use_count() = {}\n", a.use_count(), a->ptr.use_count());
	std::cout << std::format("b.use_conut() = {}, b.ptr.use_count() = {}\n", b.use_count(), b->ptr.use_count());

	a.reset();
	std::cout << std::format("b.use_conut() = {}, b.ptr.use_count() = {}\n", b.use_count(), b->ptr.use_count());
	std::cout << std::format("aref.ptr.use_count() = {}\n", aref.ptr.use_count());

	b.reset();
	std::cout << std::format("aref.ptr.use_count() = {}\n", aref.ptr.use_count());
	std::cout << std::format("bref.ptr.use_count() = {}\n", bref.ptr.use_count());
	*/
}