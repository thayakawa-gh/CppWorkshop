#include <vector>
#include <format>
#include <iostream>

/*
 ######テンプレートについて######
 C++にはテンプレートという強力な機能があります。
 今までstd::vectorやstd::unique_ptrなどのクラスの使い方を勉強する中で、
 std::vector<double>の<...>は一体何なのかと疑問を持った人も多かろうと思います。
 この<...>こそがテンプレートで、あるクラスに対して何らかの型情報などを伝達する役割があります。
 例えば、std::vectorそれ自体は格納するリストの型情報を持ちません。double型なのか、int型なのか、Basetrack型なのかを知らないのです。
 最初はこの型を適当に（関数の引数のように）Tなどと仮置きして	std::vectorを設計しておき、
 std::vector<double>のように指定されたときにはじめてTをdoubleに置換し、double型用std::vectorを生成しているのです。

 テンプレートは極めて強力な機能で、これをマスターするとプログラミングの自由度が大幅に向上し、再利用性に優れた設計が可能になります。
 一方で、文法が複雑で可読性が悪化しやすいなどのデメリットもあり、濫用は禁物です。
 ここではテンプレートのごく初歩的な部分だけを紹介します。

 テンプレートには大別して2種類あります。
 1. クラステンプレート
 2. 関数テンプレート
 （変数テンプレートやエイリアステンプレートもありますが、およそ皆さんが使うことはないだろうと思います。）


*/



int main()
{


}