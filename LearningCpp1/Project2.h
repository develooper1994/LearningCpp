#pragma once
#include <iostream>
#include <memory>

// -*-*-* RAW *-*-*-
class EmployeeRAW;

class ProjectRAW
{
public:
	EmployeeRAW* employee;

	ProjectRAW();
	~ProjectRAW();
};

class EmployeeRAW
{
public:
	ProjectRAW* prj;

	EmployeeRAW();
	~EmployeeRAW();
};


// -*-*-* Smart *-*-*-
// !Memory Leak!
class EmployeeSmart;

class ProjectSmart
{
public:
	std::shared_ptr<EmployeeSmart> employee;

	ProjectSmart();
	~ProjectSmart();
};

class EmployeeSmart
{
public:
	std::shared_ptr<ProjectSmart> prj;

	EmployeeSmart();
	~EmployeeSmart();
};


// -*-*-* Weak *-*-*-
// one of them must be weak_ptr
class EmployeeWeak;

class ProjectWeak
{
public:
	std::shared_ptr<EmployeeWeak> employee;

	ProjectWeak();
	~ProjectWeak();
};

class EmployeeWeak
{
public:
	std::weak_ptr<ProjectWeak> prj;

	EmployeeWeak();
	~EmployeeWeak();
};
