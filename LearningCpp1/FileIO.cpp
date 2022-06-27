#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> // C++17 and no more experimental

// always remember close the file.

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

namespace BasicFileIO {
	/*
	ifstream = input file stream
	ofstream = output file stream
	fstream  = input and output file stream
	*/
	// Only text!
	constexpr auto TextFilename = "data.txt";
	void WriteText() {
		std::ofstream out{ TextFilename }; // if doesn't exist tries to creates the file.
		out << "I am data.txt file\n";
		out << 1 << '\n';
		out.close();
	}
	void ReadText() {
		//std::ifstream in2;
		//in2.open(TextFilename);
		std::ifstream in{ TextFilename }; // + " asd" // to fail opening file
		if (!in.is_open() || in.fail())
		{
			std::cerr << "Could not open the file\n";
			return;
		}
		std::string message;
		std::getline(in, message);
		int value{};
		in >> value;
		in >> value; // to fail reading data.
		// There is 4 kind of bits to check = good/bad/fail/eof
		if (in.fail()) // some I/O operations failed. I don't know what it is.
		{
			std::cerr << "Could not read the file\n";
		}
		else if (in.eof()) // end of file 
		{
			std::cerr << "There is nothing to read anymore\n";
		}
		else if (in.bad()) // end of file 
		{
			std::cerr << "Corrupted Media\n";
		}
		else if (in.good()) {
			std::cout << "Reading is successful\n";
		}
		else {
			std::cerr << "Something went go wrong\n";
		}
		in.setstate(std::ios::failbit | std::ios::badbit); // I can set the bit by chaining.
		in.clear(); // may cause "std::ios::badbit"
		in.close();
		std::cout << message << " : " << value << '\n';

	}

	// char by char
	constexpr auto TextFilename2 = "temperature.txt";
	void Write_char_by_char() {
		std::ofstream output(TextFilename2); // if doesn't exist tries to creates the file.
		if (!output)
		{
			std::cerr << "Could not open file for writing\n";
			return;
		}

		std::string message("Program the programming\nYou are living inside simulation and you don't even don't know it\nSuccess is 0 not 1\n");
		// * put also known as ofstream "file location pointer"
		std::clog << "Current put position is: " << output.tellp() << '\n'; // "tell the where is the put?" // on failure returns -1
		for (const char& ch : message)
		{
			output.put(ch);
		}

		auto position_put = 5;
		output.seekp(position_put);
		output.put('%'); // override

	}
	void Read_char_by_char() {
		std::ifstream input(TextFilename2);
		if (!input)
		{
			std::cerr << "Source file is not found\n";
			return;
		}

		{
			auto position_get = 5;
			// change the position of get according to number of character || offset and base position(std::ios::beg | std::ios::cur | std::ios::end)
			input.seekg(position_get); // position_get characters from the begging
			std::clog << "Current get position is: " << input.tellg() << '\n'; // "tell the where is the get?" // on failure returns -1
			input.seekg(position_get, std::ios::beg); // position_get characters from the begging
			std::clog << "Current get position is: " << input.tellg() << '\n'; // "tell the where is the get?" // on failure returns -1
			input.seekg(position_get, std::ios::cur); // position_get characters from the current
			std::clog << "Current get position is: " << input.tellg() << '\n'; // "tell the where is the get?" // on failure returns -1
			input.seekg(position_get, std::ios::end); // position_get characters from the ending
			std::clog << "Current get position is: " << input.tellg() << '\n'; // "tell the where is the get?" // on failure returns -1
		}

		input.seekg(0);
		char ch{};
		// * get also known as ifstream "file location pointer"
		while (input.get(ch)) // as long as "!eof" bit is set // as long as there are enough characters to read, the loop will continue
		{
			std::cout << ch;
		}

	}

	void FileStreams() {
		constexpr auto filename = "lyrics.txt";
		/*
		* I can read and write with one object.
		* The difference is if doesn't exist doesn't tries to creates the file. First Create the file with ofstream
		*/
		std::fstream stream{ filename };
		if (!stream) {
			std::cerr << "File doesn't exist" << '\n';
			std::ofstream out{ filename };
			out.close();
			stream.open(filename);
		}

		stream << "When they stand up and feel the warmth - (The day that never comes - Metallica)" << '\n';
		// "location pointer" goes to end of file. so that I cannot read anything at all :(.
		// I have to reset "get location pointer"
		stream.seekg(0);

		std::string line;
		std::getline(stream, line);
		std::cout << "lyrics: " << line << '\n';
	}
	void Binary() {
		// -*-*-* textStream *-*-*-
		std::ofstream textStream{ "data.txt" };
		int num{ 123456789 };
		char chs[10]{};
		_itoa_s(num, chs, 10);
		textStream << chs;

		// -*-*-* binaryStream *-*-*-
		std::ofstream binaryStream{ "binary.bin", std::ios::binary | std::ios::out }; // Visual studio can show ".bin" files ;)
		auto num_casted = reinterpret_cast<const char*>(&num); // reinterpret_cast<const char*>(&num); // (const char*)(&num);
		std::cout << std::hex << "num_casted: " << num_casted << '\n';
		// accepts "const char pointer"
		//textStream.write(num_casted, sizeof(num));
		binaryStream.write(num_casted, sizeof(num)); // binary files only needs 4 bytes
		binaryStream.close();

		std::cout << "Readed num: " << num << '\n';

		// -*-*-* input *-*-*-
		num = 0; // reset
		std::ifstream input{ "binary.bin", std::ios::binary | std::ios::in };
		input.read((char*)&num, sizeof(num));
		input.close();
	}

	namespace Record {
		struct Record {
			int id{};
			char name[10]{};
			void WriteRecord(Record* record) {
				std::ofstream output_binary{ "records.bin", std::ios::binary | std::ios::out };
				output_binary.seekp(0);

				//std::cout << "sizeof(Record): " << sizeof(Record) << " |vs| " << "sizeof(record): " << sizeof(record) << '\n';

				output_binary.write(reinterpret_cast<const char*>(record), sizeof(Record)); // I need a fixed size
				output_binary.close();
			}
			Record ReadRecord() {
				std::ifstream input_binary{ "records.bin", std::ios::binary | std::ios::in };
				input_binary.seekg(0);
				Record record{};
				input_binary.read(reinterpret_cast<char*>(&record), sizeof(Record));
				input_binary.close();
				return record;
			}
			void RecordTest() {
				Record r{};
				r.id = 900;
				std::string record_name = "record1"; // 7 chars + '\n' => record_name.size() + 1
				strcpy_s(r.name, record_name.size() + 1, record_name.c_str());
				WriteRecord(&r);
				Record r2;
				r2 = ReadRecord();
				std::cout << "id: " << r2.id << " : name: " << r2.name << '\n';
			}
		};

	}

	void FileIO_Main() {
		// Only text!
		WriteText();
		ReadText();
		// read-write char by char means read-write bytes ;)
		// also I can read-write from not from-to specific location
		Write_char_by_char();
		Read_char_by_char();
		FileStreams();

		// binary I/O
		Binary();
		Record::Record r;
		r.RecordTest();
	}
}

namespace CopyUtility {
	namespace fs = std::filesystem;
	using namespace fs; // changing the name of namespace not to confuse with other namespaces ;)
	int CopyTextUtility_Main() {
		// Copy (only text) source file into new location.

		// -*-*-* source *-*-*-
		path source(current_path());
		std::cout << "current_path: " << source << '\n';
		source /= "FileIO.cpp"; // current_path() + "FileIO.cpp" string operation

		std::ifstream input{ source };
		if (!input) // is_open()
		{
			std::cout << "source file not found\n";
			return -1;
		}

		// -*-*-* destination *-*-*-
		path destination(current_path());
		destination /= "FileIO_Copy.cpp"; // current_path() + "FileIO_Copy.cpp" string operation

		std::ofstream output{ destination };
		if (!output) // is_open()
		{
			std::cout << "source file not found\n";
			return -1;
		}

		// -*-*-* copy *-*-*-
		std::string line;
		while (!std::getline(input, line).eof()) // if it is not end of file ...
		{
			output << line << '\n';
		}
		input.close();
		output.close();
		return 0;

	}
}

namespace Assignments
{
	namespace Assignment1 {
		/*
		Modify the file copy utility to support copying of binary files. Here are some guidelines:

		* Use read & write functions of the stream classes instead of getline, operator << or >>.
		* Remember, binary files don't have EOF marker, so you'll have to read the file based on its size.
		* Take help of the filesystem library to manage paths. (path class, current_path(), is_directory(), etc)
		* Handle stream errors appropriately
		* Prevent existing files from being overwritten during copy operations. Show a suitable message if a file will be overwritten.
		Here is the link to the documentation of filesystem library: http://en.cppreference.com/w/cpp/header/experimental/filesystem
		*/
		void Assignment1_Main() {

		}
	}
	namespace Assignment2 {
		/*
		Modify the file copy utility to support following:

		* Accept file names through command line
		* If the source is a directory, then copy the content of the entire directory. e.g. C:\copyutil c:\myfiles d:\oldfiles. All files in copyutil will be copied to myfiles directory. If the target directory does not exist, then create it.
		* Show the progress of copy for each file as shown in the image below.

		*/
		void Assignment2_Main() {

		}
	}
	namespace Assignment3 {
		/*

		*/
		void Assignment3_Main() {

		}
	}

	void Assignment_Tests()
	{
		Assignment1::Assignment1_Main();
		//Assignment2::Assignment2_Main();
		//Assignment3::Assignment3_Main();
	}
}

void File_InputOutput_Main() {
	//str_literals::raw_string_literals();
	//standard_filesystem::standard_filesystem_Main();
	BasicFileIO::FileIO_Main();
	//CopyUtility::CopyTextUtility_Main();
	Assignments::Assignment_Tests();
}
