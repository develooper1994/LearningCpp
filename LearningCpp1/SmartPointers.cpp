// input-output
#include <iostream>
#include <iosfwd>
#include <cmath>
// containers
#include <vector>
#include <array>
// memory
#include <memory>

// custom
#include "Integer.h"

#include "Project.h"
#include "Employee.h"

#include "Printer.h"

#include "Project2.h"

//Note: refc = reference counter
//Note: control block = refc

/*
* // It is actually a garbage collector of modern c++
* Smart pointers has a reference counter inside. Calls default deleter to delete resource.
* There is 3 wall known smart pointers:
* unique_ptr:	only one owner						 || cannot copy, I can only move
* shared_ptr:	one or more owner					 || Reference counter increases as it copied. Reference counter becomes 0 when all the shared pointers destroyed and deletes the underlying memory. (or end of the scope)
* weak_ptr:		doesn't increments reference counter.||	Prevent some memory leaks.
* !!! If you are not sure what kind of smart pointer you need start with unique_ptr and iterate while debugging. !!! Use your BRAIN
* Compiler point out the places where you are attempting a copy of the unique_ptr.
*
* Note: You can check memory leaks with valgrind in Linux https://valgrind.org/ and other memory sanitizer https://clang.llvm.org/docs/MemorySanitizer.html
*/



// -*-*-* UNIQUE AND SHARED *-*-*-
namespace UNIQUEandSHARED {
	// -*-*-* UNIQUE *-*-*-
	void Display(Integer* p) {
		if (!p) { // check the null
			return;
		}
		std::cout << p->GetValue() << '\n';
	}
	Integer* GetPointer(int value) {
		auto* p = new Integer{ value };
		return p;
	}
	void ProcessByValue(std::unique_ptr<Integer> p) {
		// I don't need p object after the Process function. I can move object to give the ownership.
		std::cout << "processing data into z0rt: " << p->GetValue() << '\n';
	}

	void ProcessByReference(const std::unique_ptr<Integer>& p) {
		// I can access to p after function
		std::cout << "processing data into z0rt: " << p->GetValue() << '\n';
	}

	void notRecommended1(int value) {
		// It becomes a little hard to read and we humans in these cases forget to delete!
		// In these cases we should use "smart pointers" to don't forget delete.
		Integer* p = GetPointer(value);
		if (p == nullptr) {
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
		// change every raw pointers with smart pointers.
		// unique_ptr deletes object end of the scope. I don't have to deal with memory management at all.
		// unique_ptr has explicit constructors. So that we have to use direct initialization.
		std::unique_ptr<Integer> p{ GetPointer(value) };
		if (p == nullptr) {
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

	// -*-*-* SHARED *-*-*-

	void DisplayEmployeeInfoRaw(Employee* e) {
		std::cout << "Employee project details: ";
		e->GetProject()->DisplayDetails();
	}
	//void notRecommended2(std::string name = "Validator") {
	//	// !!! more than one owner !!!
	//	// Project can have many employees || Employee has only one project.
	//	Project* prj = new Project{};
	//	prj->SetName("Validator");
	//	Employee* e1 = new Employee{};
	//	e1->SetProject(prj);
	//	Employee* e2 = new Employee{};
	//	e2->SetProject(prj);
	//	Employee* e3 = new Employee{};
	//	e3->SetProject(prj);
	//	DisplayEmployeeInfoRaw(e1);
	//	DisplayEmployeeInfoRaw(e2);
	//	DisplayEmployeeInfoRaw(e3);
	//	prj->DisplayDetails();
	//	// Can we not have the "Employee destructor" call delete on the "project pointer"? NO
	//	// This "project pointer" is shared between "Employee instances". "Employee instances" do not really own this pointer
	//	delete prj;
	//	delete e1;
	//	delete e2;
	//	delete e3;
	//}


	//void DisplayEmployeeInfoSmart(const std::unique_ptr<Employee>& e) 
	void DisplayEmployeeInfoSmart(const std::shared_ptr<Employee>& e)
	{
		std::cout << "Employee project details: ";
		e->GetProject()->DisplayDetails();
	}
	void shared(std::string name = "Validator") {
		// !!! one or more owner !!!
		// change every raw pointers with smart pointers.
		// Project can have many employees || Employee has only one project.

		std::shared_ptr<Project> prj(new Project{}); // It must to be shared_ptr
		prj->SetName("Validator");
		// Project will have "array or list of employees"(multiple employees)	so that employee must be shared_ptr
		std::shared_ptr<Employee> e1(new Employee{});
		e1->SetProject(prj); // prj cannot be unique_ptr. move empties inside of it ;). Be Careful!
		std::shared_ptr<Employee> e2(new Employee{});
		e2->SetProject(prj);
		std::shared_ptr<Employee> e3(new Employee{});
		e3->SetProject(prj);

		//e3.reset(); // decrements the reference counter of smart pointer.
		// also I can assign a new Employee. counter = 0 => delete underlying pointer || Otherwise do nothing but take ownership of this new pointer. count inside this smart pointer will be 1.
		//e3.reset(new Employee{});
		if (e3) { // I can check e3 is it a valid pointer.(is this null, it this deleted?)
			// Valid
		}
		else {
			// Not Valid
		}

		DisplayEmployeeInfoSmart(e1);
		DisplayEmployeeInfoSmart(e2);

		// shared_ptr has reference counter. Reference counter shared between all the copies.
		std::cout << "reference count= " << prj.use_count() << '\n'; //only meant to be used for debugging

		prj->DisplayDetails();
		// Reference counter becomes 0 when all the shared pointers destroyed and deletes the underlying memory. (or end of the scope)
	}

	void subroutineUNIQUEANDSHARED() {
		// -*-*-* UNIQUE *-*-*-
		auto value = 5;
		notRecommended1(value);
		unique(value);

		// -*-*-* SHARED *-*-*-
		std::string name = "Validator";
		//notRecommended2(name);
		shared(name);
	}
}

// -*-*-* WEAK *-*-*-
namespace WEAK {
	// !!! extremely important !!!!
	// brain usage time!
	// doesn't increases refc.
	// weak pointer knows underlying refc of smart pointers.
	// multiple weak_pointers can point to the same control block.

	// expire method return 0 when control block is 0. that indicates the shared_ptr and underlying memory is no longer available.
	// lock method return shared_pointer. refc incremented by one

	void subPrinterShared() {
		PrinterShared prt;
		int num{};
		std::cin >> num;
		std::shared_ptr<int> p{ new int{num} }; // refc=1
		// p passed as a parameter inside Set(), a copy of the shared_ptr created and the reference counter becomes 2. 
		// copy increases refc to 2. nullptr assignment decreases refc to 1. End of the function refc is not 0 so that is a !memory leak!
		prt.Set(p);
		// <body>

		if (*p > 10) {
			//delete p;
			p = nullptr; // decreases reference counter, but not deleted in this line.
			//p.reset(); // makes same thing.
		}

		// </body>
		prt.Display();
		//delete p;	// smart pointer throws error.
	}
	void subPrinterWeak() {
		PrinterWeak prt;
		int num{};
		std::cin >> num;
		std::shared_ptr<int> p{ new int{num} }; // refc=1
		// p passed as a parameter inside Set(), a copy of the shared_ptr created and the reference counter becomes 2. 
		// copy increases refc to 2. nullptr assignment decreases refc to 1. End of the function refc is not 0 so that is a !memory leak!
		prt.Set(p);
		// <body>

		if (*p > 10) {
			//delete p;
			p = nullptr; // decreases reference counter, but not deleted in this line.
			//p.reset(); // makes same thing.
		}

		// </body>
		prt.Display();
		//delete p;	// smart pointer throws error.
	}

	void subCircularReference() {
		// Brain out
		// You have to give your attention
		std::cout << "\n-*-*-* raw pointer *-*-*-\n";
		{
			/*
			EmployeeRAW()
			ProjectRAW()
			~EmployeeRAW()
			~ProjectRAW()
			*/
			EmployeeRAW* employee = new EmployeeRAW{};
			ProjectRAW* prj = new ProjectRAW{};

			employee->prj = prj;
			prj->employee = employee;

			delete employee;
			delete prj;
		}
		std::cout << "\n-*-*-* shared pointer *-*-*-\n";
		{
			/*
			EmployeeSmart()
			ProjectSmart()
			* !There is no detractors!
			*/
			std::shared_ptr<EmployeeSmart> employee{ new EmployeeSmart{} }; // employee-refc = 1 owner
			std::shared_ptr<ProjectSmart> prj{ new ProjectSmart{} }; // prj-refc = 1 owner

			employee->prj = prj; // employee-refc = 2 owner
			prj->employee = employee; // prj-refc = 2 owner

			//refc decreases by 1 end of the scope. both of refc is 1 end of the scope. !They are never delete automatically!
		}
		std::cout << "\n-*-*-* weak pointer *-*-*-\n";
		{
			std::shared_ptr<EmployeeWeak> employee{ new EmployeeWeak{} }; // employee-refc = 1 owner
			std::shared_ptr<ProjectWeak> prj{ new ProjectWeak{} }; // prj-refc = 1 owner

			employee->prj = prj; // employee member prj initialized with prj control block
			prj->employee = employee; // prj-refc = 2 owner

			std::cout << employee.use_count() << '\n';
			std::cout << prj.use_count() << '\n';
		}

		/*
		Source: https://www.nextptr.com/tutorial/ta1382183122/using-weak_ptr-for-circular-references
		* Circular dependency, Circular Reference is a memory problem.
		* Look carefully to the "void dispatchEvent(Event e)" methods.
		*
		// !!! WRONG !!!
		struct Event {
			//..
		};

		class Listener {
		public:
		 void onEvent(Event e) {
		  //Handle event from Source
		 }
		 //...
		};

		class Source {
		public:
			void dispatchEvent(Event e) {
				if(listener)
					listener->onEvent(e);
			}

		 void
		 registerListener(const std::shared_ptr<Listener>& lp) {
		  listener = lp;
		 }
		 //...
		private:
		 //Strong reference to Listener
		 std::shared_ptr<Listener> listener;
		};


		// !!! CORRECT !!!
		class Source {
		public:
			void dispatchEvent(Event e) {
				//Acquire strong ref to listener
				if(auto listener = weakListener.lock()) {
					listener->onEvent(e);
				}
				else {
					//Handle if required
				}
		 }

		 void
		 registerListener(const std::shared_ptr<Listener>& lp) {
		  weakListener = lp;
		 }
		 //...
		private:
		 //Weak reference to Listener
		 std::weak_ptr<Listener> weakListener;
		};

		*/
	}

	void subroutineWEAK() {
		subPrinterShared();	// !memory leak!
		subPrinterWeak();
		subCircularReference();
	}
}

namespace Others {
	// -*-*-* DELETERS *-*-*-
	/*
	* Smart pointers release resources by calling deleters. If you don't you define any, it will call default.
	* If it cannot find it, compiler gives and error.
	*/

	// -*-*-* First(recommended)(function objects) *-*-*-
	// You can use class
	struct Free {
		void operator()(int* p) {
			free(p);
			std::cout << "I'm a free pointer...\n";
		}
	};
	// -*-*-* Second *-*-*-
	void MallocFree(int* p) {
		free(p);
		std::cout << "I'm a free pointer...\n";
	}
	void subUniqueDeleter() {
		// int* p = (int*)malloc(4);
		std::unique_ptr<int, Free> p{ (int*)malloc(4), Free{} };
		std::unique_ptr<int, void(*)(int*)> p2{ (int*)malloc(4), MallocFree }; // with function pointer declaration
		*p = 100;
		std::cout << *p << '\n';
		//free(p);
	}
	void subSharedDeleter() {
		// int* p = (int*)malloc(4);
		std::shared_ptr<int> p{ (int*)malloc(4), Free{} };
		std::shared_ptr<int> p2{ (int*)malloc(4), MallocFree };  // without function pointer declaration
		*p = 100;
		std::cout << *p << '\n';
		//free(p);
	}



	void subDynamicArray() {
		std::cout << "\nunique_ptr<int>\n";
		{
			std::unique_ptr<int> b{ new int[] {1,2,3,4,5} };
			//b[3] = 55; // !!! ERROR !!!
			b.get()[3] = 55; // Valid
			std::cout << "sizeof(b)= " << sizeof(b) << '\n'; // gives the wrong answer. Because smart pointer holds extra data inside

		}
		std::cout << "\nunique_ptr<int[]>\n";
		{
			// calls correct constructor and deleter automatically.
			std::unique_ptr<int[]> b{ new int[] {10,20,30,40,50} };
			b[3] = 55; // Valid
			b.get()[0] = 111; // Valid
			std::cout << "sizeof(b)= " << sizeof(b) << '\n'; // gives the wrong answer. Because smart pointer holds extra data inside
		}
		std::cout << '\n';
	}

	struct vec3 {
		int x{}, y{}, z{};
		vec3(int x = 0, int y = 0, int z = 0) noexcept : x(x), y(y), z(z)
		{}
		friend std::ostream& operator<<(std::ostream& os, const vec3& v) {
			return os << "{ x= " << v.x << "|| y= " << v.y << "|| z= " << v.z << '}\n';
		}
	};
	void subMakeSmart() {
		/*
		I cannot...
		* cannot initialize with initializer_list(there is some resource. I tested and completion failed)
		* cannot specify deleter. If you are using custom deleter, you have to construct custom smart pointer and allocate the memory for your resource yourself.
		* so that...
		I recommend "make_unique" and "make_shared" if you are not using custom deleters. Otherwise choose "unique_ptr" and "shared_ptr"
		*/
		std::cout << "\nmake_unique and make_shared\n";
		// Modern c++ ways that i can find
		std::cout << "\nstd::make_unique\n";
		{
			// Modern c++ way-1
			auto b1 = std::make_unique<int>(5); // same as "std::unique_ptr<int> b1{ new int{5} };". "creates just one 5"
			auto b2 = std::make_unique<vec3>(1, 2, 3);
			auto bArr = std::make_unique<int[]>(5); // Note: cannot initialize dynamic array using make_unique. Use bArr[0] = 10;
			bArr[0] = 10;
		}
		std::cout << "\nstd::make_shared. C++20 standard. Calls more functions than make_unique.\n";
		{
			// Modern c++ way-1
			auto b1 = std::make_shared<int>(5); // same as "std::unique_ptr<int> b1{ new int{5} };". "creates just one 5"
			auto b2 = std::make_shared<vec3>(1, 2, 3); // use the vec3 "vec3(int, int, int)" constructor.

			// shared_ptr to a value-initialized short[0]; // initialized with zero
			auto bArr = std::make_shared<short[]>(128); // it is like a short* bArr = new short[128]{0};
			bArr[0] = 10;
			// shared_ptr to a value-initialized short[128]; // initialized with zero
			auto sp5 = std::make_shared<short[128]>(); // it is like a short sp5[128]{}; 

			// shared_ptr to a value-initialized long[5][3][4];
			auto sp4 = std::make_shared<long[][3][4]>(5); // long*** sp6 = new long[5]; long j[3][4]; *sp6 = j;
			// shared_ptr to a value-initialized long[5][3][4];
			auto sp6 = std::make_shared<long[5][3][4]>(); // long sp6[5][3][4]{};

			// shared_ptr to a double[256], where each element is 2.0;
			auto sp7 = std::make_shared<double[]>(256, 2.0); // double sp7  = new double[256]{2.0};

			// shared_ptr to a vector<int>[4], where each vector has contents {5, 6};
			// std::vector<int> sp9 = new std::vector<int>[4]{5, 6}; // has contents {5, 6};
			auto sp9 = std::make_shared<std::vector<int>[]>(4, { 5, 6 });
			// shared_ptr to a vector<int>[4], where each vector has contents {5, 6};
			// std::vector<int> sp9[4]; // each std::vector<int> has contents {5, 6};
			auto spC = std::make_shared<std::vector<int>[4]>({ 5, 6 });
		}
	}



	void subroutineOthers() {
		subUniqueDeleter();
		subSharedDeleter();
		subDynamicArray();
		subMakeSmart();
	}
}

void SmartPointers_main()
{
	UNIQUEandSHARED::subroutineUNIQUEANDSHARED();
	WEAK::subroutineWEAK();
	Others::subroutineOthers();
}
