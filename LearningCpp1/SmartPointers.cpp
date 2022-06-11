// input-output
#include <iostream>
// containers
#include <vector>
#include <array>
// memory
#include <memory>
// math
#include <cmath>
//

// custom
#include "Integer.h"

/* Document
*
*/

namespace {
	void Display(Integer* p) {
		if (!p) // check the null
		{
			return;
		}
		std::cout << p->GetValue() << '\n';
	}
	Integer* GetPointer(int value) {
		auto* p = new Integer{ value };
		return p;
	}
	void ProcessByValue(std::unique_ptr<Integer> p) {
		std::cout << "processing data into z0rt: " << p->GetValue() << '\n';
	}

	void ProcessByReference(const std::unique_ptr<Integer>& p) {
		std::cout << "processing data into z0rt: " << p->GetValue() << '\n';
	}

	void notRecommended(int value) {
		// It becomes a little hard to read and we humans in these cases forget to delete!
		// In these cases we should use "smart pointers" to don't forget delete.
		Integer* p = GetPointer(value);
		if (p == nullptr)
		{
			p = new Integer{};
		}
		p->SetValue(11);
		Display(p);
		delete p;
		p = nullptr; // it is a good practice. If you don't assign "nullptr" pointers will still hold the address of the memory has been deleted If you don't allocate new memory.
		p = new Integer{};
		*p = __LINE__;
		Display(p);
		delete p;
	}

	void unique(int value) {
		// !!! only one owner !!!
		// unique_ptr deletes object end of the scope. I don't have to deal with memory management at all.
		// unique_ptr has explicit constructors. So that we have to use direct initialization.
		std::unique_ptr<Integer> p{ GetPointer(value) };
		if (p == nullptr)
		{
			// p = new Integer{};
			// 1) holds an existing pointer, that will be deleted
			// 2) and then takes ownership of this pointer.
			p.reset(new Integer{});
		}
		p->SetValue(11);
		Display(p.get()); // access the underlying pointer
		// delete p;
		p = nullptr; // meaning in smart pointer is simply deletes the underlying pointer and makes the pointer variable NULL
		p.reset(new Integer{});
		*p = __LINE__;
		Display(p.get());
		// I can access to p after function
		ProcessByReference(p);
		*p = 43;
		// I don't need p object after the Process function. I can move object to give the ownership.
		ProcessByValue(std::move(p)); // ByValue
		// std::cout << p->GetValue(); << '\n'; // I cannot access to p
		//delete p;
	}

	void shared(int value) {
		// not yet implemented
		// !!! more than one owner !!!

	}

	void subroutine1() {
		auto value = 5;
		notRecommended(value);
		unique(value);
		shared(value);
	}
}

void SmartPointers_main()
{
	subroutine1();
}
