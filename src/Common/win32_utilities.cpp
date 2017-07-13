#include "win32_utilities.h"
#include "utilities.h"


// Convert an HRESULT to one of many possible Win32 error codes
DWORD Win32FromHresult(HRESULT hr) {
    DWORD   result;

    if ((hr & 0xFFFF0000) == MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, 0)) {
        // Could have come from many values, but we choose this one
        result = HRESULT_CODE(hr);
    } else if (hr == S_OK) {
        result = HRESULT_CODE(hr);
    } else {
        // otherwise, we got an impossible value
        result = ERROR_INVALID_DATA;
    }

    return result;
}


//! @brief store the logging level for the service in the registry
void
SetLogLevelToRegistry(DWORD log_level) {
    HKEY    softwareKey, agentKey;
    LONG        st;

    // Get the polling interval from the registry.
    st = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                        WIN32_SOFTWARE_KEY_NAME,
                        0,
                        KEY_ALL_ACCESS | KEY_WOW64_64KEY,
                        &softwareKey);

    if (ERROR_SUCCESS == st) {
        st = ::RegOpenKeyEx(softwareKey,
                            WIN32_APP_REGISTRY_KEY,
                            0,
                            KEY_ALL_ACCESS | KEY_WOW64_64KEY,
                            &agentKey);
        if (ERROR_SUCCESS == st) {
            ::RegSetValueEx(agentKey,
                            WIN32_APP_LOG_LEVEL,
                            0,
                            REG_DWORD,
                            reinterpret_cast<BYTE*>(&log_level),
                            sizeof log_level);
            ::RegCloseKey(agentKey);
        }

        ::RegCloseKey(agentKey);
    }
}


DWORD
GetLogLevelFromRegistry() {
    HKEY    softwareKey, agentKey;
    LONG    st;
    DWORD   log_level = StringToLogLevel("info");
    DWORD   sizeData = sizeof log_level;

    // Get the polling interval from the registry.
    st = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                        WIN32_SOFTWARE_KEY_NAME,
                        0,
                        KEY_ALL_ACCESS | KEY_WOW64_64KEY,
                        &softwareKey);

    if (ERROR_SUCCESS == st) {
        st = ::RegOpenKeyEx(softwareKey,
                            WIN32_APP_REGISTRY_KEY,
                            0,
                            KEY_ALL_ACCESS | KEY_WOW64_64KEY,
                            &agentKey);
        if (ERROR_SUCCESS == st) {
            st = ::RegGetValue(agentKey,
                               nullptr,
                               WIN32_APP_LOG_LEVEL,
                               RRF_RT_REG_DWORD,
                               nullptr,
                               &log_level,
                               &sizeData);
            if (st != ERROR_SUCCESS) {
                // Assume the log level is not set, so set one
                SetLogLevelToRegistry(log_level);
            }
            ::RegCloseKey(agentKey);
        }

        ::RegCloseKey(softwareKey);
    }

    return log_level;
}
