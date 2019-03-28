setlocal EnableDelayedExpansion

set INCLUDE=-ID:\\Beta\\C\\include\\SDL
set LDFLAGS=-LD:\\Beta\\C\\lib

set LIBS=-lSDL -lSDLmain

set CC=D:\Alpha\Port\mingw-get\bin\gcc.exe

set BIN=D:\Beta\workspace\ps2-mover-test\bin\out.exe

set "OBJS=image bmp main"
set "SRC=image.c bmp.c main.c"

echo %CC% -o %BIN% %SRC% %INCLUDE% %LDFLAGS% %LIBS%