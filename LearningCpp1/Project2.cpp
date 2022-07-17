#include <iostream>
#include "Project2.h"


// -*-*-* RAW *-*-*-
//ProjectRAW
ProjectRAW::ProjectRAW() {
	std::cout << "ProjectRAW()\n";
}

ProjectRAW::~ProjectRAW() {
	std::cout << "~ProjectRAW()\n";
}
//EmployeeRAW
EmployeeRAW::EmployeeRAW() {
	std::cout << "EmployeeRAW()\n";
}

EmployeeRAW::~EmployeeRAW() {
	std::cout << "~EmployeeRAW()\n";

}


// -*-*-* Smart *-*-*-
//ProjectSmart
ProjectSmart::ProjectSmart() {
	std::cout << "ProjectSmart()\n";
}

ProjectSmart::~ProjectSmart() {
	std::cout << "~ProjectSmart()\n";
}
//EmployeeSmart
EmployeeSmart::EmployeeSmart() {
	std::cout << "EmployeeSmart()\n";
}

EmployeeSmart::~EmployeeSmart() {
	std::cout << "~EmployeeSmart()\n";
}


// -*-*-* Weak *-*-*-
// one of them must be weak_ptr
ProjectWeak::ProjectWeak() {
	std::cout << "ProjectWeak()\n";
}

ProjectWeak::~ProjectWeak() {
	std::cout << "~ProjectWeak()\n";
}
//EmployeeSmart
EmployeeWeak::EmployeeWeak() {
	std::cout << "EmployeeWeak()\n";
}

EmployeeWeak::~EmployeeWeak() {
	std::cout << "~EmployeeWeak()\n";
}
