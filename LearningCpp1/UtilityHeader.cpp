#include "UtilityHeader.h"

void settings() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// DON'T RESTR�CT THE SCOPE IF YOU ARE GO�NG TO USE �T GLOBALLY

/* restrict the scope with ...
* https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-error-lnk2005?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(LNK2005)%26rd%3Dtrue&view=msvc-170
* inline
* static
* __declspec(selectany)
* Remove the function body from the header file and leave only the declaration, then implement the function in one and only one source file (most useful)
*/
void Print(int count, char ch)
{
	using namespace std;
	for (size_t i = 0; i < count; ++i)
	{
		cout << ch;
	}
	cout << '\n';
}

void EndMessage()
{
	std::cout << "End of program \n";
}




std::string repeat(int n) {
	std::ostringstream os;
	for (int i = 0; i < n; i++)
		os << "repeat";
	return os.str();
}


void log_function_detail(const std::string_view message,
	const std::source_location location) // = std::source_location::current()
{
	std::clog << "file: "
		<< location.file_name() << "("
		<< location.line() << ":"
		<< location.column() << ") `"
		<< location.function_name() << "`: " << '\n';
}

void log(const std::string_view message,
	const std::source_location location) {
	log_function_detail(message, location);
}
