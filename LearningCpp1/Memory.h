#pragma once

void OldCDynamicMemory() {
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
		int* p = (int*)malloc(sizeof(int)) * 1; // malloc(size of type) * number of type
		if (p == NULL)
		{
			printf("Failed to allocate memory\n");
			return -1;
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
			return -1;
		}
		*p = 5;
		printf("%d", *p);
		free(p); // p becomes "Dangling pointer". It is useless and harmfull
		p = NULL; // I have to assign null to the pointer to eliminate it.
		free(p); // without NULL assignment program crashes.
	}
}

void OldCppDynamicMemory()
{
	//new
	//delete
	using namespace std;
	cout << "Old C++ style memory \n";
}

void Memory_Main()
{
	//OldCDynamicMemory();
	OldCppDynamicMemory();
}
