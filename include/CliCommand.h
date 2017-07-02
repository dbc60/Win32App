#pragma once

#include "platform.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <Windows.h>


/**
The base class for CLI commands.
*/
template <typename Config_>
class CliCommand {
public:
    typedef Config_     Config;
    virtual ~CliCommand() {
    }

    // run the command - return true for success, false otherwise.
    virtual bool Execute() = 0;

    // Parse a command-line
    virtual bool ParseCommand(int argc, wch** argv) {
        int compare_result = ::lstrcmpi(argv[1], command_name_.c_str());

        return (0 == compare_result);
    }

    // A short string that shows the args
    const std::wstring& GetHelp() const {
        return help_short_;
    }

    // The command name with a description of the args
    const std::wstring& GetDetailedHelp() const {
        return help_detailed_;
    }

    // The name of the command
    const std::wstring& GetName() const {
        return command_name_;
    }

    const int GetErrorCode() const {
        return error_code_;
    }


    bool Match(const wch *command_name) const {
        return 0 == ::lstrcmpi(command_name_.c_str(), command_name);
    }

protected:
    CliCommand(const std::wstring command_name,
               const std::wstring help_short,
               const std::wstring help_detailed)
        : command_name_(command_name), help_short_(help_short),
        help_detailed_(help_detailed), error_code_(0) {
        ;
    }

    CliCommand(const wch *command_name,
               const wch *help_short,
               const wch *help_detailed, int args_min, int args_max)
        : command_name_(command_name), help_short_(help_short),
        help_detailed_(help_detailed), error_code_(0) {
        ;
    }

    // No copy/move constructors nor assignment operators for now. The copy
    // constructor and copy assignment operator might be useful later.
    CliCommand(const CliCommand& other) = delete;
    CliCommand& operator=(const CliCommand& other) = delete;
    CliCommand(CliCommand&& other) = delete;
    CliCommand& operator=(CliCommand&& other) = delete;

    u32 error_code_;

    const std::wstring command_name_;
    const std::wstring help_short_;
    const std::wstring help_detailed_;
};
