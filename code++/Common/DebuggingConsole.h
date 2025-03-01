//
// Created on 2023/01/06
//

#ifndef DEBUGGINGCONSOLE_H
#define DEBUGGINGCONSOLE_H

#include <iostream>

/// @brief 
inline void attachDebugConsole()
{
#ifndef NDEBUG
#   if WIN32
    if (::GetStdHandle(STD_OUTPUT_HANDLE) == NULL) {
        // these next few lines create and attach a console
        // to this process.  note that each process is only allowed one console.
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        (void)freopen("CON", "w", stdout);

        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);

        printf("DEBUGGING console output. Actual CP-%d, OEM: CP-%d, Console CP-%d\n", 
            GetACP(), GetOEMCP(), GetConsoleOutputCP());
    }
#   endif
#endif
}

#ifndef NDEBUG
#   define CONSOLE(x) do { std::cout << __func__ << ":" << x << '\n';  } while(0)
#else
#   define CONSOLE(x)
#endif

#define STATUS(x) do { \
    std::ostringstream ss; \
    ss << x; \
    CONSOLE ( ss.str() ); \
    GM_LOG_MSG_DIRECT(GM_Log_Status, ss.str().c_str()); \
} while(0)

/// @brief 
/// @param s 
inline void dump_to_console(const char *s)
{
    while (*s)
        printf("%02x ", *s++ & 255);
    printf("\n");
}

/// @brief
/// @param s 
inline void dump_to_console(const wchar_t *s)
{
    while (*s)
        printf("%04x ", *s++ & 0xffff);
    printf("\n");
}

#endif // DEBUGGINGCONSOLE_H
