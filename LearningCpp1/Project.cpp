#include "Project.h"

void Project::SetName(const std::string& name)
{
	this->name = name;
}

std::string Project::GetName() const {
	return name;
}

std::string Project::GetProjectDetails() const {
	return GetName();
}
void Project::DisplayDetails() const {
	std::cout << "[Project Name]= " << GetName() << '\n';
}
