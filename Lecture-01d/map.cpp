#include <iostream>
#include <map>

/*
 ##### std::map #####
 std::map��C++�W�����C�u�����Ɋ܂܂��A�A�z�z��������@�\�B
 C����W���ɂ͂��������ގ��@�\�͂Ȃ��AC++�ŐV���ɒǉ����ꂽ�B
 �A�z�z��Ƃ́A�L�[�ƒl���y�A�ɂ��Ċi�[����f�[�^�\���ŁA�L�[���g���Ēl���������邱�Ƃ��ł���B
 �S�v�f�̒�����L�[�̒l��T������̂������A�v�f�̒ǉ���폜����r�I�����ɍs����B
 
  ������					std::map<int, std::string> map = { {1, "one"}, {3, "three"} };
  �v�f�̒ǉ�				map.insert(std::make_pair(5, "five"))
  �v�f�̃A�N�Z�X			map[5]
  �v�f�̍폜				map.erase(5)//�L�[��5�Ɉ�v����v�f���폜
  �v�f�̌���				std::map<int, std::string>::iterator it = map.find(5)//�L�[��5�Ɉ�v����v�f��T��
  �T�C�Y�擾				map.size()
  �S�v�f�폜				map.clear()
*/

int main()
{
	// map�̏�����
	// �L�[��int�^�A�l��std::string�^��map���쐬����B
	std::map<int, std::string> map;

	// �v�f�̒ǉ�
	// std::map��map[x]�̂悤�ɃA�N�Z�X�����݂��Ƃ��Amap[x]�����݂��Ȃ���Ώ���ɂ��̗v�f���ǉ������B
	map[1] = "one";
	map[3] = "three";

	// ������̗v�f�ǉ�
	map.insert(std::make_pair(5, "Five"));

	// �v�f�ւ̃A�N�Z�X
	std::cout << "map[3]: " << map[3] << std::endl;

	// map�̑S�v�f�̕\��
	for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	// �v�f�̍X�V
	map[3] = "drei";
	std::cout << "Updated map[3]: " << map[2] << std::endl;

	// map�̃T�C�Y
	std::cout << "Size of map: " << map.size() << std::endl;

	// �v�f�̍폜
	map.erase(3);
	std::cout << "Map after erasing key 3:" << std::endl;
	for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	// �v�f�̌���
	auto it = map.find(1);
	if (it != map.end()) {
		std::cout << "Element with key " << it->first << " found: " << it->second << std::endl;
	}
	else {
		std::cout << "Element with key " << it->first << " not found" << std::endl;
	}

	// ���ׂĂ̗v�f�̃N���A
	map.clear();
	std::cout << "Map after clear, is map empty? " << (map.empty() ? "Yes" : "No") << std::endl;

	// ���̏��������@
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
