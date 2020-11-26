#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H

#if defined _WIN32 || defined __CYGWIN__
    // Export symbols when creating .dll and .lib, and import them when using .lib.
    #if BINDINGS_BUILD
        #define BINDINGS_API __declspec(dllexport)
    #else
        #define BINDINGS_API __declspec(dllimport)
    #endif
    // Disable warnings about exporting STL types being a bad idea. Don't use this in production
    // code.
    #pragma warning( disable : 4251 )
#else
    #define BINDINGS_API
#endif

// Define this device for package configuration
// THIS_DEFINE values:
//		1 - xavier
//		2 - hook
//		3 - main controller

#define THIS_DEVICE				1
#define DEFAULT_RECEIVER_DEVICE	3

#define	__XAVIER
//#define	__HOOK
//#define	__MAIN_CONTROLLER

#endif // GLOBAL_MACROS_H
