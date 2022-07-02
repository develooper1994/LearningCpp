/*
Created by Mustafa Selçuk Çaðlar
Note:Use this code at your own risk.
*/

#include <iostream>
#include <string>
#include <sstream>
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
		if (!output) {
			std::cerr << "Could not open file for writing\n";
			return;
		}

		std::string message("Program the programming\nYou are living inside simulation and you don't even don't know it\nSuccess is 0 not 1\n");
		// * put also known as ofstream "file location pointer"
		std::clog << "Current put position is: " << output.tellp() << '\n'; // "tell the where is the put?" // on failure returns -1
		for (const char& ch : message) {
			output.put(ch);
		}

		auto position_put = 5;
		output.seekp(position_put);
		output.put('%'); // override

	}
	void Read_char_by_char() {
		std::ifstream input(TextFilename2);
		if (!input) {
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
		while (input.get(ch)) { // as long as "!eof" bit is set // as long as there are enough characters to read, the loop will continue
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
		input.read(reinterpret_cast<char*>(&num), sizeof(num));
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
	typedef uint8_t BYTE;
	typedef std::allocator<BYTE> BYTE_allocator;
	typedef std::char_traits<BYTE> BYTE_char_traits;

	//using string = std::basic_string<BYTE, BYTE_char_traits, BYTE_allocator >;
	using ios = std::basic_ios<BYTE, BYTE_char_traits>;
	//using streambuf = std::basic_streambuf<BYTE, BYTE_char_traits>;
	//using istream = std::basic_istream<BYTE, BYTE_char_traits>;
	//using ostream = std::basic_ostream<BYTE, BYTE_char_traits>;
	//using iostream = std::basic_iostream<BYTE, BYTE_char_traits>;
	//using stringbuf = std::basic_stringbuf<BYTE, BYTE_char_traits, std::allocator<BYTE>>;
	//using istringstream = std::basic_istringstream<BYTE, BYTE_char_traits, BYTE_allocator>;
	//using ostringstream = std::basic_ostringstream<BYTE, BYTE_char_traits, BYTE_allocator>;
	//using stringstream = std::basic_stringstream<BYTE, BYTE_char_traits, BYTE_allocator>;
	//using filebuf = std::basic_filebuf<BYTE, BYTE_char_traits>;
	using ifstream = std::basic_ifstream<BYTE, BYTE_char_traits>;
	using ofstream = std::basic_ofstream<BYTE, BYTE_char_traits>;
	using fstream = std::basic_fstream<BYTE, BYTE_char_traits>;

	namespace fs = std::filesystem;
	using namespace fs; // changing the name of namespace not to confuse with other namespaces ;)
	bool isFileAvailable(const ios& file) {
		// not a bood idea :|
		if (!file) {
			throw std::runtime_error("Could not open the source file");
			return false;
		}
		return true;
	}
	bool isFileAvailable(const std::ios& file) {
		// not a bood idea :(
		if (!file) {
			throw std::runtime_error("Could not open the source file");
			return false;
		}
		return true;
	}
	void resetLocationCursor(std::ifstream& input, ofstream& output)
	{
		input.seekg(0, std::ios::beg);
		output.seekp(0, std::ios::beg);
	}
	void resetLocationCursor(ifstream& input, ofstream& output)
	{
		input.seekg(0, std::ios::beg);
		output.seekp(0, std::ios::beg);
	}
	int CopyTextUtility_Main() {
		// Copy (only text) source file into new location.

		// -*-*-* source *-*-*-
		std::string source_filename("FileIO.cpp");
		path source(current_path());
		std::cout << "current_path: " << source << '\n';
		source /= source_filename; // current_path() + "FileIO.cpp" string operation

		std::ifstream input{ source };
		if (!input) { // is_open()
			std::cout << "source file not found\n";
			return -1;
		}

		// -*-*-* destination *-*-*-
		std::string destination_filename("FileIO_Copy.cpp");
		path destination(current_path());
		destination /= destination_filename; // current_path() + "FileIO_Copy.cpp" string operation

		std::ofstream output{ destination };
		if (!output) { // is_open()
			std::cout << "source file not found\n";
			return -1;
		}

		// -*-*-* copy *-*-*-
		std::string line;
		while (!std::getline(input, line).eof()) { // if it is not end of file ...
			output << line << '\n';
		}
		input.close();
		output.close();
		return 0;
	}
	void source_subroutine(std::ifstream& input, const std::string& source_filename = "FileIO.cpp") {
		path source(current_path());
		std::cout << "current_path: " << source << '\n';
		source /= source_filename; // current_path() + "FileIO.cpp" string operation

		input.setstate(std::ios::binary | std::ios::in);
		isFileAvailable(input);
		input.open(source);
		// Stop eating new lines in binary mode!!!
		input.unsetf(std::ios::skipws);
	}
	void source_subroutine(ifstream& input, const std::string& source_filename = "FileIO.cpp") {
		path source(current_path());
		std::cout << "current_path: " << source << '\n';
		source /= source_filename; // current_path() + "FileIO.cpp" string operation

		input.setstate(std::ios::binary | std::ios::in);
		isFileAvailable(input);
		input.open(source);
		// Stop eating new lines in binary mode!!!
		input.unsetf(std::ios::skipws);
	}
	void destination_subroutine(ofstream& output, const std::string& destination_filename = "FileIO_Copy.cpp")
	{
		path destination(current_path());
		destination /= destination_filename; // current_path() + "FileIO_Copy.cpp" string operation

		output.setstate(std::ios::binary | std::ios::in);
		isFileAvailable(output);
		output.open(destination);
		// Stop eating new lines in binary mode!!!
		output.unsetf(std::ios::skipws);
	}
	void all_in_one_time(uintmax_t file_size, std::ifstream& input, ofstream& output) {
		// read-write all in one time. pre-allocationg is good :)
		// you cannot do anything while copying and writing is bad :(

		// reset the "location cursor"
		resetLocationCursor(input, output);

		std::vector<BYTE> input_vec;
		input_vec.reserve(file_size);
		// -*-*-* Read *-*-*-
		{
			// increase locality
			auto Read = [&input, &input_vec]() {
				std::copy(
					std::istream_iterator<BYTE>(input),
					std::istream_iterator<BYTE>(),
					std::back_inserter(input_vec)
				);
			};
			Read();
			input_vec.shrink_to_fit();
			resetLocationCursor(input, output);
		}

		// -*-*-* Write *-*-*-
		{
			// increase locality
			auto Write = [&output, &input_vec]() {
				if (!output.write(&input_vec.front(), input_vec.size())) {
					throw std::runtime_error("Error occured during write operation");
				}
			};
			Write();
			resetLocationCursor(input, output);
		}
	}
	void all_in_one_test()
	{
		// -*-*-* source *-*-*-
		std::string source_filename = "FileIO.cpp";
		std::ifstream input;
		source_subroutine(input, source_filename);
		auto file_size = fs::file_size(source_filename);

		// -*-*-* destination *-*-*-
		std::string destination_filename("FileIO_Copy.cpp");
		ofstream output;
		destination_subroutine(output, destination_filename);

		// -*-*-* Copying *-*-*-
		std::cout << "Copying\n";
		all_in_one_time(file_size, input, output);
		// -*-*-* Done *-*-*-
		std::cout << " Done!" << std::endl;
		input.close();
		output.close();
		fs::remove(destination_filename);
	}
	int chunk_by_chunk_test()
	{
		// -*-*-* source *-*-*-
		std::string source_filename = "Integer.cpp";
		ifstream input;
		source_subroutine(input, source_filename);
		auto file_size = fs::file_size(source_filename);

		// -*-*-* destination *-*-*-
		std::string destination_filename("Integer_Copy.cpp");
		ofstream output;
		destination_subroutine(output, destination_filename);

		// -*-*-* Copying *-*-*-
		std::cout << "Copying\n";
		resetLocationCursor(input, output);
		const size_t BufferSize(512); // number of bytes
		//BYTE input_vec[Buffer_size]{};
		std::vector<BYTE> input_vec;
		input_vec.reserve(BufferSize); // pre-allocate but smaller chunks not all of them. May be there is not enough memory ;)
		input_vec.resize(BufferSize, 0);
		auto ch_start = input_vec.begin(); // I can tell where i crashed and continue to the process.
		auto ch_end = input_vec.end();
		auto input_vec_size = input_vec.size();

		auto&& input_vec_data = input_vec.data(); // I don't want to copy inner data
		bool readError{}, writeError{};
		size_t process{}, oldprocess{}; // no way to negative
		size_t interrupted_input_idx = 0, interrupted_output_idx = 0;  // I can tell where i crashed and continue to the process.
		bool isRemaining = false;
		// * Split the file into chunks
		// more than one chunk
		auto chunks = static_cast<size_t>(floor(file_size / BufferSize - 1));
		auto remaining = static_cast<size_t>(BufferSize + file_size % BufferSize); // remaining bytes
		size_t chunk = 0;

		auto input_vec_reset = [&input_vec, &ch_start, &ch_end](bool isRemaining = false) {
			ch_start = input_vec.begin();
			if (isRemaining)
				ch_end = --input_vec.end();
			else
				ch_end = input_vec.end();
		};
		auto check_progress = [&input_vec]
		(auto& file_stream, const auto& readError, const auto& ch_start, const auto& ch_end, std::string error_message = "Operation Error") {
			auto inputState = file_stream.rdstate();
			auto interrupted_idx = static_cast<size_t>(std::distance(input_vec.begin(), ch_start)); // last is good
			//if (!(inputState & (std::ios_base::badbit | std::ios_base::failbit))) {
			if (!readError && ch_start < ch_end) {
				throw std::runtime_error(std::string(error_message));
			}
			return interrupted_idx; // it will not be executed but I have to report where the operation interrupted to continue after.
		};
		auto ReadSome = [&input, &input_vec, &readError, &check_progress](auto&& ch_start, auto&& ch_end) {
			for (; !readError && ch_start < ch_end; ++ch_start) {
				readError = !input.get(*ch_start);
			}
			//while (!readError) { // as long as "!eof" bit is set // as long as there are enough characters to read, the loop will continue
			//	readError = !input.get(ch) && input_vec_counter < remaining;
			//	input_vec[input_vec_counter++] = ch;
			//	// TODO: Control errors. fail|bad|
			//}
		};
		auto Read = [&input, &input_vec, &readError, &ReadSome, &check_progress](auto&& ch_start, auto&& ch_end) {
			/*readError = !input.read(input_vec_data, BufferSize);
			if (readError) throw std::runtime_error("Read operation Error");*/
			ReadSome(ch_start, ch_end);
			auto interrupted_input_idx = check_progress(input, readError, ch_start, ch_end, "ReadSome Operation Error");
			return interrupted_input_idx;
		};
		auto WriteSome = [&output, &input_vec, &writeError, &check_progress](auto& ch_start, auto& ch_end) {
			//Write - _Count: fileSize
			for (; !writeError && ch_start < ch_end; ++ch_start) {
				writeError = !output.put(*ch_start);
			}
			//auto outputState = output.rdstate();
			//auto interrupted_idx = static_cast<size_t>(std::distance(input_vec.begin(), ch_start));
			////if (!(outputState & (std::ios_base::badbit | std::ios_base::failbit))) {
			//if (!writeError && ch_start < ch_end) {
			//	throw std::runtime_error("Write operation Error");
			//	//return interrupted_idx; // it will not be executed but I have to report where the operation interrupted to continue after.
			//}

			//// Read - _Count: remaining
			//readError = !input.read(input_vec_data, remaining);
			//if (readError) {
			//	throw std::runtime_error("Read operation Error");
			//}
			////input_vec.shrink_to_fit();
			////Write - _Count: remaining
			//writeError = !output.write(input_vec_data, remaining);
			//if (writeError) {
			//	throw std::runtime_error("Write operation Error");
			//}
		};
		auto Write = [&output, &input_vec, &writeError, &check_progress, &WriteSome](auto& ch_start, auto& ch_end) {
			/*writeError = !output.write(input_vec_data, BufferSize);
			if (writeError) throw std::runtime_error("Write operation Error");*/
			WriteSome(ch_start, ch_end);
			auto interrupted_output_idx = check_progress(output, writeError, ch_start, ch_end, "WriteSome Operation Error");
			return interrupted_output_idx;
		};
		auto process_meter = [&process, &oldprocess](auto&& chunk, auto&& chunks) {
			/*
			  * Get progress from 0 to 10 and print .s
			  *
			  * I'm calculating the percentage of the chunks copied. However, I multiply it by
			  * 10 to ensure its value is greater than 0 and I can compare it with its old value
			  * later. Conversion to integer is necessary because we cannot compare two float
			  * values precisely. If the old and new values of percentage are different,
			  * then we print the period on the screen.
		  */
			const auto& fchunk = static_cast<float>(chunk);
			process = static_cast<size_t>(10 * fchunk / chunks); // show process every %10
			if (process != oldprocess)
				std::cout << '.';
			oldprocess = process; // process gets age and become old :)
		};

		for (; chunk < chunks; ++chunk) {
			// Read - _Count: BUFFER_SIZE
			input_vec_reset(isRemaining);
			interrupted_input_idx = Read(ch_start, ch_end);

			// Write - _Count: BUFFER_SIZE
			input_vec_reset(isRemaining);
			interrupted_output_idx = Write(ch_start, ch_end);

			process_meter(chunk, chunks);
		}
		if (remaining > 0) {
			isRemaining = true;
			input_vec.resize(remaining, 0);

			// Read - _Count: remaining
			input_vec_reset(isRemaining);
			interrupted_input_idx = Read(ch_start, ch_end);
			input_vec.resize(interrupted_input_idx, 0);
			//input_vec.shrink_to_fit(); // possible reallocation!

			// Write - _Count: BUFFER_SIZE
			input_vec_reset(isRemaining);
			interrupted_output_idx = Write(ch_start, ch_end);

			std::cout << '.';  // show last process every
		}

		// -*-*-* Done *-*-*-
		std::cout << "\nDone!\n";
		input.close();
		output.close();
		return 0; // Success
	}
	void CopyBinaryUtility_Main() {
		// all in one
		all_in_one_test();

		// chunk by chunk read and write
		chunk_by_chunk_test();
	}
}
namespace Assignments
{
	typedef uint8_t BYTE;
	typedef std::allocator<BYTE> BYTE_allocator;
	typedef std::char_traits<BYTE> BYTE_char_traits;

	//using string = std::basic_string<BYTE, BYTE_char_traits, BYTE_allocator >;
	using ios = std::basic_ios<BYTE, BYTE_char_traits>;
	//using streambuf = std::basic_streambuf<BYTE, BYTE_char_traits>;
	//using istream = std::basic_istream<BYTE, BYTE_char_traits>;
	//using ostream = std::basic_ostream<BYTE, BYTE_char_traits>;
	//using iostream = std::basic_iostream<BYTE, BYTE_char_traits>;
	//using stringbuf = std::basic_stringbuf<BYTE, BYTE_char_traits, std::allocator<BYTE>>;
	//using istringstream = std::basic_istringstream<BYTE, BYTE_char_traits, BYTE_allocator>;
	//using ostringstream = std::basic_ostringstream<BYTE, BYTE_char_traits, BYTE_allocator>;
	//using stringstream = std::basic_stringstream<BYTE, BYTE_char_traits, BYTE_allocator>;
	//using filebuf = std::basic_filebuf<BYTE, BYTE_char_traits>;
	using ifstream = std::basic_ifstream<BYTE, BYTE_char_traits>;
	using ofstream = std::basic_ofstream<BYTE, BYTE_char_traits>;
	using fstream = std::basic_fstream<BYTE, BYTE_char_traits>;

	namespace fs = std::filesystem;
	using namespace fs; // changing the name of namespace not to confuse with other namespaces ;)
	bool isFileAvailable(const ios& file) {
		// not a bood idea :|
		if (!file) {
			throw std::runtime_error("Could not open the source file");
			return false;
		}
		return true;
	}
	bool isFileAvailable(const std::ios& file) {
		// not a bood idea :(
		if (file.fail()) {
			throw std::runtime_error("Could not open the source file");
			return false;
		}
		return true;
	}
	void resetLocationCursor(std::ifstream& input, std::ofstream& output, auto input_offset = 0, auto output_offset = 0)
	{
		input.seekg(input_offset, std::ios::beg);
		output.seekp(output_offset, std::ios::beg);
	}
	void resetLocationCursor(std::ifstream& input, ofstream& output, auto input_offset = 0, auto output_offset = 0)
	{
		input.seekg(input_offset, std::ios::beg);
		output.seekp(output_offset, std::ios::beg);
	}
	void resetLocationCursor(ifstream& input, ofstream& output, auto input_offset = 0, auto output_offset = 0)
	{
		input.seekg(input_offset, std::ios::beg);
		output.seekp(output_offset, std::ios::beg);
	}
	void source_subroutine(std::ifstream& input, const std::string& source_filename = "FileIO.cpp") {
		path source(current_path());
		std::cout << "current_path: " << source << '\n';
		source /= source_filename; // current_path() + "FileIO.cpp" string operation

		input.setstate(std::ios::binary | std::ios::in);
		isFileAvailable(input);
		input.open(source);
		// Stop eating new lines in binary mode!!!
		//input.unsetf(std::ios::skipws);
	}
	void source_subroutine(ifstream& input, const std::string& source_filename = "FileIO.cpp") {
		path source(current_path());
		std::cout << "current_path: " << source << '\n';
		source /= source_filename; // current_path() + "FileIO.cpp" string operation

		input.setstate(std::ios::binary | std::ios::in);
		isFileAvailable(input);
		input.open(source);
		// Stop eating new lines in binary mode!!!
		//input.unsetf(std::ios::skipws);
	}
	void destination_subroutine(ofstream& output, const std::string& destination_filename = "FileIO_Copy.cpp") {
		path destination(current_path());
		destination /= destination_filename; // current_path() + "FileIO_Copy.cpp" string operation
		if (std::filesystem::exists(destination)) {
			//throw std::runtime_error("file already exist");
		}

		output.setstate(std::ios::binary | std::ios::out);
		isFileAvailable(output);
		output.open(destination);
		// Stop eating new lines in binary mode!!!
		//output.unsetf(std::ios::skipws);
	}
	void destination_subroutine(std::ofstream& output, const std::string& destination_filename = "FileIO_Copy.cpp") {
		path destination(current_path());
		destination /= destination_filename; // current_path() + "FileIO_Copy.cpp" string operation
		if (std::filesystem::exists(destination)) {
			//throw std::runtime_error("file already exist");
		}

		output.setstate(std::ios::binary | std::ios::out);
		isFileAvailable(output);
		output.open(destination);
		// Stop eating new lines in binary mode!!!
		//output.unsetf(std::ios::skipws);
	}
	void TextFileCopy() {
		using namespace std::filesystem;
		path source(current_path());
		source /= "Source.cpp";
		path dest(current_path());
		dest /= "Copy.cpp";

		std::ifstream input{ source };
		if (!input) {
			std::cout << "Source file not found" << std::endl;
			return;
		}
		std::ofstream output{ dest };

		std::string line;
		/*
		getline returns input (ifstream). The while condition checks for failbit
		through the overloaded bool operator of ifstream. When it fails to read
		any more lines, it sets the fail bit & the bool operator return false for !failbit().
		*/
		while (std::getline(input, line)) {
			output << line << std::endl;
		}
		input.close();
		output.close();
	}
	void all_in_one_time(uintmax_t file_size, std::ifstream& input, ofstream& output) {
		// read-write all in one time. pre-allocationg is good :)
		// you cannot do anything while copying and writing is bad :(

		// reset the "location cursor"
		resetLocationCursor(input, output, 0, 0);

		std::vector<BYTE> input_vec;
		input_vec.reserve(file_size);
		// -*-*-* Read *-*-*-
		{
			// increase locality
			auto Read = [&input, &input_vec]() {
				std::copy(
					std::istream_iterator<BYTE>(input),
					std::istream_iterator<BYTE>(),
					std::back_inserter(input_vec)
				);
			};
			Read();
			input_vec.shrink_to_fit();
			resetLocationCursor(input, output, 0, 0);
		}

		// -*-*-* Write *-*-*-
		{
			// increase locality
			auto Write = [&output, &input_vec]() {
				if (!output.write(&input_vec.front(), input_vec.size())) {
					throw std::runtime_error("Error occured during write operation");
				}
			};
			Write();
			resetLocationCursor(input, output, 0, 0);
		}
	}
	void all_in_one_test()
	{
		// -*-*-* source *-*-*-
		std::string source_filename = "FileIO.cpp";
		std::ifstream input;
		source_subroutine(input, source_filename);
		auto file_size = fs::file_size(source_filename);

		// -*-*-* destination *-*-*-
		std::string destination_filename("FileIO_Copy.cpp");
		ofstream output;
		destination_subroutine(output, destination_filename);

		// -*-*-* Copying *-*-*-
		std::cout << "Copying\n";
		all_in_one_time(file_size, input, output);
		// -*-*-* Done *-*-*-
		std::cout << " Done!" << std::endl;
		input.close();
		output.close();
		fs::remove(destination_filename);
	}
	void Copy(const path& source, const path& destination) {
		std::ifstream input(source, std::ios::in | std::ios::binary);
		if (!input) {
			throw std::runtime_error("Could not open the source file");
		}
		std::ofstream output(destination, std::ios::out | std::ios::binary);
		if (!output) {
			throw std::runtime_error("Could not open the destination file");
		}
		auto fileSize = file_size(source);
		const unsigned int BUFFER_SIZE = 512;
		//char buffer[BUFFER_SIZE]{};
		std::vector<char> buffer{};
		buffer.reserve(BUFFER_SIZE);
		buffer.resize(BUFFER_SIZE, 0);
		auto&& buffer_data = buffer.data();

		std::cout << "-*-*-*-*-* Copying *-*-*-*-*-" << source << '\n';
		if (fileSize < BUFFER_SIZE) {
			//Source file is small, so read completely and write into target
			if (!input.read(buffer_data, fileSize)) {
				throw std::runtime_error("Error occurred during read operation");
			}
			if (!output.write(buffer_data, fileSize)) {
				throw std::runtime_error("Error occurred during write operation");
			}
		}
		else {
			//Split the file into chunks
			auto chunks = fileSize / BUFFER_SIZE;
			int remaining = fileSize % BUFFER_SIZE;
			int progress{}, oldProgress{};
			for (int i = 0; i < chunks; i++) {
				if (!input.read(buffer_data, BUFFER_SIZE)) {
					throw std::runtime_error("Error occurred during read operation");
				}
				if (!output.write(buffer_data, BUFFER_SIZE)) {
					throw std::runtime_error("Error occurred during write operation");
				}
				/*
				 * Get progress from 0 to 10 and print .s
				 *
				 * I'm calculating the percentage of the
				 * chunks copied. However, I multiply it by
				 * 10 to ensure its value is greater than 0
				 * and I can compare it with its old value
				 * later. Conversion to integer is necessary
				 * because we cannot compare two float
				 * values precisely. If the old and new
				 * values of percentage are different,
				 * then we print the period on the screen.
				 */
				progress = static_cast<int>((10 * static_cast<float>(i) / chunks));
				if (progress != oldProgress)
					std::cout << ".";
				oldProgress = progress;
			}
			/*
			The next read operation will read less than BUFFER_SIZE & the buffer may
			contain leftover characters from the last read operation.
			Therefore, zero out the buffer.
			*/
			//memset(buffer_data, '\0', BUFFER_SIZE);
			buffer.resize(BUFFER_SIZE, 0);

			//Read and write the remaining bytes
			if (remaining > 0) {
				if (!input.read(buffer_data, remaining)) {
					throw std::runtime_error("Error occurred during read operation");
				}
				if (!output.write(buffer_data, remaining)) {
					throw std::runtime_error("Error occurred during write operation");
				}
				std::cout << ".";
			}
		}
		std::cout << " Done!" << std::endl;
		input.close();
		output.close();
	}
	int chunk_by_chunk_test()
	{
		// -*-*-* source *-*-*-
		std::vector<std::string> source_filenames{
		"1 Minute Timer.mp4", // much much large size
		"CppLands.png", // much large size
		"CppMountain.jpeg", // large size
		"Integer.cpp", // medium size
		"lyrics.txt", // small size
		"empty.txt" // empty
		};

		std::vector<path> sources(source_filenames.size(), current_path());
		std::cout << "current source path: " << sources[0] << '\n';
		for (size_t idx = 0; idx < sources.size(); ++idx) {
			sources[idx] /= source_filenames[idx]; // current_path() + "FileIO.cpp" string operation
		}

		// -*-*-* destination *-*-*-
		std::vector<std::string> destination_filenames{
			"1 Minute Timer_Copy.mp4", // much much large size
			"CppLands_Copy.png", // much large size
			"CppMountain_Copy.jpeg", // large size
			"Integer_Copy.cpp", // medium size
			"lyrics_Copy.txt", // small size
			"empty_Copy.txt" // empty
		};
		std::vector<path> destinations(destination_filenames.size(), current_path());
		std::cout << "destination source path: " << destinations[0] << '\n';

		for (size_t idx = 0; idx < destinations.size(); ++idx) {
			destinations[idx] /= destination_filenames[idx]; // current_path() + "FileIO_Copy.cpp" string operation
		}

		// Operation
		for (size_t idx = 0; idx < sources.size(); ++idx) {
			Copy(sources[idx], destinations[idx]);
		}


		return 0;
	}
	void CopyBinaryUtility_Main() {
		// only text copy
		// TextFileCopy();

		// all in one
		//all_in_one_test();

		// chunk by chunk read and write
		chunk_by_chunk_test();
	}
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
			CopyBinaryUtility_Main();
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
	//BasicFileIO::FileIO_Main();
	//CopyUtility::CopyTextUtility_Main();
	//CopyUtility::CopyBinaryUtility_Main();
	Assignments::Assignment_Tests();
}