#pragma once

#include "platform.h"
#include "Win32AppT.h"
#include "HelpCommandT.h"
#include "LoggerG3LogT.h"
#include "LogVSOutputWindowSink.h"


struct Win32AppConfig {
    typedef Win32AppT<Win32AppConfig>       Win32App;
    typedef HelpCommandT<Win32AppConfig>    HelpCommand;
    typedef LoggerG3LogT<Win32AppConfig>    Logger;
    typedef LogVSOutputWindowSink           LogSink;
};

//typedef Win32AppConfig::Win32App    Win32App;
//typedef Win32AppConfig::HelpCommand HelpCommand;
//typedef Win32AppConfig::Logger      Logger;
//typedef Win32AppConfig::LogSink     LogSink;

using Win32App = Win32AppConfig::Win32App;
using HelpCommand = Win32AppConfig::HelpCommand;
using Logger = Win32AppConfig::Logger;
using LogSink = Win32AppConfig::LogSink;
