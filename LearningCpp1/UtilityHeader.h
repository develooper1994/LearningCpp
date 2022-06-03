#pragma once
#include "AllMacrosInOnePlace.h"
inline void settings() {
	std::srand(std::time(nullptr));
}

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
