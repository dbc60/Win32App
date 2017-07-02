#include "utilities.h"
#include <Windows.h>

/*! @brief Get the directory in which this app's executable resides and make it
the current directory.
*/
u32
setCurrentDirectory(wch *dir_path, size_t length) {
    wch full_path[_MAX_PATH];
    u32 result = ERROR_SUCCESS;
    u32 count = ::GetModuleFileNameW(nullptr,
                                     full_path,
                                     (sizeof full_path) / (sizeof full_path[0]));
    LPTSTR file_part;

    // count is the number of characters written into the buffer.
    if (count > 0) {
        // If the full path fit, then the directory path will too
        ::GetFullPathNameW(full_path,
                          static_cast<DWORD>(length),
                          dir_path,
                          &file_part);

        // Essentially shorten dir_path to the directory only with the trailing
        // directory separator.
        *file_part = L'\0';

        // Make it so!
        ::SetCurrentDirectoryW(dir_path);
    } else {
        result = ::GetLastError();
    }

    return result;
}
