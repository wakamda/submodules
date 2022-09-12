#ifndef __LOG_H__
#define __LOG_H__

typedef enum{
    PRIO_LOG_VERBOSE    = 0x00,
    PRIO_LOG_DEBUG      = 0x01,
    PRIO_LOG_INFO       = 0x03,
    PRIO_LOG_WARN       = 0x04,
    PRIO_LOG_ERROR      = 0x05,
    PRIO_LOG_FATAL      = 0x06,
}Log_Level_t;

int log_set_level(Log_Level_t level);
int log_get_level();
/*
 * Normally we strip ALOGV (VERBOSE messages) from release builds.
 * You can modify this (for example with "#define LOG_NDEBUG 0"
 * at the top of your source file) to change that behavior.
 */
#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 1
#else
#define LOG_NDEBUG 0
#endif
#endif

/*
 * This is the local tag used for the following simplified
 * logging macros.  You can change this preprocessor definition
 * before using the other macros to change the tag.
 */
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif


 

// ---------------------------------------------------------------------

/*
 * Simplified macro to send a verbose log message using the current LOG_TAG.
 */
#ifndef ALOGV
#if LOG_NDEBUG
#define ALOGV(...)   ((void)0)
#define ALOGHEXV(_hex, _len)   ((void)0)
#else
#define ALOGV(...) ((void)ALOG( PRIO_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#define ALOGHEXV(_desc, _hex, _len) ((void)___log_print_hex(PRIO_LOG_VERBOSE, LOG_TAG, _desc, _hex, _len))
#endif
#endif

#define CONDITION(cond)     (__builtin_expect((cond)!=0, 0))

#ifndef ALOGV_IF
#if LOG_NDEBUG
#define ALOGV_IF(cond, ...)   ((void)0)
#else
#define ALOGV_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG( PRIO_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif
#endif

/*
 * Simplified macro to send a debug log message using the current LOG_TAG.
 */
#ifndef ALOGD
#if LOG_NDEBUG
#define ALOGD(...)
#define ALOGHEXD(_desc, _hex, _len)
#else
#define ALOGD(...) ((void)ALOG( PRIO_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define ALOGHEXD(_desc, _hex, _len) ((void)___log_print_hex(PRIO_LOG_DEBUG, LOG_TAG, _desc, _hex, _len))
#endif
#endif

#ifndef ALOGD_IF
#define ALOGD_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG( PRIO_LOG_DEBUG, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an info log message using the current LOG_TAG.
 */
#ifndef ALOGI
#define ALOGI(...) ((void)ALOG( PRIO_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define ALOGHEXI(_desc, _hex, _len) ((void)___log_print_hex(PRIO_LOG_INFO, LOG_TAG, _desc, _hex, _len))
#endif

#ifndef ALOGI_IF
#define ALOGI_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG( PRIO_LOG_INFO, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send a warning log message using the current LOG_TAG.
 */
#ifndef ALOGW
#define ALOGW(...) ((void)ALOG( PRIO_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define ALOGHEXW(_desc, _hex, _len) ((void)___log_print_hex(PRIO_LOG_WARN, LOG_TAG, _desc, _hex, _len))
#endif

#ifndef ALOGW_IF
#define ALOGW_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG( PRIO_LOG_WARN, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an error log message using the current LOG_TAG.
 */
#ifndef ALOGE
#define ALOGE(...) ((void)ALOG( PRIO_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define ALOGHEXE(_desc, _hex, _len) ((void)___log_print_hex(PRIO_LOG_ERROR, LOG_TAG, _desc, _hex, _len))
#endif

#ifndef ALOGE_IF
#define ALOGE_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG( PRIO_LOG_ERROR, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

// ---------------------------------------------------------------------

/*
 * Basic log message macro.
 *
 * Example:
 *  ALOG(LOG_WARN, NULL, "Failed with error %d", errno);
 *
 * The second argument may be NULL or "" to indicate the "global" tag.
 */
#ifndef ALOG
#define ALOG(priority, tag, ...) \
    LOG_PRI(priority, tag, __VA_ARGS__)
#endif

/*
 * Log macro that allows you to specify a number for the priority.
 */
#ifndef LOG_PRI
#define LOG_PRI(priority, tag, ...) \
    __printLog(priority, tag, __VA_ARGS__)
#endif



/*
 * ===========================================================================
 *
 * The stuff in the rest of this file should not be used directly.
 */

#define __printLog(prio, tag, fmt...) \
    ___log_print(prio, tag, fmt)



extern int ___log_print(int prio, const char *tag, const char *fmt, ...);
extern int ___log_print_hex(int prio, const char *tag,  const char* desc, const void* hex, int length);

#endif
