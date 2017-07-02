#pragma once

#include "CliCommand.h"
#include <sstream>
#include <iostream>


// Contain a reference to all the commands to make it easier to display help.
template <typename Config>
class HelpCommandT : public CliCommand<Config> {
private:
    typedef std::vector<CliCommand<Config>*> CliContainer;

    std::wstringstream  usage_;
    std::wstringstream  help_msg_;
    CliContainer        commands_;

public:
    typedef typename CliContainer::iterator  iterator;
    typedef typename CliContainer::const_iterator const_iterator;

    HelpCommandT();
    bool Execute();

    bool ParseCommand(int argc, wch** argv);

    void CommandRegistration(CliCommand<Config>* cmd);

    inline iterator begin() {
        return commands_.begin();
    }

    inline iterator end() {
        return commands_.end();
    }

    inline const_iterator cbegin() const {
        return commands_.cbegin();
    }

    inline const_iterator cend() const {
        return commands_.cend();
    }

    // No copy/move constructors nor assignment operators for now.
    HelpCommandT(const HelpCommandT&) = delete;
    HelpCommandT& operator=(const HelpCommandT&) = delete;
    HelpCommandT(HelpCommandT&&) = delete;
    HelpCommandT& operator=(HelpCommandT&&) = delete;

    const std::wstring Usage(const wch *appName) {
        const std::wstring cws = usage_.str();

        usage_.str(std::wstring());
        usage_.clear();
        usage_ << L"Usage:" << std::endl << L"  " << appName << std::endl;
        usage_ << cws << std::endl;
        return usage_.str();
    }
};
