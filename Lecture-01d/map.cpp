#include <iostream>
#include <map>

int main()
{
	// mapの初期化
	std::map<int, std::string> map;

	// 要素の追加
	// std::mapはmap[x]のようにアクセスを試みたとき、map[x]が存在しなければ勝手にその要素が追加される。
	map[1] = "one";
	map[3] = "three";

	// もう一つの要素追加
	map.insert(std::make_pair(5, "Five"));

	// 要素へのアクセス
	std::cout << "map[3]: " << map[3] << std::endl;

	// mapの全要素の表示
	for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	// 要素の更新
	map[3] = "drei";
	std::cout << "Updated map[3]: " << map[2] << std::endl;

	// mapのサイズ
	std::cout << "Size of map: " << map.size() << std::endl;

	// 要素の削除
	map.erase(3);
	std::cout << "Map after erasing key 3:" << std::endl;
	for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	// 要素の検索
	auto it = map.find(1);
	if (it != map.end()) {
		std::cout << "Element with key 1 found: " << it->second << std::endl;
	}
	else {
		std::cout << "Element with key 1 not found" << std::endl;
	}

	// すべての要素のクリア
	map.clear();
	std::cout << "Map after clear, is map empty? " << (map.empty() ? "Yes" : "No") << std::endl;

	// 他の初期化方法
	std::map<int, std::string> map2 = {
		{ 2, "two" },
		{ 4, "four" },
		{ 6, "six" }
	};
	std::cout << "map2:" << std::endl;
	for (const auto& pair : map2) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}

	return 0;
}
