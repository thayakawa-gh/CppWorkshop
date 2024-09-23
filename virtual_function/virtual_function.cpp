#include <memory>
#include <iostream>
#include <format>
#include <vector>

class Base
{
public:

	// �h���N���X���`����ꍇ�A�f�X�g���N�^��virtual�ɂ��Ă������Ƃ���������܂��B
	virtual ~Base()
	{
		std::cout << "Base destructor\n";
	}

	// �ʏ�̊֐�
	void normal_function() const
	{
		std::cout << "Base::normal_function\n";
	}

	void normal_function_calling_virtual() const
	{
		virtual_function();
	}

	// ���z�֐�
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

/*
 �p���̎��ЂƂʔ����@�\�Ƃ��āA���z�֐�������܂��B
 ����́A���N���X�ŗ\�ߔC�ӂ̃����o�֐���"virtual"��t�^���Đ錾���Ă����A
 �h���N���X�ł��̊֐���������������悤�ɂ�����̂ł��B

 �����A�����ɂ����΁A���z�֐��łȂ������o�֐��ł����Ă��A�h���N���X�ł̏㏑���͉\�ł��B
 �������A���z�֐��ł��邩�A�����łȂ����ɂ���āA�֐����Ă΂ꂽ�Ƃ��Ɂu�ǂ̊֐����Ă΂��̂��v���قȂ�܂��B

 �Ⴆ�΁A�h���N���X�͊��N���X�̃|�C���^��Q�ƂŎw��������邱�Ƃ�����܂��B
 Base* d = new Derived;
 ���̏ꍇ�Ad�͖{����Derived�^�̃I�u�W�F�N�g���w���Ă���̂ł����B
 ����Base�^�̃|�C���^�Ɋi�[����Ă��邽�߁ABase�^�Ƃ��Ĉ����܂��B
 ���������āAd��Base�^�̃����o�ɂ����A�N�Z�X���邱�Ƃ��ł��܂���B
 d->normal_function(); // Base::normal_function  �ƕ\������܂��B

 �������A���z�֐��̏ꍇ�͈قȂ�܂��B
 ���Ƃ�Base�^�̃|�C���^�ɑ������Ă��Ă��A�������Derived���̊֐����Ă�ł���܂��B
 d->virtual_function(); // Derived::virtual_function  �ƕ\������܂��B

 ���̐U�镑���́Astd::unique_ptr�̂悤�ȃX�}�[�g�|�C���^���g�����ꍇ�����l�ł��B
 std::unique_ptr<Base> d = std::make_unique<Derived>();
 d->virtual_function(); // Derived::virtual_function  �ƕ\������܂��B

 ���̂悤�ɁA���N���X�̃|�C���^��Q�Ƃ���ł��h���N���X�Œ�`�����֐������s�ł���悤�ɂ�����̂����z�֐��ł��B



 ���z�֐��ɂ̓f�����b�g������܂��B
 �܂��A���z�֐�����ł���`����ƁA���̃N���X�̑傫���̓|�C���^1���傫���Ȃ�܂��B
 �Ⴆ�΁Aderived_class�̕��ŗ�Ƃ��ďo����BasetrackSubset��64�o�C�g�̑傫���������܂��B
 �i56�o�C�g�ł́H�Ǝv����������܂��񂪁A64�ł��B����ɂ͍\���̂̃A���C�����g����������Ă��܂��B�j
 ����A����BasetrackSubset��1�ł����z�֐����`����ƁA�傫����72�o�C�g�ɂȂ�܂��B
 ���������āA�f�[�^�̊i�[��S���N���X�ɉ��z�֐�����邱�Ƃ͂��܂萄���ł��܂���B
 �������Ȃ���A��ʂɌp����p����Ƃ��́A�Œ��virtual�ȃf�X�g���N�^���`���邱�Ƃ���������Ă��܂��B
 ���z�֐��Ɠ����悤�ɁABase�|�C���^��Q�Ƃɕϊ����Ă��܂���Derived�^�ϐ��́A����Derived�^�̃f�X�g���N�^���ĂԂɂ�virtual�ɂ���K�v�����邽�߂ł��B
 �u�p������Ƃ��ɂ�virtual�f�X�g���N�^���`����v�u���z�֐��ivirtual�ȃf�X�g���N�^�܂ށj������ƃT�C�Y��8�o�C�g������v
 �c�c�Ƃ������Ƃ́A���{�I�ɁA�f�[�^�i�[�N���X���p���Œ�`���邱�Ƃ͂��܂�悭�Ȃ��Ƃ������܂��B
 BasetrackSubset��BasetrackFull�́A���̂�����̐U�镑���𕪂����Ă���l�Ԃ�������ƊǗ����Ďg���̂Ȃ�悢�̂ł����A
 ������Ȃ������Ɉ��ՂɎg���ׂ��ł͂Ȃ���������܂���B

 �܂��A���z�֐��͊֐��Ăяo���̃I�[�o�[�w�b�h���傫���ł��B
 �ׂ����b���Ƃ�₱�����̂ŏȗ����܂����A���z�֐��͍œK���������ɂ����A���z�֐��̏������ĂԂ̂ɒʏ�̊֐������킸���Ɏ��Ԃ�������ꍇ�������̂ł��B
 �܂�A���z�֐����ߓx�ɑ��p����Ƃ��̃v���O�����̏������x���Ȃ�\��������܂��B
 ��������1����A1������x�̉��z�֐��Ăяo���ł͑債�ĉe���͂Ȃ��ł��傤�B���A100����A1����Ƒ����Ă���ƁA�����ɉe�����Ă��邩������܂���B
*/


int main()
{
	Base b;
	Derived d;

	// �����ł́ABase�ADerived�̕ϐ���p�ӂ��A���ꂼ��̊֐����Ăяo���Ă��܂��B
	// �d�v�Ȃ��Ƃ́Ab�Ad�Ƃ��ɂ��ꂼ��Base�^�ADerived�^�Ő錾����Ă��邱�Ƃł��B
	// �܂�Ab�Ad�Ƃ����ϐ��́A���ꂼ�ꎩ�g��Base�^�ADerived�^�ł���Ƃ������Ƃ�"�m���Ă��܂�"�B

	std::cout << "\n------normal_function------\n";
	b.normal_function();// Base::normal_function
	d.normal_function();// Derived::normal_function

	std::cout << "\n------virtual_function------\n";
	b.virtual_function();// Base::virtual_function
	d.virtual_function();// Derived::virtual_function

	// b�̏ꍇ��Base���Œ�`�����֐����Ad�̏ꍇ��Derived���Œ�`�����֐����Ă΂�Ă��܂��B
	// ����͂���قǕs�v�c�ȐU�镑���ł͂Ȃ��Ǝv���܂��B



	// ���ɁAb�Ad��Base�^�̎Q�Ƃɕς��Ă݂܂��傤�B
	// �����ŏd�v�Ȃ��Ƃ́Ad_ref�̎Q�Ɛ�ł���d�͂��Ƃ���Derived�^�ł������ɂ�������炸�A����Base�^�̈����ɂȂ��Ă��邱�Ƃł��B
	// ����������ƁA�ȉ���d_ref�́A"���g��Derived�ł������Ƃ������Ƃ�Y��Ă���"�̂ł��B
	// �iC++�ł́A"�ϐ��̌^�����ł��邩"�����ɏd�v�ȈӖ��������܂��B�j
	Base& b_ref = b;
	Base& d_ref = d;

	std::cout << "\n------normal_function------\n";
	b_ref.normal_function();// Base::normal_function
	d_ref.normal_function();// Base::normal_function

	std::cout << "\n------virtual_function------\n";
	b_ref.virtual_function();// Base::virtual_function
	d_ref.virtual_function();// Derived::virtual_function

	// �����ŁAb_ref.normal_function()��d_ref.normal_function()�͂ǂ����Base::normal_function()���Ă΂�Ă��܂��B
	// ����́Ab_ref�Ad_ref���ǂ����Base�^�Ƃ��Ĉ����Ă��邩��ł��B
	// ���ɁAd_ref�͎��g��Derived�^�ł��������Ƃ�Y��Ă��܂��Ă���̂ł��B

	// ����ŁAb_ref.virtual_function()��d_ref.virtual_function()�ł͂��ꂼ��A
	// ���Ƃ��Ƃ̎����̌^�ł���Base�^�ADerived�^�̊֐����Ă΂�Ă��܂��B
	// ���ꂪ���z�֐��̎������ł��B
	// ���������g�̌^��Base�^�ł����Ă��A�^�̌^��Derived�ł�������΁A���z�֐��͔h���N���X�Œ�`���ꂽ���z�֐����Ăяo���Ă���܂��B


	std::cout << "\n";


}