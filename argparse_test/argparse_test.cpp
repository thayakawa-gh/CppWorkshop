#include <argparse/argparse.hpp>
#include <iostream>

// #### ���@
// �v���O�������s���ɗ^����R�}���h���C��������ǂݍ��݁A�v���O�����̋����𒲐�������@�B
// ���炩�̃v���O���������s����Ƃ��A���̃v���O�����ɑ΂��ăp�����[�^��^���ċ����𒲐��������Ȃ邱�Ƃ����΂��΂���܂��B
// �V���v���ȗ�Ō����΁A����Basetrack�̃t�@�C����ǂݍ��݁APH�J�b�g�������Ďc����Basetrack���o�͂������ƍl�����Ƃ��A
// ����PH臒l���v���O�������ɒ��ڏ����Ă��܂��ƁAPH臒l���O����ύX�ł��Ȃ��Ȃ��Ă��܂��܂��B
// �������Ⴆ�Έȉ��̂悤�ɁA���s���ɊO����R�}���h���C�������Ƃ���臒l��n�����Ƃ��ł���΁A���������R�[�h���C�����Ȃ��Ă�臒l�̕ύX���\�ł��B
// program_name.exe --ph_cut 20
// ���������������@�͐F�X�Ƃ���܂����A�����ł͑��삪�悭�g�����@���Љ�܂��B

// #### argparse�T�v
// C++�ɂ́A�R�}���h���C���������V���v���Ɉ������߂̋@�\���W���ŗp�ӂ���Ă��܂���B
// NETSCAN�Ȃǂ͌��\�ȗ͋Ƃł�����������Ă��܂����A���p���̒Ⴓ���v���Ɨǂ����@�ł͂Ȃ��ł��傤�B
// �����ŁAargparse�Ƃ������C�u�������g�����Ƃ������߂��܂��B
// argparse�̓T�[�h�p�[�e�B�����C�u�����ŁA�ȉ���GitHub���|�W�g���Ō��J����Ă��܂��B
// https://github.com/p-ranav/argparse
// �R�}���h���C�������Ƃ��Ď󂯎�����l����ǂ��A�p�����[�^���ȒP�Ɏ��o����悤�ɂ���֗��ȃ��C�u�����ł��B
// �V���O���w�b�_�̂��ߓ������₷���A�g�������V���v���ł��B

// �������@�iVisual Studio�̏ꍇ�j ���\�[�X�t�@�C���̉摜�iargparse.png�j���Q�ƁB
// 1. E:\udd\hayakawa\prg\ThirdParty�ɂ���argparse-3.2�t�H���_���A�C�ӂ̃��[�J���ȃt�H���_�ȂǂɃR�s�y����B�������GitHub���璼�ړ��肵�Ă��ǂ��B
// 2. Visual Studio��argparse���g�������v���W�F�N�g���J���B
// 3. �\�����[�V�����G�N�X�v���[���[�i����Visual Studio�̃E�B���h�E�E���ɂ���܂��j����A�v���W�F�N�g�����E�N���b�N���A�v���p�e�B��I���B
// 4. �u�\���v���p�e�B�v���uVC++ �f�B���N�g���v���u�C���N���[�h�f�B���N�g���v�ɁAargparse�̃R�s�[��t�H���_��ǉ�����B
// 5. �u�\���v���p�e�B�v���uC/C++�v���u����v���uC++����W���v���u/std:c++17�v�Ȃ���������17�ȏ�̂��̂�I���B/std:c++20�ȏォ/std:c++latest�𐄏��B

int main(char argc, char* argv[])
{
	argparse::ArgumentParser parser("This is a test program.");

	parser.add_argument("input_filename").help("input file name");
	parser.add_argument("output_filename").help("output file name");

	// �����^���󂯎�肽���Ƃ���scan<'i', int>()���g���B
	parser.add_argument("--ph_cut").help("PH cut threshold").scan<'i', int>().default_value(20);
	// ���������_�^���󂯎�肽���Ƃ���scan<'f', double>()���g���B
	// �܂������̒l���󂯎�肽���ꍇ�Anargs(num)�Ȃ���nargs(min, max)�̂悤�ɐ����w�肷��B
	parser.add_argument("--xrange").help("xmin xmax").scan<'f', double>().default_value(std::vector<double>()).nargs(2);
	parser.add_argument("--rem_tracks").help("output filename for removed track list").default_value(std::string());

	// ��L�̈�����`���ƁA���̂悤�ɂ��̃v���O���������s���邱�Ƃ��ł��܂��B
	// program_name.exe input.txt output.txt --ph_cut 20 --rem_tracks removed_tracks.txt --xrange 350000 400000
	// input.txt��output.txt�͕K�{�ŁAprogram_name.exe�ɑ����Ďw�肷��K�v������܂��B
	// --ph_cut�A--xrange�A--rem_tracks�͏ȗ��\���w�菇���C�ӂŁA�ȗ������ꍇ�͂��ꂼ��f�t�H���g�l���g���܂��B

	try
	{
		// �R�}���h���C����������͂���B
		parser.parse_args(argc, argv);
	}
	catch (const std::exception& err)
	{
		// ����������͂ŃG���[�����������ꍇ�i���͈����̗^�������Ԉ���Ă����ꍇ�j�A
		// �G���[���b�Z�[�W��\�����A�w���v��\�����ăv���O�������I������B
		std::cerr << err.what() << std::endl;
		std::cerr << parser;
		std::exit(1);
	}

	std::string input_filename = parser.get<std::string>("input_filename");
	std::string output_filename = parser.get<std::string>("output_filename");
	int ph_cut = parser.get<int>("ph_cut");
	std::vector<double> xrange = parser.get<std::vector<double>>("xrange");
	std::string rem_tracks = parser.get<std::string>("rem_tracks");

	std::cout << std::format("input_filename: {}\n", input_filename);
	std::cout << std::format("output_filename: {}\n", output_filename);
	std::cout << std::format("ph_cut: {}\n", ph_cut);
	if (xrange.size() != 2) std::cout << "xrange:\n";
	else std::cout << std::format("xrange: {:>.1f} {:>.1f}\n", xrange[0], xrange[1]);
	std::cout << std::format("rem_tracks: {}\n", rem_tracks);
}