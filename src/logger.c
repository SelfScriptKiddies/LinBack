#include "logger.h"
#include <stdarg.h>

#define LOG_LEVEL TRACE
#define COLOR_LOG

/*
Main idea of this code is to use only functions, which are compiled, and give empty functions, if level won't be displayed.
Optimizing size of binary :)
*/

#define TRACE       10
#define DEBUG       20
#define INFO        30
#define WARNING     40
#define ERROR       50
#define CRITICAL    60

// Colorful config

#ifdef COLOR_LOG
#define KRED        "\x1B[31m"
#define KGREEN      "\x1B[32m"
#define KYELLOW     "\x1B[33m"
#define KBLUE       "\x1B[34m"
#define KMAGENTA    "\x1B[35m"
#define KCYAN       "\x1B[36m"
#define KWHITE      "\x1B[37m"
#define KRESET      "\x1B[0m"
#else
#define KRED        ""
#define KGREEN      ""
#define KYELLOW     ""
#define KBLUE       ""
#define KMAGENTA    ""
#define KCYAN       ""
#define KWHITE      ""
#define KRESET      ""
#endif

// Log function

#ifdef LOG_LEVEL <= CRITICAL
#include <time.h>
#include <string.h>
#include <stdio.h>

static const char *FORMAT = "%d:%d:%d [%s%s%s : %s] %s \n"; // {Hour}:{Minute}:{Second} [{Color}{Level}{Reset} : {Name}] {message}

static void log(const char* level, const char* color, const char* root, const char* message) {
    time_t now_time = time(NULL);
    struct tm time = *localtime(&now_time);
    printf(FORMAT, time.tm_hour, time.tm_min, time.tm_sec, color, level, KRESET, root, message);
    free(message);
}

static const char* concat_variadic(const char* fmt, va_list arg_list) {
    const char* message = malloc(1024);
    char buffer[32];
    while (*fmt != 0) {
        switch (*fmt)
        {
        case 's':
            strcat(message, va_arg(arg_list, char *));
            break;
        case 'd':
            sprintf(buffer, "%d", va_arg(arg_list, int));
            break;
        case 'f':
            sprintf(buffer, "%f", va_arg(arg_list, double));
            break;
        case 'c':
            sprintf(buffer, "%c", va_arg(arg_list, int));
            break;
        default:
            break;
        }
        ++fmt;
    }

    return message;
}
#endif



// TRACE LEVEL

#if LOG_LEVEL >= TRACE
void trace(const char* root, const char* fmt_args, ...) {
    va_list args;
    va_start(args, fmt_args);
    const char* message = concat_variadic(args, fmt_args);
    log("TRACE", KWHITE, root, message);
};
#else
void trace(const char* root, const char* fmt_args, ...) {};
#endif

// DEBUG LEVEL 

#if LOG_LEVEL <= DEBUG
void debug(const char* root, const char* fmt_args, ...) {
    va_list args;
    va_start(args, fmt_args);
    const char* message = concat_variadic(args, fmt_args);
    log("DEBUG", KCYAN, root, message);
};
#else
void debug(const char* root, const char* fmt_args, ...) {};
#endif

// INFO LEVEL 

#if LOG_LEVEL <= INFO
void info(const char* root, const char* fmt_args, ...) {
    va_list args;
    va_start(args, fmt_args);
    const char* message = concat_variadic(args, fmt_args);
    log("INFO", KBLUE, root, message);
};
#else
void info(const char* root, const char* fmt_args, ...) {};
#endif

// WARNING LEVEL 

#if LOG_LEVEL <= WARNING
void warning(const char* root, const char* fmt_args, ...) {
    va_list args;
    va_start(args, fmt_args);
    const char* message = concat_variadic(args, fmt_args);
    log("WARNING", KYELLOW, root, message);
};
#else
void warning(const char* root, const char* fmt_args, ...) {};
#endif

#if LOG_LEVEL <= ERROR
void error(const char* root, const char* fmt_args, ...) {
    va_list args;
    va_start(args, fmt_args);
    const char* message = concat_variadic(args, fmt_args);
    log("ERROR", KRED, root, message);
};
#else
void error(const char* root, const char* fmt_args, ...) {};
#endif

#if LOG_LEVEL >= FATAL
void fatal(const char* root, const char* fmt_args, ...) {
    va_list args;
    va_start(args, fmt_args);
    const char* message = concat_variadic(args, fmt_args);
    log("!FATAL!", KRED, root, message);
};
#else
void fatal(const char* root, const char* fmt_args, ...) {};
#endif


