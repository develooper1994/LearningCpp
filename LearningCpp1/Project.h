#pragma once
#include <iostream>
#include <string>
// Project can have many employees
// Project will have array or list of employees	so that employee must be shared_ptr
class Project
{
private:
	std::string name;
public:
	void SetName(const std::string& name);
	std::string GetName() const;
	std::string GetProjectDetails() const;
	void DisplayDetails() const;
};

