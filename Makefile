ELFNAME=csos.elf
KERNEL=csos.bin

ASFLAGS = -march=armv6zk -mcpu=arm1176jzf-s   -Iinc -Iinc/klibc -nostdlib
CFLAGS = -O3 -march=armv6zk -mcpu=arm1176jzf-s  -fpic -Iinc -Iinc/klibc -nostdlib -ffreestanding -nostartfiles -nostdinc -nodefaultlibs  -fno-stack-protector  -mfloat-abi=hard 
LDFLAGS = -e 0x00000000 -T src/kernel/pi/link.ld -o $(ELFNAME)
CXXFLAGS=-lang=c++ -fno-rtti -fuse-cxa-atexit -std=c++11 $(CFLAGS) 
OBJGLAGS =  $(ELFNAME) -O binary $(KERNEL)
TCC=/opt/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-gcc
TCP=/opt/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-g++
TAS=/opt/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-as
TLD=/opt/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-ld
TOB=/opt/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-objcopy

     
OBJS =  \
	   src/kernel/pi/start.o src/kernel/pi/intr.o src/kernel/pi/halt.o  \
	   src/cmdParse.o \
	   src/kernel/mm.o \
	   src/kernel/pmm.o \
	   src/kernel/pi/main.o \
	   src/kshell.o \
	   src/kernel/pi/mailbox.o \
	   src/kernel/pi/utils.o \
	   src/kernel/pi/iob.o \
	   src/kernel/pi/atag.o \
	   src/kernel/pi/power.o \
	   src/softEvent/event.o src/gol.o src/kernel/pi/isr.o \
	   src/kernel/pi/dmb.o \
	   src/kernel/pi/put.o \
	   src/kernel/font8x8.o \
	   src/kernel/font12x16.o

AEBI = src/aebi/_udivsi3.o src/aebi/_divsi3.o

KLIBC = \
	src/klibc/malloc.o \
	src/klibc/string.o \
	src/klibc/stdio.o \
    src/klibc/time.o \
    src/klibc/typeconv.o \
    src/klibc/assert.o \
    src/klibc/math_exp.o \
    src/klibc/math_misc.o \
    src/klibc/math_pow.o \
    src/klibc/math_trigo.o \
    src/klibc/ctype.o \
    src/klibc/errno.o \
    src/klibc/stdlib.o \
    src/sys/utsname.o \
    src/klibc/libgcc.o \
    src/klibc/mm.o \
    src/klibc/memclr.o \
    src/klibc/getopt.o \
    src/klibc/getopt_long.o \
    src/klibc/wchar.o\
    src/klibc/wctype.o \
    src/klibc/_extern.o \
    src/klibc/sleep.o \
    src/klibc/sqrtf.o \
    src/klibc/sprintf.o \
    src/klibc/crtend.o \
    src/klibc/crtbegin.o \
    src/klibc/crti.o \
    src/klibc/crtn.o
        
KLIBCPP = src/klibc/cxx/new.o \
		  src/klibc/cxx/icxxabi.o \
		  src/klibc/cxx/cxxstd.o \
		  src/klibc/cxx/list.o \
		  src/klibc/cxx/iostream.o \
		  src/klibc/cxx/intrusive_list.o \
		  src/klibc/cxx/intrusive_slist.o \
		  src/klibc/cxx/slist.o \
		  src/IStream.o \
		  src/klibc/cxx/lock.o 

FS	  = src/fs.o \
		src/DeviceStream.o \
		src/devfs.o

DEV   = src/dev/Driver.o \
	    src/dev/DriverList.o \
	    src/dev/Device.o \
	    src/dev/serial_out.o \
	    src/dev/DeviceList.o \
	    src/dev/random.o \
	    src/dev/SysTimer.o \
	    src/dev/Framebuffer.o 
 
FB	  = src/Framebuffer/Buffer.o src/Framebuffer/GraphicDevice.o

HASH  = src/klibc/hash/md5.o \
 		src/klibc/hash/adler32.o \
 		src/klibc/hash/util.o \
 		src/klibc/hash/crc.o


PROMPT = " -> "
AR = @echo "   " $(PROMPT)  AR "    " $ && ar
CD = @echo  $(PROMPT) CD "        " && cd
LD = @echo "   " $(PROMPT) LIN "    " $ && $(TLD)
CC = @echo "   " $(PROMPT) GCC "   " $< && $(TCC)
CPP = @echo "   " $(PROMPT) GPP "   " $< && $(TCP)
AS = @echo "   " $(PROMPT) AS "   " $< && $(TAS)
RM = @echo "   " $(PROMPT) REM "   " $< && rm
CP = @echo "   " $(PROMPT)  CP && cp
OB = @echo "   " $(PROMPT) OB "   " $< && $(TOB)

SOURCES=$(OBJS) $(KLIBC) $(KLIBCPP) $(DEV) $(FS) $(AEBI) $(FB) $(HASH)

all: $(SOURCES) link 
.s.o:
	$(CC) $(CFLAGS) -std=gnu11 -c $< -o $@
.c.o:
	$(CC) $(CFLAGS) -std=gnu11 -c $< -o $@
.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< -o $@
link:
	$(LD) $(LDFLAGS) $(SOURCES)
	$(TOB) $(OBJGLAGS)
clean:
	$(RM) $(SOURCES) $(ELFNAME) $(KERNEL)


