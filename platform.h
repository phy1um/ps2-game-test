#ifndef PLATFORM_H__
#define PLATFORM_H__

#include <stdarg.h>

#define LOGAT "(@%s:%s)"

#if defined(__MINGW32__)
// Windows must log explicitly to a file
extern FILE *LOGFILE;
#define log(p, m, f, l, ...) fprintf(LOGFILE, p LOGAT m, f, l, ##__VA_ARGS__)

#elif defined(_EE)
// PS2: Just log on the network link FOR NOW
#define log(p, m, f, l, ...) printf(p LOGAT m, f, l, ##__VA_ARGS__)
#include <gsToolkit.h>
extern GSGLOBAL *gsGlobal;
extern GSFONTM *gsFontm;

#else

//#error "Unsupported platform"
#define log(p, m, f, l, ...) printf(p LOGAT m, f, l, ##__VA_ARGS__)

#endif

#define info(s, ...) log("INFO", s, __FILE__, __LINE__, ##__VA_ARGS__)
#define error(s, ...) log("ERROR", s, __FILE__, __LINE__, ##__VA_ARGS__)
#define fatal(s, ...) do {\
    log("FATAL", s, __FILE__, __LINE__, ##__VA_ARGS__); \
    fatal_handler(s); \
 }while(0)
void fatal_handler(const char *msg);

#endif
