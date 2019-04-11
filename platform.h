#ifndef PLATFORM_H__
#define PLATFORM_H__

#include <stdio.h>
#include <stdarg.h>

#define LOGAT "(@%s:%d)"

#if defined(__MINGW32__)
#pragma message "### Platform = MinGW32 ###"
// Windows must log explicitly to a file
extern FILE *LOGFILE;
#define log(p, m, f, l, ...) fprintf(LOGFILE, p LOGAT m "\n", f, l, ##__VA_ARGS__); fflush(LOGFILE)

#elif defined(_EE)
#pragma message "### Platform = PlayStation 2 SDK ###"
// PS2: Just log on the network link FOR NOW
#define log(p, m, f, l, ...) printf(p LOGAT m "\n", f, l, ##__VA_ARGS__)
#include <gsToolkit.h>
extern GSGLOBAL *gsGlobal;
extern GSFONTM *gsFontm;

#else
#pragma message "### Platform = Generic ###"
//#error "Unsupported platform"
#define log(p, m, f, l, ...) printf(p LOGAT m "\n", f, l, ##__VA_ARGS__)

#endif

#define info(s, ...) log("INFO", s, __FILE__, __LINE__, ##__VA_ARGS__)
#define dbg(s, ...) info(s, ##__VA_ARGS__)
#define error(s, ...) log("ERROR", s, __FILE__, __LINE__, ##__VA_ARGS__)
#define fatal(s, ...) do {\
    log("FATAL", s, __FILE__, __LINE__, ##__VA_ARGS__); \
    fatal_handler(s); \
 }while(0)
void fatal_handler(const char *msg);

#endif
