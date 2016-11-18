#include <windows.h>
#include <stdio.h>
#include <direct.h>
#define GetCurrentDir _getcwd

#include <iostream>

#define MAX_REG_SIZE 0x7FFF
void waitForUser(void);

int main () {
    HKEY hkey;
    DWORD dwDisposition;
    DWORD path_len = MAX_REG_SIZE;
    DWORD path_type = REG_SZ;
    DWORD len;
    
    std::wstring path_str;
    std::string::size_type found_len;
    std::string::size_type found;

    wchar_t toolchain_path_w[FILENAME_MAX];
    wchar_t toolchain_bin_w[FILENAME_MAX];
    wchar_t prev_path[MAX_REG_SIZE];

    if (!GetCurrentDirectoryW(sizeof(toolchain_path_w), toolchain_path_w)) {
        goto err;
    }

    toolchain_path_w[lstrlenW(toolchain_path_w)] = '\0';

    wcscpy(toolchain_bin_w, toolchain_path_w);
    wcscat(toolchain_bin_w, L"\\bin");
    printf("CEDEV Varible: %ls\n", toolchain_path_w);
    printf("PATH Variable: %ls\n", toolchain_bin_w);

    // Get the current key value if it exists
    if (RegOpenKeyW(HKEY_CURRENT_USER, L"Environment", &hkey) != ERROR_SUCCESS) {
        goto err;
    }

    RegQueryValueExW(hkey, L"CEDEV", NULL, &path_type, (LPBYTE)&prev_path, &path_len);
    RegCloseKey(hkey);

    // open the user enviornment key to add the CEDEV variable
    if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Environment", 0, NULL, 0, KEY_SET_VALUE, NULL, &hkey, &dwDisposition) != ERROR_SUCCESS) {
        goto err;
    }

    len = lstrlenW(toolchain_path_w) * sizeof(wchar_t) + 1;
    if (RegSetValueExW(hkey, L"CEDEV", 0, REG_SZ, (LPBYTE)toolchain_path_w, len) != ERROR_SUCCESS) {
        goto err;
    }
    RegCloseKey(hkey);

    // open the system path enviornment key to add the CEdev\bin path
    if (RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", &hkey) != ERROR_SUCCESS) {
        goto err;
    }

    wchar_t path[MAX_REG_SIZE];
    path_len = MAX_REG_SIZE;
    path_type = REG_SZ;
    RegQueryValueExW(hkey, L"Path", NULL, &path_type, (LPBYTE)&path, &path_len);

    path_str.assign(path);
    
    // delete the old path if there is one
    if (lstrlenW(prev_path)) {
        // organize the new path
        wcscat(prev_path, L"\\bin");
        
        printf("\nRemoving previous location...\n");
        found_len = lstrlenW(prev_path);
        found = path_str.find(prev_path);

        // remove the old path if needed
        if (found != std::string::npos) {
            if(path_str.length() != found + found_len && path_str.at(found + found_len) == ';') {
                found_len++;
            }
            if (found && path_str.at(found-1) == ';') {
                found--;
                found_len++;
            }
            path_str.erase(found, found_len);
        }
    }
    
    // append the new path
    path_str.append(L";");
    path_str.append(toolchain_bin_w);

    len = path_str.length() * sizeof(wchar_t) + 1;
    if (RegSetValueExW(hkey, L"Path", 0, REG_SZ, (LPBYTE)path_str.c_str(), len) != ERROR_SUCCESS) {
        goto err;
    }

    RegCloseKey(hkey);
    std::cout << std::endl << "Success!";
    waitForUser();
    return 0;

err:
    printf("Errors were encountered. Please check rights or set up manually.\n");
    waitForUser();
    return errno;
}

void waitForUser(void) {
    std::cout << std::endl << "Press [Enter] to exit...";
    std::cin.ignore();
}
