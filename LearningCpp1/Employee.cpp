#include "Employee.h"

//void Employee::SetProject(std::unique_ptr<Project>& prj)
void Employee::SetProject(const std::shared_ptr<Project>& prj)
{
	// I don't a copy so that argument is a reference
	//this->project = std::move(prj);	// unique_ptr cannot copy. I can only move and empties inside of it ;). Be Careful!
	this->project = prj;
}

const std::shared_ptr<Project>& Employee::GetProject() const
{
	return this->project;
}
