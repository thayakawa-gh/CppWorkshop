#define YAML_CPP_STATIC_DEFINE // <- ���܂��Ȃ��B�K�{�ł��B
#include <yaml-cpp/yaml.h> // <- ���܂��Ȃ��Byaml-cpp�̃w�b�_�t�@�C�����C���N���[�h���܂��B
#include <iostream>
#include <string>
#include <format>

// #### Yaml�t�@�C����p���ĊO����p�����[�^��^������@�B
// �v���O�����̕��G�ȋ����𐧌䂷�邽�߂̃p�����[�^�́A���ɃR�}���h���C�����������ł͂ƂĂ�����Ȃ����炢��ʂɂȂ��Ă��܂����Ƃ�����܂��B
// �Ⴆ�΁A0<tan��<2�͈̔͂�0.2���݂�radial lateral���ꂼ��̊p�x���x��^����ꍇ�A�v20���̃p�����[�^��^����K�v������܂����A
// ��������������R�}���h���C�������Ŏw�肷��Ȃ�Ĕn���������Ƃ͂ƂĂ��ł��܂���B
// ���̂悤�ȏꍇ�A���̓p�����[�^�̃��X�g���e�L�X�g�t�@�C���Ȃǂɏ������݁A���̃t�@�C�������R�}���h���C�������Ŏw�肷�邱�Ƃ���ʓI�ł��B
// ���̂Ƃ��̃e�L�X�g�t�@�C���́A�Ⴆ��NETSCAN����Runcard�Ƃ����Ǝ��`���AHTS�Ȃǂł�JSON�t�@�C�����g���Ă��܂����A
// ���Ƃ��ẮA���L�q���A�ǐ��A�����ɗD�ꂽYAML�t�@�C�����悢�Ǝv���Ă��܂��B
// YAML��JSON�̏�ʌ݊��ƌĂׂ���̂ŁAJSON�t�@�C����YAML�t�@�C�������œǂݍ��ނ��Ƃ��ł��A����YAML�Ǝ��̋L�@�������Ă��܂��B
// �����A�R�����g���L�q�ł��邱�Ƃ�JSON�ɂ͂Ȃ���ΓI�ȗ��_�ł��B

// #### yaml-cpp�T�v
// YAML�t�@�C����C++�ň������߂̃��C�u�����Ƃ���yaml-cpp������܂��B�ȉ���GitHub���|�W�g���Ō��J����Ă��܂��B
// https://github.com/jbeder/yaml-cpp
// ���x�͒x���̂Ő��\�A���SMB�ȏ�̃f�[�^��ǂ܂���ɂ͕s�����ł����A���Ɏg���₷�����C�u�����ł��B
// �i�ǂ����Ă����x���~�������rapidyaml�Ƃ������C�u����������܂����A�g���ɂ����̂ŏ��S�҂ɂ͂�����Ɗ��߂��܂���j�B

// �������@�iVisual Studio�̏ꍇ�j ���\�[�X�t�@�C���̉摜�iyamlcpp1.png�Ayamlcpp2.png�j���Q�ƁB
// 1. E:\udd\hayakawa\prg\ThirdParty�ɂ���yaml-cpp-0.8.0�t�H���_���A�C�ӂ̃��[�J���ȃt�H���_�ȂǂɃR�s�y����B�������GitHub���璼�ړ��肵�Ă��ǂ��B
// 2. Visual Studio��yaml-cpp���g�������v���W�F�N�g���J���B
// 3. �\�����[�V�����G�N�X�v���[���[�i����Visual Studio�̃E�B���h�E�E���ɂ���܂��j����A�v���W�F�N�g�����E�N���b�N���A�v���p�e�B��I���B
// 4. �u�\���v���p�e�B�v���uVC++ �f�B���N�g���v���u�C���N���[�h�f�B���N�g���v�ɁA�R�s�[����yaml-cpp�t�H���_����include�t�H���_�ւ̃p�X��ǉ�����B
// 5. �u�\���v���p�e�B�v���uVC++ �f�B���N�g���v���u���C�u�����f�B���N�g���v�ɁA�R�s�[����yaml-cpp�t�H���_����lib�t�H���_�ւ̃p�X��ǉ�����B
// 6. �u�\���v���p�e�B�v���u�����J�[�v���u���́v���u�ǉ��̈ˑ��t�@�C���v�ɂāA
//    �����Debug�ɂ�����Ԃ�yaml-cppd.lib��ǉ����E���́u�K�p�v���N���b�N�A���̌㍶���Release�ɕύX����yaml-cpp.lib��ǉ�����B
// 7. �u�\���v���p�e�B�v���uC/C++�v���u����v���uC++����W���v���u/std:c++17�v�Ȃ���������17�ȏ�̂��̂�I���B/std:c++20�ȏォ/std:c++latest�𐄏��B

struct Material
{
	std::string name;
	double thickness;
	double radiation_length;
};
struct Parts
{
	std::string name;
	std::vector<std::string> structure;
};

int main()
{
	double thr_chi_square = 30;
	std::string cut_mode;
	std::vector<std::string> ecc_dirs;
	std::vector<double> rad_acc;
	std::vector<double> lat_acc;
	Material emulsion;

	std::vector<Material> vmat;
	std::vector<Parts> vparts;
	try
	{
		// ----------YAML�t�@�C���̓ǂݍ���----------
		YAML::Node params = YAML::LoadFile("params.yaml");

		// ----------YAML�t�@�C�����̃p�����[�^�̎擾----------
		thr_chi_square = params["ThrChiSquare"].as<double>();
		cut_mode = params["CutMode"].as<std::string>();

		ecc_dirs = params["ECCDirs"].as<std::vector<std::string>>();

		rad_acc = params["RadAngAccuracy"].as<std::vector<double>>();
		lat_acc = params["LatAngAccuracy"].as<std::vector<double>>();

		YAML::Node materials = params["Materials"];
		YAML::Node emul = materials["Emulsion"];
		emulsion.thickness = emul["Thickness"].as<double>();
		emulsion.radiation_length = emul["RadiationLength"].as<double>();


		// ----------������ƍ��x�ȃp�����[�^�擾----------

		// map�S�̂����[�v���Ȃ���擾���邱�Ƃ��ł��܂��B
		for (const auto& n : materials)
		{
			//n.first��"Base"�A"Emulsuon"�Ȃǂ̃L�[�An.second�ł��̃m�[�h���擾�ł��܂��B
			Material m;
			m.name = n.first.as<std::string>();
			m.thickness = n.second["Thickness"].as<double>();
			m.radiation_length = n.second["RadiationLength"].as<double>();
			vmat.emplace_back(std::move(m));
		}

		// ���l��sequence�����[�v���Ȃ���擾���邱�Ƃ��ł��܂��B
		YAML::Node parts = params["Parts"];
		for (const auto& n : parts)
		{
			Parts p;
			p.name = n["Name"].as<std::string>();
			p.structure = n["Structure"].as<std::vector<std::string>>();
			vparts.emplace_back(std::move(p));
		}

		// ���閼�O�̃L�[�����m�[�h�����݂��邩�ǂ����𒲂ׂ邱�Ƃ��ł��܂��B
		if (materials["Air"]) std::cout << "Air exists\n";
		else std::cout << "Air does not exist\n";

		if (materials["Iron"]) std::cout << "Iron exists\n";
		else std::cout << "Iron does not exist\n";
	}
	catch (const YAML::Exception& e)
	{
		// ����YAML�t�@�C���̓ǂݍ��݂ŃG���[�����������ꍇ�A�G���[���b�Z�[�W��\�����ăv���O�������I������B
		std::cerr << e.what() << std::endl;
		exit(-1);
	}

	// ----------�擾�����p�����[�^�̕\��----------
	std::cout << "ThrChiSquare: " << thr_chi_square << std::endl;
	std::cout << "CutMode: " << cut_mode << std::endl;
	for (const auto& ecc_dir : ecc_dirs) std::cout << ecc_dir << std::endl;
	std::cout << " ang rad_acc lat_acc\n";
	for (int i = 0; i < rad_acc.size(); ++i)
	{
		double ang = i * 0.2 + 0.1;
		std::cout << std::format("{:>4.1f} {:>7.4f} {:>7.4f}\n", ang, rad_acc[i], lat_acc[i]);
	}
	std::cout << std::format("Emulsion: thickness {:>.1f}, radiation_length {:>.1f}", emulsion.thickness, emulsion.radiation_length) << std::endl;
	for (const auto& m : vmat)
	{
		std::cout << std::format("Material: name {:>12}, thickness {:>7.1f}, radiation_length {:>7.1f}\n", m.name, m.thickness, m.radiation_length);
	}

	// ����ȍ~�Ɏ����̏����������B
}