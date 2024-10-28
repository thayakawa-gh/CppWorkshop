#include <iostream>
#include <vector>
#include <format>


class Microtrack
{
public:
	int pos;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

class Basetrack
{
public:
	int pl;
	int64_t rawid;
	int ph;
	double ax, ay;
	double x, y, z;
};

// クラステンプレートの例。
// 関数テンプレートと同様にtemplate <class ...>と与えます。
// このクラスは、Track1とTrack2という2つの型を受け取り、それらを接続したLinkletクラスを生成します。
// このクラス内では、Track1とTrack2をメンバ変数として保持しており、
// それらのメンバ変数がph、x、y、z、ax、ayを持っていることを前提としています。
template <class Track1, class Track2>
class Linklet
{
public:

	//Track1とTrack2を接続したLinkletクラス。
	Linklet() {}
	Linklet(const Track1& t1_, const Track2& t2_)
		: t1(t1_), t2(t2_)
	{}

	int ph() const { return t1.ph + t2.ph; }
	double x() const {  return (t1.x + t2.x) / 2; }
	double y() const {  return (t1.y + t2.y) / 2; }
	double z() const {  return (t1.z + t2.z) / 2; }
	double ax() const { return (t1.x - t2.x) / (t1.z - t2.z); }
	double ay() const { return (t1.y - t2.y) / (t1.z - t2.z); }

	double dx() const
	{
		double cz = (t1.z + t2.z) / 2;
		double x1 = t1.x + (cz - t1.z) * t1.ax;
	}
	double dax() const { return t1.ax - t2.ax; }
	double day() const { return t1.ay - t2.ay; }

	Track1 t1;
	Track2 t2;
};

int main()
{
	Basetrack bt1{ 27, 12345, 210041, 0.1798, 0.2223, 157089.1, 163130.6, -32413 };
	Basetrack bt2{ 28, 67890, 250063, 0.1773, 0.2171, 156540.7, 162453.1, -35481 };

	// クラステンプレートに対しては、<...>という形で明示的に型情報を与えることが望ましいです。
	// （関数テンプレートのように、コンストラクタの引数から推論させることも可能です。）
	// 以下では、2本のBasetrackを接続したLinkletクラスを生成しています。
	Linklet<Basetrack, Basetrack> bb(bt1, bt2);
	std::cout << bb.ph() << std::endl;//460104
	std::cout << bb.dax() << std::endl;//156814.9

	// 同様に、Base-MicroやMicro-Microという組み合わせでもLinkletクラスを生成できます。
	Linklet<Basetrack, Microtrack> bm;
	Linklet<Microtrack, Microtrack> mm;
}

/*
 問題
 1. basetracks_pl48.txt、basetracks_pl49.txt、microtracks_pl49.txtという3つのファイルを用意しています。
    これらをstd::vector<Basetrack>やstd::vector<Microtrack>に読み込んでください。
    このとき、PL49の飛跡それぞれについては、下記のアフィンパラメータ+dzで座標変換するようにしましょう。
    (a, b, c, d, p, q, dz) = (1.001610, -0.002939, 0.002939, 1.001610, -675.4, -43.3, -814.0)
      座標 : x_=x*a+y*b+p, y_=x*c+y*d+q、z_=z+dz
      角度 : ax_=ax*a+ay*b, ay_=ax*c+ay*d
    （BasetrackとMicrotrackそれぞれのアフィン変換を行うのは面倒なので、これも関数テンプレートにすると良いかもしれませんね。）

 2. 関数テンプレートのときに出題したJudgeConnectivity関数を用いて、接続可能な飛跡の組み合わせを全て取り出し、
    std::vector<Linklet<Basetrack, Basetrack>>またはstd::vector<Linklet<Basetrack, Microtrack>>に格納する関数Connectを作成してください。
    template <class Track1, class Track2>
    std::vector<Linklet<Track1, Track2>> Connect(const std::vector<Track1>& tracks1, const std::vector<Track2>& tracks2)
    {
        この中身を実装する。
    }
    その後、1. で読み込んだ飛跡情報をこの関数に与え、接続可能な飛跡の組み合わせを取り出してください。
	こちらで試した限り、Base-Base接続で5本、Base-Micro接続で11本のLinkletが作られました。

 3. JudgeConnection関数をクラスのメンバ変数として定義し、Connect関数に外部から与えられるようにしてみましょう。
    class DposDang
    {
    public:
        template <class Track1, class Track2>
        bool JudgeConnection(const Track1& t1, const Track2& t2)
        {
            ....
        }
    };
    template <class Track1, class Track2, class Cut>
    std::vector<Linklet<Track1, Track2>> Connect(const std::vector<Track1>& tracks1, const std::vector<Track2>& tracks2, const Cut& cut)
    {
        この中身を実装する。
    }
    DposDang以外にもいろいろな条件（PH、radial-lateralでの位置角度差）のクラスを作成し、Connect関数に与えてみましょう。
*/