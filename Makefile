ifneq ($(PLATFORM), GCW)
$(info *** Defaulting to PC version. Specify PLATFORM=GCW for GCW build. ***)
SDL_CONFIG=/usr/bin/sdl2-config
TOOLCHAIN=
LIB_INCLUDE=/usr/lib
else
$(info *** Making GCW build. Unspecify PLATFORM=GCW for PC build. ***)
SDL_CONFIG=/opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/bin/sdl2-config
TOOLCHAIN=/opt/gcw0-toolchain/usr/bin/mipsel-linux-
LIB_INCLUDE=/opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/lib
CFLAGS+= -D_GCW_
endif

OPK_DIR=opk_build
CC=$(TOOLCHAIN)gcc
CXX=$(TOOLCHAIN)g++
STRIP=$(TOOLCHAIN)strip
EXE = lyfe
OPK = $(EXE).opk
RM = rm -f

LDFLAGS += -lshake -lSDL2 -lSDL2_ttf -lSDL2_mixer $(shell $(SDL_CONFIG) --libs)
CFLAGS += -O2 $(shell $(SDL_CONFIG) --cflags) -Wall -Wextra

REMOTE_USER=root
REMOTE_IP=192.168.0.156
REMOTE_PATH=/media/GCW_EXT/apps

SRCS=$(shell echo *.c)
OBJS=$(SRCS:%.c=%.o)

ALL : $(EXE)

.c.o:
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $*.c -o $*.o 
.cpp.o:
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $*.cpp -o $*.o 

$(EXE) : $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)
	mkdir -p $(OPK_DIR)
#	$(STRIP) $(EXE)
	cp $(EXE) $(OPK_DIR)/$(EXE)

opk : $(EXE)
	mksquashfs $(OPK_DIR) $(EXE).opk -all-root -noappend -no-exports -no-xattrs

upload : opk
	scp ./$(OPK) $(REMOTE_USER)@$(REMOTE_IP):$(REMOTE_PATH)/$(OPK)

clean :
	$(RM) $(OBJS) $(EXE) $(OPK_DIR)/$(EXE) $(OPK)

.PHONY:opk clean install uninstall ALL
