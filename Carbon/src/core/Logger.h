#pragma once
#include <sstream>
#include <time.h>

static inline char* timenow() {
    static char buffer[64];
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

// Log Tags
#define INFO_TAG    "[INFO] "
#define WARN_TAG    "[WARNING] "
#define ERROR_TAG   "[ERROR] "
#define FATAL_TAG   "[FATAL] "
#define ASSERT_TAG  "[Assert] "

#ifdef CA_BUILD_DLL
    #define CORE_TAG    "[CORE] "
#else
    #define CORE_TAG
#endif

// Log Formats
#define DETAIL_FORMAT   "%s | %-7s | %-15s | %s:%d | "
#define DETAIL_ARGS(LOG_TAG) timenow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__
#define SIMPLE_FORMAT   "%s | %-7s | "
#define SIMPLE_ARGS(LOG_TAG) timenow(), LOG_TAG
#define NEXTLINE    "\n"
#define SEPERATOR   " | "

// Break
#ifdef CA_PLATFORM_WINDOWS
    #define break() __debugbreak()
#elif CA_PLATFORM_MAC
    #define break() __builtin_trap()
#else
    #define break()
#endif

// Logger
#define CONSOLE_LOGGER(format, ...) \
    fprintf(stderr, format, __VA_ARGS__)

#define LOGGING(format, ...)\
    CONSOLE_LOGGER(format, __VA_ARGS__)

#ifdef CA_DEBUG
    #define LOG_INFO(message, ...) LOGGING(CORE_TAG SIMPLE_FORMAT message NEXTLINE, SIMPLE_ARGS(INFO_TAG), ## __VA_ARGS__)
    #define LOG_WARN(message, ...) LOGGING(CORE_TAG SIMPLE_FORMAT message NEXTLINE, SIMPLE_ARGS(WARN_TAG), ## __VA_ARGS__)
    #define LOG_ERROR(message, ...) LOGGING(CORE_TAG SIMPLE_FORMAT message NEXTLINE, SIMPLE_ARGS(ERROR_TAG), ## __VA_ARGS__)
    #define LOG_FATAL(message, ...) {\
        LOGGING(CORE_TAG SIMPLE_FORMAT message NEXTLINE, SIMPLE_ARGS(FATAL_TAG), ## __VA_ARGS__);\
        break();\
    }
    #define ASSERT(x, message, ...) {\
        if(!(x)) {\
            LOGGING(CORE_TAG DETAIL_FORMAT #x SEPERATOR message NEXTLINE, DETAIL_ARGS(ASSERT_TAG), ## __VA_ARGS__);\
            break();\
        }\
    }
#else
    #define LOG_INFO(message, ...)
    #define LOG_WARN(message, ...)
    #define LOG_ERROR(message, ...)
    #define LOG_FATAL(message, ...)
    #define ASSERT(x, messgae, ...)
#endif
