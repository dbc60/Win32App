#pragma once

#include "platform.h"

template <class Config_>
class Win32AppT {
public:
    typedef Config_ Config;

private:
    int argc_;
    wch** argv_;

public:
    Win32AppT();
    Win32AppT(int argc, wch** argv);
    ~Win32AppT();
};
