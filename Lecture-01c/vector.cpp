#include <iostream>
#include <vector>
#include <algorithm>  // std::find

int main()
{
	// �x�N�^�[�̏�����
	// int�^��1, 2, 3, 4, 5�Ƃ����v�f�����x�N�^�[���쐬����
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	//std::vector<std::string> vec_str = { "Hello", "World" }; vector��int�����łȂ�double��string�ȂǔC�ӂ̌^���i�[�ł���

	// ���낢��ȏ��������@
	std::vector<int> vec0;  // ��̃x�N�^�[
	std::vector<int> vec1(5);  // 5�̗v�f��0�ŏ�����
	std::vector<int> vec2(5, 10);  // 5�̗v�f��10�ŏ�����

	// �o��
	std::cout << "vec: ";
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// �v�f�̒ǉ�
	vec.push_back(6);
	std::cout << "After push_back(6): ";
	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// �v�f�ւ̃A�N�Z�X
	std::cout << "Element at index 2: " << vec[2] << std::endl;

	// �x�N�^�[�̃T�C�Y
	std::cout << "Size of vec: " << vec.size() << std::endl;

	// �v�f�̑}��
	vec.insert(vec.begin() + 3, 10);  // �C���f�b�N�X3�̈ʒu��10��}��
	std::cout << "After insert(10) at index 3: ";
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// �v�f�̍폜
	vec.erase(vec.begin() + 3);  // �C���f�b�N�X3�̗v�f���폜
	std::cout << "After erase at index 3: ";
	for (int val : vec) {
		std::cout << val << " ";
	}
	std::cout << std::endl;

	// �v�f�̃N���A
	vec.clear();
	std::cout << "After clear, is vec empty? " << (vec.empty() ? "Yes" : "No") << std::endl;

	// ���������ăT�C�Y���w��
	std::vector<int> vec3(5, 100);  // 5�̗v�f��100�ŏ�����
	std::cout << "vec3: ";
	for (int val : vec3) {
		std::cout << val << " ";
	}
	std::cout << std::endl;

	return 0;
}

/*
���
2�A3�A5�A7�A...�ƁA30�ȉ��̑f����v�f�Ɏ���std::vector<int>���쐬���܂��傤�B
�Ȃ��A�f�����ۂ��̔���͎���IsPrime���Ăяo�����ƂŔ���ł��܂��B
*/

bool IsPrime(int n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; i * i <= n; i += 2)
	{
		if (n % i == 0) return false;
	}
	return true;
}