#include "ClassesOOPS.h"

#include <typeinfo>

using namespace Banking;

void Object_Slicing() {
	/*
	Up-casting to base leads to memory corruption. Some important data will be lost during up-casting.
	cannot detect at compile time(without code-analyze)!

	Account have 3 attributes => 40 byte
	Savings have 4 attributes => 44 byte

	compiler deliberately removes 4 byte :'(

	Up-Casting -> implicit
	Down-Casting -> explicit
	*/
	Checking ch1("Bob", 100);
	Account* acc1 = &ch1;
	Savings save1("Bob", 100, 0.01f);
	Account* acc2 = &save1;
	//save = acc2; // down-casting !!! Error !!!

	// Explicit downcast base class -> child class
	Savings* save3 = static_cast<Savings*>(acc1);
}

void TypeId() {
	/*
	If you are using polymorphic types acquire them at run-time
	If you are using non-polymorphic types acquire them at compile-time
	*/
	Savings save("Bob", 100, 0.07f);
	Checking ch1("Bob", 100, 50);
	std::cout << ch1.GetMinimumBalance() << '\n';

	Account* p1 = &ch1;
	Account* p2 = &save;

	int i{};
	float f{};
	const std::type_info& ti_i = typeid(ch1);
	const std::type_info& ti_f = typeid(ch1);
	const std::type_info& ti_ch1 = typeid(ch1);
	const std::type_info& ti_save = typeid(save);
	const std::type_info& ti_acc = typeid(p1);
	const std::type_info& ti_acc_pointer = typeid(*p1);
	std::cout << "int: " << ti_i.name() << '\n'
		<< "float: " << ti_f.name() << '\n'
		<< "Checking: " << ti_ch1.name() << '\n'
		<< "Savings: " << ti_save.name() << '\n'
		<< "Account: " << ti_acc.name() << '\n'
		<< "Account*: " << ti_acc_pointer.name() << '\n';

	//const std::type_info& ti = typeid(*p1);
	const std::type_info& ti = typeid(*p2);
	if (ti == typeid(Banking::Savings)) {
		std::cout << "points to Savings object\n";
	}
	else {
		std::cout << "not pointing to Savings object\n";
	}

}

void OOPS_Main() {
	Banking::Banking_Main_Test();
	//Override_Final_Main();
	//Object_Slicing();
	//TypeId();
}
