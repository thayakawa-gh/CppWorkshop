# CppWorkshop
2024年度に某研究室で開催したC++勉強会の資料です。

内容はC++の基本的な使い方に関するものですが、C言語の基本（変数、関数、if/else、for/whileなど）を習得していることを前提としています。
研究室内でのデータ形式や解析手法を具体例として取り上げていますので、類似の技術を使用する現場での勉強用資料として利用してください。

本資料はこのページ右上あたりの緑色のCodeボタン->Download ZIPでダウンロードし展開した後、Visual Studio 2022以降で開くことができます。

## 内容について
それぞれいくつかのトピックと演習問題のセットになっています。演習問題は各資料の末尾コメントに、解答はAnswer-〇〇プロジェクト下にあります。


### 第01回 [string](string)、[format](format)
`std::string`、`std::format`による文字列操作
### 第02回 [for_loop](for_loop)、[iterator](iterator)、[vector](vector)
for loopの復習、イテレータ、`std::vector`による配列操作
### 第03回 [class](class)、[constructor](constructor)、[member_function](member_function)
クラスの取り扱いの基礎
### 第04回 [read_text](read_text)、[read_text_faster](read_text_faster)、[write_text](write_text)
C++流のファイルの読み書き
### 第05回 [reference](reference)、[pointer](pointer)、[dangling](dangling)
参照型/ポインタ型の取り扱い
### 第06回 [new_delete](new_delete)
動的メモリ確保、解放
### 第07回 [unique_ptr](unique_ptr)、[shared_ptr](shared_ptr)、[cyclic_reference](cyclic_reference)
new/deleteを置き換えるスマートポインタの使い方
### 第08回 [derived_class](derived_class)、[virtual_function](virtual_function)、[utilization_of_virtual_function](utilization_of_virtual_function)
派生クラスと仮想関数
### 第09回 [function_template](function_template)、[class_template](class_template)
関数テンプレート、クラステンプレート
### 第10回 [map](map)、[map_with_any_type](map_with_any_type)、[unordered_map](unordered_map)
`std::map`、`std::unordered_map`の使い方
### 第11回 [hash_with_pos_and_ang](hash_with_pos_and_ang)
位置角度を用いたハッシュ化の具体例

### 番外編 [argparse_test](argparse_test)、[yamlcpp_test](yamlcpp_test)
プログラムのパラメータを外部から受け取る（ソフトコーディング）方法の例として、argparseとyaml-cppの使い方
