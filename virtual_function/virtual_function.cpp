#include <memory>
#include <iostream>
#include <format>
#include <vector>

/*
 継承の持つひとつ面白い機能として、仮想関数があります。
 これは、基底クラスで予め任意のメンバ関数に"virtual"を付与して宣言しておき、
 派生クラスでその関数を書き換えられるようにするものです。

 いえ、厳密にいえば、仮想関数でないメンバ関数であっても、派生クラスでの上書きは可能です。
 ただし、仮想関数であるか、そうでないかによって、関数が呼ばれたときに「どの関数が呼ばれるのか」が異なります。

 例えば、派生クラスは基底クラスのポインタや参照で指し示されることがあります。
 Base* d = new Derived;
 この場合、dは本当はDerived型のオブジェクトを指しているのですが。
 今はBase型のポインタに格納されているため、Base型として扱われます。
 したがって、dはBase型のメンバにしかアクセスすることができません。
 d->normal_function(); // Base::normal_function  と表示されます。

 しかし、仮想関数の場合は異なります。
 たとえBase型のポインタに代入されていても、きちんとDerived側の関数を呼んでくれます。
 d->virtual_function(); // Derived::virtual_function  と表示されます。

 この振る舞いは、std::unique_ptrのようなスマートポインタを使った場合も同様です。
 std::unique_ptr<Base> d = std::make_unique<Derived>();
 d->virtual_function(); // Derived::virtual_function  と表示されます。

 このように、基底クラスのポインタや参照からでも派生クラスで定義した関数を実行できるようにするものが仮想関数です。



 仮想関数にはデメリットもあります。
 まず、仮想関数を一つでも定義すると、そのクラスの大きさはポインタ1個分大きくなります。
 例えば、derived_classの方で例として出したBasetrackSubsetは64バイトの大きさを持ちます。
 （56バイトでは？と思うかもしれませんが、64です。これには構造体のアライメントがかかわっています。）
 一方、もしBasetrackSubsetに1個でも仮想関数を定義すると、大きさは72バイトになります。
 したがって、データの格納を担うクラスに仮想関数を作ることはあまり推奨できません。
 しかしながら、一般に継承を用いるときは、最低限virtualなデストラクタを定義することが推奨されています。
 仮想関数と同じように、Baseポインタや参照に変換してしまったDerived型変数は、そのDerived型のデストラクタを呼ぶにはvirtualにする必要があるためです。
 「継承するときにはvirtualデストラクタを定義する」「仮想関数（virtualなデストラクタ含む）があるとサイズが8バイト増える」
 ……ということは、根本的に、データ格納クラスを継承で定義することはあまりよくないとも言えます。
 BasetrackSubsetとBasetrackFullは、このあたりの振る舞いを分かっている人間がきちんと管理して使うのならよいのですが、
 分からないうちに安易に使うべきではないかもしれません。

 また、仮想関数は関数呼び出しのオーバーヘッドが大きいです。
 細かく話すとややこしいので省略しますが、仮想関数は最適化が効きにくく、仮想関数の処理を呼ぶのに通常の関数よりもわずかに時間がかかる場合が多いのです。
 つまり、仮想関数を過度に多用するとそのプログラムの処理が遅くなる可能性があります。
 たかだか1万回、1億回程度の仮想関数呼び出しでは大して影響はないでしょう。が、100億回、1兆回と増えてくると、顕著に影響してくるかもしれません。
*/


class Base
{
public:

	// 派生クラスを定義する場合、デストラクタをvirtualにしておくことが推奨されます。
	virtual ~Base()
	{
		std::cout << "Base destructor\n";
	}

	// 通常の関数
	void normal_function() const
	{
		std::cout << "Base::normal_function\n";
	}

	void normal_function_calling_virtual() const
	{
		virtual_function();
	}

	// 仮想関数
	virtual void virtual_function() const
	{
		std::cout << "Base::virtual_function\n";
	}
};

class Derived : public Base
{
public:

	virtual ~Derived()
	{
		std::cout << "Derived destructor\n";
	}

	void normal_function() const
	{
		std::cout << "Derived::normal_function\n";
	}

	virtual void virtual_function() const override
	{
		std::cout << "Derived::virtual_function\n";
	}
};

int main()
{
	Base b;
	Derived d;

	// ここでは、Base、Derivedの変数を用意し、それぞれの関数を呼び出しています。
	// 重要なことは、b、dともにそれぞれBase型、Derived型で宣言されていることです。
	// つまり、b、dという変数は、それぞれ自身がBase型、Derived型であるということを"知っています"。

	std::cout << "\n------normal_function------\n";
	b.normal_function();// Base::normal_function
	d.normal_function();// Derived::normal_function

	std::cout << "\n------virtual_function------\n";
	b.virtual_function();// Base::virtual_function
	d.virtual_function();// Derived::virtual_function

	// bの場合はBase内で定義した関数が、dの場合はDerived内で定義した関数が呼ばれています。
	// これはそれほど不思議な振る舞いではないと思います。



	// 次に、b、dをBase型の参照に変えてみましょう。
	// ここで重要なことは、d_refの参照先であるdはもともとDerived型であったにもかかわらず、今はBase型の扱いになっていることです。
	// 言い換えると、以下でd_refは、"自身がDerivedであったということを忘れている"のです。
	// （C++では、"変数の型が何であるか"が非常に重要な意味を持ちます。）
	Base& b_ref = b;
	Base& d_ref = d;

	std::cout << "\n------normal_function------\n";
	b_ref.normal_function();// Base::normal_function
	d_ref.normal_function();// Base::normal_function

	std::cout << "\n------virtual_function------\n";
	b_ref.virtual_function();// Base::virtual_function
	d_ref.virtual_function();// Derived::virtual_function

	// ここで、b_ref.normal_function()とd_ref.normal_function()はどちらもBase::normal_function()が呼ばれています。
	// これは、b_ref、d_refがどちらもBase型として扱われているからです。
	// 特に、d_refは自身がDerived型であったことを忘れてしまっているのです。

	// 一方で、b_ref.virtual_function()とd_ref.virtual_function()ではそれぞれ、
	// もともとの自分の型であるBase型、Derived型の関数が呼ばれています。
	// これが仮想関数の持つ性質です。
	// 今自分自身の型がBase型であっても、真の型がDerivedでさえあれば、仮想関数は派生クラスで定義された仮想関数を呼び出してくれます。


	std::cout << "\n";


}