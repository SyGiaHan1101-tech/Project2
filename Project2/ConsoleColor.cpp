using HANDLE = void*;
using DWORD = unsigned long;
using WORD = unsigned short;

extern "C" __declspec(dllimport)
HANDLE __stdcall GetStdHandle(DWORD nStdHandle);

extern "C" __declspec(dllimport)
int __stdcall SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes);

void setColor(int color) {
    HANDLE console = GetStdHandle((DWORD)-11);
    SetConsoleTextAttribute(console, (WORD)color);
}