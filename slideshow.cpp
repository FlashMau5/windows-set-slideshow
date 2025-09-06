#include <windows.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <comdef.h>
#include <iostream>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: slideshow.exe <Slideshow Path>\n";
		system("pause");
        return 1;
    }

    size_t size_needed = MultiByteToWideChar(CP_UTF8, 0, argv[1], -1, nullptr, 0);
    wchar_t* path = new wchar_t[size_needed];
	size_t len = wcslen(path);
	if (len >= 2 && path[0] == L'"' && path[len-1] == L'"') {
		path[len-1] = L'\0';
		path++;
	}
    MultiByteToWideChar(CP_UTF8, 0, argv[1], -1, path, size_needed);
    DWORD size = sizeof(path);

    CoInitialize(NULL);
    IDesktopWallpaper* dw = nullptr;
    CoCreateInstance(CLSID_DesktopWallpaper, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&dw));

    IShellItem* folder = nullptr;
    SHCreateItemFromParsingName(path, nullptr, IID_PPV_ARGS(&folder));

    IShellItemArray* arr = nullptr;
    SHCreateShellItemArrayFromShellItem(folder, IID_PPV_ARGS(&arr));

    dw->SetSlideshow(arr);

    arr->Release();
    folder->Release();
    dw->Release();
    CoUninitialize();
    return 0;
}
