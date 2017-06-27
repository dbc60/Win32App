#include "platform.h"
#include "Win32AppConfig.h"
#include <Windows.h>
#include <new>


template<>
Win32AppT<Win32AppConfig>::Win32AppT(int argc, wch**argv)
    : argc_(argc), argv_(argv)
{

}


template<>
Win32AppT<Win32AppConfig>::Win32AppT()
    : argc_(0), argv_(nullptr) {
    wch* cmdline = GetCommandLineW();
    argv_ = CommandLineToArgvW(cmdline, &argc_);
    if (argv_ == nullptr) {
        // Get the error code, log the error, and throw std::bad_alloc
        // DWORD last_error = GetLastError();
        // LOG_ERROR() << "Failed to get command line: " << last_error;
        throw std::bad_alloc();
    }
}


template<>
Win32AppT<Win32AppConfig>::~Win32AppT() {
    if (argv_ != nullptr) {
        LocalFree(argv_);
    }
}
