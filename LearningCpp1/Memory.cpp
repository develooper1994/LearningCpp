/* Dangling pointer = You free memory but pointer still points to the deleted memory.
// You have to reset pointers pointing address.
// to do that
// in "C language" => pointer = NULL
// in "C++ language" => pointer = nullptr
// *if you delete end of funtion you don't need to use nullptr. It becomes automatically destroyed en of scope(en of scope of variable= en of life of variable)
*/

/*
//		New as opposite to malloc can call constructors of class
//		It can be overload
//		New as opposite to malloc throws exception if it failed to allocate. malloc returns null
*/
#include <memory>
#include <iostream>
int OldCDynamicMemory() {
	// malloc= uninitialized raw memory
	// calloc= initialize with zero
	// realloc= re-allocate the memory
	// You cannot initalize with different value with these functions but c++ can do it.
	// these functions return NULL if failed to allocate memory. So that always check the NULL
	// If you forgot the free the memory before the function exit. memory cannot be released. !!! It causes serious memory leaks !!!
	using namespace std;
	cout << "Old C style memory management\n";

	// malloc. uninitialized raw memory
	{
		// malloc itself gives "void ptr". I have to convert to "int ptr"
		// in C++ implict type conversion not allowed.
		int* p = (int*)malloc(sizeof(int) * 1); // malloc(size of type * number of type)
		if (p == NULL)
		{
			printf("Failed to allocate memory\n");
			return -1; // unsuccessful exit
		}
		*p = 5;
		printf("%d", *p);
		free(p); // p becomes "Dangling pointer". It is useless and harmfull
		p = NULL; // I have to assign null to the pointer to eliminate it.
		free(p); // without NULL assignment program crashes.
	}

	// calloc. initialize with zero
	{
		// malloc itself gives "void ptr". I have to convert to "int ptr"
		// in C++ implict type conversion not allowed.
		int* p = (int*)calloc(1, sizeof(int)); // calloc(number of type, size of type)
		if (p == NULL)
		{
			printf("Failed to allocate memory\n");
			return -1; // unsuccessful exit
		}
		*p = 5;
		printf("%d", *p);
		free(p); // p becomes "Dangling pointer". It is useless and harmfull
		p = NULL; // I have to assign null to the pointer to eliminate it.
		free(p); // without NULL assignment program crashes.
	}
	return 0; // successful exit
}

void OldCppDynamicMemory()
{
	// 1. new = allocate with specific value or not with specific value. 
	//		New as opposite to malloc can call constructors of class 
	//		It can be overload
	//		New as opposite to malloc throws exception if it failed to allocate. malloc returns null
	// So that it is better.
	// 2. delete = release the memory
	using namespace std;
	cout << "Old C++ style memory \n";

	cout << "\nsingle element allocation\n";
	{
		int* p = new int(5);
		*p = 6;
		cout << "*p= " << *p << '\n';
		// !!! Always remember to delete. It is really important !!!
		delete p; // p becomes "dangling pointer"
		p = nullptr; // "nullptr" is better place holder in c++
	}

	cout << "\narray, vector element allocation\n";
	{
		int* pEmpty = new int[5];
		int* p = new int[5] {0, 1, 2, 3, 4};
		for (size_t i = 0; i < 5; i++)
		{
			p[i] *= 10;
		}
		// !!! Always remember to delete. It is really important !!!
		delete[]p;
		p = nullptr; // You don't have put it end of parenthesis. It is end of life the pointer. It will be deleted automatically.
	}

	cout << "\character arrays or old c style string element allocation\n";
	{
		char* p = new char[] {"Cpp"}; // Also Valid
		//char* p = new char[4] {"Cpp"}; // Don't forget to count '\0'(NULL terminating character). chararacter count+1
		// Note: strcpy is deprecated. use strcpy_s
		strcpy_s(p, 4, "C++"); // strcpy will automatically append a NULL. 
		cout << p << '\n';
		delete[]p;
		p = nullptr;
	}

	cout << "\n2d array, 2d vector element allocation\n";
	{
		int* xdim = new int[3]; // number of x coordinates
		int* ydim = new int[3]; // number of y coordinates
		int** table = new int* [2]; // number of dimensions.
		table[0] = xdim;
		table[1] = ydim;


		table[0][1] = std::rand(); // second element of the first row.
		cout << table[0][1] << '\n';


		// delete them in the creation order.
		delete[] xdim; xdim = nullptr;
		delete[] ydim; ydim = nullptr;
		delete[] table; table = nullptr;
	}

}

void Memory_Main()
{
	//OldCDynamicMemory();
	//OldCppDynamicMemory();
}