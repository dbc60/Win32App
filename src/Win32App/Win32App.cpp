#include "platform.h"
#include "Win32AppConfig.h"
#include <Windows.h>
#include <new>


Win32App::Win32AppT(int argc, wch**argv)
    : argc_(argc), argv_(argv), have_local_args_(false)
{

}


Win32App::Win32AppT()
    : argc_(0), argv_(nullptr), have_local_args_(true) {
    wch* cmdline = GetCommandLineW();
    argv_ = CommandLineToArgvW(cmdline, &argc_);
    if (argv_ == nullptr) {
        // Get the error code, log the error, and throw std::bad_alloc
        // DWORD last_error = GetLastError();
        // LOG_ERROR() << "Failed to get command line: " << last_error;
        throw std::bad_alloc();
    }
}


Win32App::~Win32AppT() {
    if (have_local_args_ && argv_ != nullptr) {
        LocalFree(argv_);
    }
}
