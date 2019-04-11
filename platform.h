/**
 * platform specific definitions
 * @author phy1um
 */
#ifndef PLATFORM_H__
#define PLATFORM_H__

#include <stdio.h>
#include <stdarg.h>

// formatter for line and file logging
#define LOGAT "(@%s:%d)"

#if defined(__MINGW32__)
#pragma message "### Platform = MinGW32 ###"
// windows must log explicitly to a file
extern FILE *LOGFILE;
// setup the log function to write to this logfile
#define log(p, m, f, l, ...) fprintf(LOGFILE, p LOGAT m "\n", f, l, ##__VA_ARGS__); fflush(LOGFILE)

#elif defined(_EE)
#pragma message "### Platform = PlayStation 2 SDK ###"
// PS2: Just log on the network link FOR NOW
#define log(p, m, f, l, ...) printf(p LOGAT m "\n", f, l, ##__VA_ARGS__)
#include <gsToolkit.h>
// global gsKit state
extern GSGLOBAL *gsGlobal;
extern GSFONTM *gsFontm;

#else
#pragma message "### Platform = Generic ###"
//#error "Unsupported platform"
#define log(p, m, f, l, ...) printf(p LOGAT m "\n", f, l, ##__VA_ARGS__)

#endif

// define logging functions that build upon the common log
#define info(s, ...) log("INFO", s, __FILE__, __LINE__, ##__VA_ARGS__)
#define dbg(s, ...) info(s, ##__VA_ARGS__)
#define error(s, ...) log("ERROR", s, __FILE__, __LINE__, ##__VA_ARGS__)
#define fatal(s, ...) do {\
    log("FATAL", s, __FILE__, __LINE__, ##__VA_ARGS__); \
    fatal_handler(s); \
 }while(0)
// deal with a fatal condition to this program
void fatal_handler(const char *msg);

#endif
