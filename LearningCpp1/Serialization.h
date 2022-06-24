#pragma once
#include <string>
#include <iostream>
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
class IDocument
{
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
