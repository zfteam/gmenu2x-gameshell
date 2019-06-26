
#ifndef DEBUG_H
#define DEBUG_H

#define NODEBUG_L 0
#define ERROR_L 1
#define WARNING_L 2
#define INFO_L 3
#define DEBUG_L 4

#ifndef LOG_LEVEL
# define LOG_LEVEL INFO_L
#endif

// -------------

#ifndef COLOR_DEBUG
# define COLOR_DEBUG   "\e[0;34m"
#endif
#ifndef COLOR_WARNING
# define COLOR_WARNING "\e[01;33m"
#endif
#ifndef COLOR_ERROR
# define COLOR_ERROR   "\e[01;31m"
#endif

#define COLOR_END "\e[00m"

#if (LOG_LEVEL >= DEBUG_L)
# ifdef COLOR_DEBUG
#  define DEBUG(str, ...) \
    fprintf(stdout, COLOR_DEBUG "DEBUG: " str COLOR_END "\n", ##__VA_ARGS__)
# else
#  define DEBUG(str, ...) \
    fprintf(stdout, "DEBUG: " str "\n", ##__VA_ARGS__)
# endif
#else
# define DEBUG(...)
#endif

#if (LOG_LEVEL >= INFO_L)
# ifdef COLOR_INFO
#  define INFO(str, ...) \
    fprintf(stdout, COLOR_INFO str COLOR_END "\n", ##__VA_ARGS__)
# else
#  define INFO(str, ...) \
    fprintf(stdout, str "\n", ##__VA_ARGS__)
# endif
#else
# define INFO(...)
#endif

#if (LOG_LEVEL >= WARNING_L)
# ifdef COLOR_WARNING
#  define WARNING(str, ...) \
    fprintf(stderr, COLOR_WARNING "WARNING: " str COLOR_END "\n", ##__VA_ARGS__)
# else
#  define WARNING(str, ...) \
    fprintf(stderr, "WARNING: " str "\n", ##__VA_ARGS__)
# endif
#else
# define WARNING(...)
#endif

#if (LOG_LEVEL >= ERROR_L)
# ifdef COLOR_ERROR
#  define ERROR(str, ...) \
    fprintf(stderr, COLOR_ERROR "ERROR: " str COLOR_END "\n", ##__VA_ARGS__)
# else
#  define ERROR(str, ...) \
    fprintf(stderr, "ERROR: " str "\n", ##__VA_ARGS__)
# endif
#else
# define ERROR(...)
#endif

#endif
