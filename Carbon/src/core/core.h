#pragma once

#ifdef CA_PLATFORM_WINDOWS
    #ifdef CA_BUILD_DLL
        #define CARBON_API __declspec(dllexport)
    #else
        #define CARBON_API __declspec(dllimport)
    #endif
#elif CA_PLATFORM_MAC
    #ifdef CA_BUILD_LIB
        #define CARBON_API __attribute__((visibility("default")))
    #else
        #define CARBON_API
    #endif
#else
    #define CARBON_API
#endif

#define Bit(x) 1 << x

#define NON_COPYABLE_CLASS(className) \
    className(const className& rhs) = delete; \
    className& operator=(const className& rhs) = delete; \
    className(className&& rhs) = delete; \
    className& operator=(className&& rhs) = delete;