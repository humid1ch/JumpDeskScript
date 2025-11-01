
#include <windows.h>
#include <iostream>
#include <cstdint>

typedef int32_t (*GetDesktopCount_t)();
typedef int32_t (*GetCurrentDesktopNumber_t)();
typedef int32_t (*GoToDesktopNumber_t)(int32_t);

int main() {
    HMODULE dll = LoadLibraryA("VirtualDesktopAccessor.dll");
    if (!dll) {
        std::cerr << "Error: Cannot load VirtualDesktopAccessor.dll\n";
        return 1;
    }

    auto GetDesktopCount = (GetDesktopCount_t)GetProcAddress(dll, "GetDesktopCount");
    auto GetCurrentDesktopNumber = (GetCurrentDesktopNumber_t)GetProcAddress(dll, "GetCurrentDesktopNumber");
    auto GoToDesktopNumber = (GoToDesktopNumber_t)GetProcAddress(dll, "GoToDesktopNumber");

    if (!GetDesktopCount || !GetCurrentDesktopNumber || !GoToDesktopNumber) {
        std::cerr << "Error: Missing function exports.\n";
        FreeLibrary(dll);
        return 1;
    }

    int total = GetDesktopCount();
    int cur = GetCurrentDesktopNumber();
    int next = (cur + 1) % total;

    GoToDesktopNumber(next);

    FreeLibrary(dll);
    return 0;
}
