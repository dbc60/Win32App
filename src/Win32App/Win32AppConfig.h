#pragma once

#include "platform.h"
#include "Win32AppT.h"


struct Win32AppConfig {
    typedef Win32AppT<Win32AppConfig>    Win32App;
};

typedef Win32AppConfig::Win32App  Win32App;
