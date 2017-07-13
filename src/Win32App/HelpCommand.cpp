/* ========================================================================
Author: Douglas B. Cuthbertson
(C) Copyright 2015 by Douglas B. Cuthbertson. All Rights Reserved.
======================================================================== */
#include "Win32AppConfig.h"


HelpCommand::HelpCommandT()
: CliCommand(
    L"help",
    L"help [-d|--details] <command>\" for command-specific options.",
    L"help [-d|--details] <command> for command-specific options. Add '-d' or '--details' for more detailed information.") {
}


void
HelpCommand::CommandRegistration(CliCommand<Config>* cmd) {
    commands_.push_back(cmd);

    usage_.str(std::wstring());
    usage_.clear();
    usage_ << L"Available COMMANDs:" << std::endl;
    const wch *separator = L"  ";
    for (auto cmd : commands_) {
        usage_ << separator << cmd->GetName();
        separator = L", ";
    }
}


bool
HelpCommand::Execute() {
    std::wcout << help_msg_.str() << std::endl;
    return true;
}


bool
HelpCommand::ParseCommand(int argc, wch **argv) {
    // reinitialize the help message
    help_msg_.str(std::wstring());
    help_msg_.clear();
    bool result = true;

    if (::lstrcmpi(argv[1], command_name_.c_str()) == 0) {
        if (argc > 2) {
            bool found = false;
            bool details = false;
            if (0 == ::lstrcmpi(argv[2], L"--details")
                || 0 == ::lstrcmpi(argv[2], L"-d")) {
                details = true;
            }

            if (!details || (details && argc > 3)) {
                for (auto cmd = std::begin(commands_);
                     cmd != std::end(commands_) && !found;
                     ++cmd) {
                    if (details) {
                        found = (*cmd)->Match(argv[3]);
                    } else {
                        found = (*cmd)->Match(argv[2]);
                    }

                    if (found) {
                        help_msg_ << L"Enter: \"" << argv[0] << L" ";
                        if (details) {
                            help_msg_ << (*cmd)->GetDetailedHelp() << std::endl;
                        } else {
                            help_msg_ << (*cmd)->GetHelp() << std::endl;
                        }
                    }
                }
            }

            if (!found) {
                result = false;
            }
        } else {
            help_msg_ << usage_.str();
        }
    }

    return result;
}
