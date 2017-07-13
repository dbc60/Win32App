/* ========================================================================
Author: Douglas B. Cuthbertson
(C) Copyright 2015 by Douglas B. Cuthbertson. All Rights Reserved.
======================================================================== */
#include "Win32AppConfig.h"
#include "utilities.h"
#include "win32_utilities.h"


LogLevelCommand::LogLevelCommandT()
    : CliCommand(L"log",
                 L"log [-l, --level <level>]",
                 L"log:\n    -l, --level (trace|debug|verbose|info|warning|error|fatal)    set the level for logging",
                 0, 4),
#if defined(_DEBUG)
    // This setting is better for debugging
    log_level_(Logger::trace)
#else
    log_level_(Logger::info)
#endif
{
    ;
}


bool
LogLevelCommand::Execute() {
    SetLogLevelToRegistry(log_level_.value);

    // Report the current log level
    //log_level_ = GetLogLevelFromRegistry();
    std::wcout << L"The log level is "
        << StringToWstring(log_level_.text) << std::endl;

    return true;
}


bool
LogLevelCommand::ParseCommand(int argc, wchar_t **argv) {
    bool result = true;

    if (::lstrcmpi(argv[1], command_name_.c_str()) == 0) {
        if (argc == 4) {
            // We expect "foo.exe log --level debug", for example.
            if (0 == ::lstrcmpi(argv[2], L"--level")
                || 0 == ::lstrcmpi(argv[2], L"-l")) {
                std::string lvl_text = WstringToString(argv[3]);
                int level = StringToLogLevel(lvl_text);
                log_level_ = LEVELS(level, lvl_text);
            } else {
                // Parse failure
                LOG(Logger::error)
                    << "register command Parse error. Unrecognize argument \""
                    << argv[2] << L"\"";
                result = false;
            }
        } else {
            // If "foo.exe log", then return the current log level
            int level = GetLogLevelFromRegistry();
            std::string lvl_text = LogLevelToString(level);
            log_level_ = LEVELS(level, lvl_text);
        }
    } else {
        // Report an error
        helpCommand.Usage(argv[0]);
        result = false;
    }

    return result;
}
