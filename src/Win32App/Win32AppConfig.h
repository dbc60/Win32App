#pragma once

#include "platform.h"
#include "Win32AppT.h"
#include "HelpCommandT.h"
#include "LogLevelCommandT.h"
#include "LoggerG3LogT.h"
#include "LogVSOutputWindowSink.h"


struct Win32AppConfig {
    typedef Win32AppT<Win32AppConfig>           Win32App;
    typedef HelpCommandT<Win32AppConfig>        HelpCommand;
    typedef LogLevelCommandT<Win32AppConfig>    LogLevelCommand;
    typedef LoggerG3LogT<Win32AppConfig>        Logger;
    typedef LogVSOutputWindowSink               LogSink;
};

using Win32App = Win32AppConfig::Win32App;
using HelpCommand = Win32AppConfig::HelpCommand;
using LogLevelCommand = Win32AppConfig::LogLevelCommand;
using Logger = Win32AppConfig::Logger;
using LogSink = Win32AppConfig::LogSink;

extern HelpCommand      helpCommand;
extern LogLevelCommand  logLevelCommand;
