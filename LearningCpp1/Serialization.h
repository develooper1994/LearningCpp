#pragma once
#include <string>
#include <iostream>
#include <iosfwd>
#include <string_view>
#include <source_location>

#include "UtilityHeader.h"

/*
!!! Polymorphism memory-leaks !!! (base object reference and pointer)
* If child the class object is deleted through a base class pointer, then the destructor of the base will be directly involved.
That leads memory leaks!
* c++ 11 has override-final keywords to solve it.
- final can prevents the users of this class from inheriting it, and that can be done by making this class with the final.

*/

class Serialization final
{
private:
public:
	// constructor
	Serialization() = default;
	// destructor
	~Serialization()
	{
		// release resources
	}

	// member-function
	void serialize(const std::string& filename);
	void deserialize(const std::string& filename);
	void displayStatics(); // I am going to re-implement in a different class.
};

// class FastSerialiazation : public Serialization {}; // final keyword! !!! ERROR !!!

class Document
{
public:
	virtual void Serialize1(float version) {
		std::cout << __FUNCSIG__ << '\n';
		std::cout << "Document::Serialize\n";
	}
	virtual void Serialize2(float version) {
		std::cout << __FUNCSIG__ << '\n';
		std::cout << "Document::Serialize\n";
	}
	void Serialize3(float version) // without virtual
	{
		std::cout << __FUNCSIG__ << '\n';
		std::cout << "Document::Serialize\n";
	}
};

class Text : public Document
{
public:
	// if function explicitly overloaded. Function definitions must be same and "VIRTUAL"
	void Serialize1(float version) override
	{
		std::cout << __FUNCSIG__ << '\n';
		std::cout << "Text::Serialize\n";
	}
	void Serialize2(float version) // without "override"
	{
		std::cout << __FUNCSIG__ << '\n';
		std::cout << "Text::Serialize\n";
	}
	void Serialize3(float version) // without "override"
	{
		std::cout << __FUNCSIG__ << '\n';
		std::cout << "Text::Serialize\n";
	}
};

class RichText : public Text
{
public:
	void Serialize1(float version) override // Not a virtual function
	{
		std::cout << "RichText::Serialize\n";
	}
	void Serialize2(float version) override // Not a virtual function
	{
		std::cout << "RichText::Serialize\n";
	}
	/*
	void Serialize3(float version) override // Not a virtual function
	{
		std::cout << "RichText::Serialize\n";
	}
	*/

};

//class XML : public Document {
//public:
//	void Serialize1(float version) override {
//		std::cout << __FUNCSIG__ << '\n';
//		std::cout << "Document::Serialize\n";
//	}
//};

/*
* // Pure-virtual function. It is equal to interface of java and c#
* At least one pure virtual function
* Can contain other members (data, non-vertual functions,...)
* Can not be instantiated, but used through a pointer or reference
* Establishes a contract with clients
* Used for creating interface

* marked with =0
* Does not have an implementation (optional)
* Can not be invoked (except by derived classes if defined)
* No entry in the "VTABLE"
* Must be overridden by the derived classes
*/
class IDocument {
public:
	virtual void Serialize1(float version) = 0;
};

class XML : public IDocument {
public:
	void Serialize1(float version) override {
		std::cout << __FUNCSIG__ << '\n';
		std::cout << "XML::Serialize\n";
	}
};

inline void serialize(IDocument* p) {
	// doesn't call serialize XML without abstract call
	p->Serialize1(0.8f);
}

inline void Override_Final_Main()
{
	Text t;
	// This is base object reference causes !!! Polymorphism memory-leaks !!! without "override" keyword
	Document& doc = t;
	doc.Serialize1(1.2f);
	doc.Serialize2(1.2f);
	doc.Serialize3(1.2f);
}

inline void Abstraction_Main()
{
	XML xml;
	serialize(&xml);

}


/*
Multiple (Diamond) Inheritance
Example:
Stream -> InputStream
Stream -> OutputStream
InputStream, OutputStream -> IOStream
*/

// BASE!
class Stream
{
private:
	std::string FileName;
public:
	Stream(const std::string& filename) : FileName(filename) {
		std::cout << __FUNCSIG__ << '\n';
	}
	const std::string& GetFileName()const { return FileName; }
	~Stream() {
		std::cout << __FUNCSIG__ << '\n';
	}
};

// creates vptr
class OutputStream : virtual public Stream
{
private:
	std::ostream& out;
public:
	OutputStream(std::ostream& os, const std::string& filename)
		: out(os), Stream(filename)
	{
		std::cout << __FUNCSIG__ << '\n';
	}
	std::ostream& operator<<(const std::string& data) {
		out << data;
		return out;
	}
	~OutputStream() {
		std::cout << __FUNCSIG__ << '\n';
	}
};

// creates vptr
class InputStream : virtual public Stream
{
private:
	std::istream& in;
public:
	InputStream(std::istream& is, const std::string& filename)
		: in(is), Stream(filename)
	{
		std::cout << __FUNCSIG__ << '\n';
	}
	std::istream& operator>>(std::string& data)
	{
		in >> data;
		return in;
	}
	~InputStream() {
		std::cout << __FUNCSIG__ << '\n';
	}

};

// InputStream and OutputStream has vptr. So that IOStream objects 2 vptr points to the single instance of the 
class IOStream : public InputStream, public OutputStream
{
	/*
	* "Stream::Stream" called twice
	__cdecl Stream::Stream(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &)
	__cdecl InputStream::InputStream(class std::basic_istream<char,struct std::char_traits<char> > &,const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &)
	__cdecl Stream::Stream(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &)
	__cdecl OutputStream::OutputStream(class std::basic_ostream<char,struct std::char_traits<char> > &,const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &)
	__cdecl IOStream::IOStream(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &)
	__cdecl IOStream::~IOStream(void)
	__cdecl OutputStream::~OutputStream(void)
	__cdecl Stream::~Stream(void)
	__cdecl InputStream::~InputStream(void)
	__cdecl Stream::~Stream(void)
		*/
public:
	IOStream(const std::string& filename)
		: InputStream(std::cin, filename), OutputStream(std::cout, filename), Stream(filename) // "Stream(filename)" is mandotory to eliminate memory bugs.
	{
		std::cout << __FUNCSIG__ << '\n';
	}
	~IOStream() {
		std::cout << __FUNCSIG__ << '\n';
	}
};

inline void Multiple_Inheritance_Main() {
	IOStream stream("app.log");

	std::string data;
	stream >> data;
	std::cout << '\n';
	stream << data;

	// GetFileName member function inherited twice
	// to solve this we will inherit them as virtual
	stream << stream.GetFileName() << '\n';

}




