

#include <iostream>
#include <string>
#include <filesystem> // C++17

namespace str_literals {
	void raw_string_literals() {
		std::string wrong_filename{ "C:\temperatures\newyork.txt" };
		/*
		// output:
		C:      emperatures
		ewyork.txt
		\t => tab
		\n => new line
		;)
		*/
		std::cout << "wrong_filename: " << wrong_filename << '\n';

		std::string true_filename{ "C:\\temperatures\\newyork.txt" };
		std::cout << "true_filename: " << true_filename << '\n';

		// C++11 raw string literals
		// useful when processing html, xml, regex strings
		std::string ignore_special_characters_filename{ R"(C:\temperatures\newyork.txt)" };
		std::cout << "ignore special characters filename: " << ignore_special_characters_filename << '\n';

		std::string ignore_special_characters{ R"(\n\t\a)" };
		std::cout << "ignore special characters: " << ignore_special_characters << '\n';

		std::string ignore_special_characters_MSG{ R"MSG(\n\t\a "Filesystem API("C++17")" )MSG" }; // max number of chars = 16 | whitespace, backslashes not allowed.
		std::cout << "ignore special characters: " << ignore_special_characters_MSG << '\n';
	}
}

namespace standard_filesystem {
	void standard_filesystem_Main() {
		namespace fs = std::filesystem;
		using namespace fs; // changing the name of namespace not to confuse with other namespaces ;)
		std::string fullpath_name{ R"(C:\Windows)" };
		fs::path system_path{ fullpath_name };
		if (system_path.has_filename()) {
			std::cout << system_path.filename() << '\n';
		}
		for (const auto& x : system_path) {
			std::cout << x << '\n';
		}


		fs::directory_iterator begin{ system_path };
		fs::directory_iterator end{};
		while (begin != end) {
			std::cout << *begin << '\n';
			++begin;
		}


	}
}

namespace FileIO {
	/*
	ifstream = input file stream
	ofstream = output file stream
	fstream  = input and output file stream
	*/

	void FileIO_Main()
	{

	}
}

void File_InputOutput_Main() {
	str_literals::raw_string_literals();
	standard_filesystem::standard_filesystem_Main();
}
