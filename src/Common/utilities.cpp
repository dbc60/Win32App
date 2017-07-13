/* ========================================================================
Author: Douglas B. Cuthbertson
(C) Copyright 2015 by Douglas B. Cuthbertson. All Rights Reserved.
======================================================================== */

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


// Converter used to process wstrings
std::wstring_convert<convert_type, wchar_t> converter;

// Converts string to wstring via a converter
std::wstring StringToWstring(const std::string& input,
                             std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>& converter) {
    return converter.from_bytes(input);
}

std::wstring StringToWstring(const std::string& input) {
    return StringToWstring(input, converter);
}

// Converts wstring to string via a converter
std::string WstringToString(const std::wstring& input,
                            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>& converter) {
    return converter.to_bytes(input);
}

std::string WstringToString(const std::wstring& input) {
    return WstringToString(input, converter);
}


u32
StringToLogLevel(const std::string& log_level) {
    u32 result;
    std::string test;

    // Make sure the input string is in lowercase
    for (auto itr : log_level) {
        test += ::tolower(itr);
    }

    if (test == "trace") {
    result = 0;
    } else if (test == "debug") {
    result = 1;
    } else if (test == "info") {
        result = 2;
    } else if (test == "warning") {
    result = 3;
    } else if (test == "error") {
    result = 4;
    } else if (test == "fatal") {
    result = 5;
    } else {
        // Unknown, so just return info
        result = 2;
    }

    return result;
}


std::string LogLevelToString(u32 ll) {
    std::string result;

    switch (ll) {
    case 0:
        result = "trace";
        break;

    case 1:
        result = "debug";
        break;

    case 2:
        result = "info";
        break;

    case 3:
        result = "warning";
        break;

    case 4:
        result = "error";
        break;

    case 5:
        result = "fatal";
        break;

    default:
        result = "info";
        break;
    }

    return result;
}
