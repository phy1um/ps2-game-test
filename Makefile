
EE_BIN = bin/test.elf
PC_BIN = bin/test.exe

OBJS =  main.o game.o events.o
EE_OBJS = $(OBJS) platform_ps2.o sys_ps2.o draw_ps2.o events_ps2.o romdisk.o

INCLUDE = -I/usr/include/ -I/usr/include/SDL
EE_INCS = -I$(PS2SDK)/ports/include \
			-I$(PS2DEV)/gsKit/include \
			-I$(PS2SDK)/ee/common/include

CFLAGS = -Wall
EE_CFLAGS = $(CFLAGS) 

EE_LDFLAGS = -L$(PS2SDK)/ports/lib -L$(PS2DEV)/gsKit/lib \
			 -L$(PS2SDK)/ee/common/lib -L$(PS2SDK)/ee/lib
EE_LIBS = -lpad -lgskit -lgskit_toolkit -ldmakit -lmc -lc -lpng -lz \
		  -lm  -lkernel -ldebug -lromfs
EE_LIBS += -Xlinker

PS2HOST=192.168.1.140

PC_LIBS = -lSDL -lSDLmain
CC=x86_64-w64-mingw32-gcc

ROMDISK=bin/romdisk.iso
GENROMFS=$(PS2SDK)/bin/genromfs
ROMDIR=res

# from ROMFS
EE_CFLAGS += -Dfopen=ropen
EE_CFLAGS += -Dfclose=rclose
EE_CFLAGS += -Dfread=rread
EE_CFLAGS += -Dfwrite=rwrite
EE_CFLAGS += -Dfseek=rseek
EE_CFLAGS += -Dftell=rtell
EE_CFLAGS += -Dfgetc=rgetc
#EE_CFLAGS += -Dfgets=rgets
EE_CFLAGS += -Dmmap=rmmap

ps2: $(EE_BIN) $(ROMDISK)
debug: EE_CFLAGS += -g
debug: ps2

ROMDEPS := $(wildcard $(ROMDIR)/*)

$(ROMDISK): $(ROMDEPS)
	@echo Creating romdisk
	$(GENROMFS) -f $@ -d $(ROMDIR)

romdisk.o: $(ROMDISK)
	$(PS2SDK)/bin/bin2o -a 16 -n $(ROMDISK) romdisk.o romdisk

clean:
	rm -f $(EE_OBJS) $(EE_BIN) $(ROMDISK)

run:
	ps2client -t 10 -h $(PS2HOST) execee host:$(EE_BIN)

reset:
	ps2client -t 5 -h $(PS2HOST) reset

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
