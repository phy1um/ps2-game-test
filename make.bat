
set "MAKE=D:\Alpha\Port\mingw-get\bin\mingw32-make"
set /P "TYPE=Thing to make:"
%MAKE% -f Makefile.pc %TYPE%
pause