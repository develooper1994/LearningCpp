#pragma once
void settings();

// DON'T RESTRÝCT THE SCOPE IF YOU ARE GOÝNG TO USE ÝT GLOBALLY

/* restrict the scope with ...
* https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-error-lnk2005?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(LNK2005)%26rd%3Dtrue&view=msvc-170
* inline
* static
* __declspec(selectany)
* Remove the function body from the header file and leave only the declaration, then implement the function in one and only one source file:
*/
void Print(int, char);

void EndMessage();
