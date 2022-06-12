#include <memory>
#include "Project.h"
// Employee has only one project.
class Employee
{
private:
	//std::unique_ptr<Project> project{};
	std::shared_ptr<Project> project{};
public:
	//void SetProject(std::unique_ptr<Project>& prj);
	void SetProject(const std::shared_ptr<Project>& prj);
	const std::shared_ptr<Project>& GetProject() const;
};