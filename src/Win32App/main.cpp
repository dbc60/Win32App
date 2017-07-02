#include "platform.h"
#include "utilities.h"
#include "Win32AppConfig.h"
#include "Win32AppCliCommands.h"
#include <iostream>
#include <iterator>


bool processCommandLine(int argc, wch** argv) {
    bool result = false;

    for (auto cmd = std::begin(helpCommand);
         cmd != std::end(helpCommand) && !result;
         cmd++) {
        result = (*cmd)->Match(argv[1]);
        if (result) {
            if ((*cmd) == &helpCommand) {
                if ((*cmd)->ParseCommand(argc, argv)) {
                    if (!(*cmd)->Execute()) {
                        std::wcout << L"Command " << (*cmd)->GetName() << L" failed. Error code: " << (*cmd)->GetErrorCode() << std::endl;
                    } else {
                        std::wcout << L"Command " << (*cmd)->GetName() << L" completed successfully" << std::endl;
                        //LOG(Logger::info) << "Command " << WstringToString((*cmd)->GetName(), converter) << " completed successfully";
                    }
                } else {
                    std::wcout << L"Error: Malformed command" << std::endl;
                    std::wcout << (*cmd)->GetDetailedHelp() << std::endl;
                }
            } else {
                std::wcout << std::endl
                    << "Warning: this program must be run with administrative privileges."
                    << std::endl << std::endl;
            }

        }
    }

    if (!result) {
        std::wcout << L"Error: Unrecognized command." << std::endl;
        std::wcout << helpCommand.Usage(argv[0]) << std::endl;
    }

    return result;
}


int wmain(int argc, wch** argv) {
    Win32App    win32_app(argc, argv);
    wch         dir_path[_MAX_PATH];
    u32         dir_result;
    dir_result = setCurrentDirectory(dir_path,
                                     sizeof dir_path / sizeof dir_path[0]);
    std::string log_basename("Win32App");
    std::string log_path("./");
    Logger::initLogging(log_basename.c_str(), log_path.c_str());
    LOG(Logger::info) << "Logging is initialized";
    if (argc > 1) {
        helpCommand.CommandRegistration(&helpCommand);
        processCommandLine(argc, argv);
    }

    LOG(Logger::trace) << "trace-level message";
    LOG(Logger::debug) << "debug-level message";
    LOG(Logger::info) << "App end";

    return 0;
}
