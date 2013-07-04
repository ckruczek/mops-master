TARGET=mops.elf
BIN=mops.bin
LINKFILE=link.ld

KLAUSNAME=klaus
CC=arm-none-linux-gnueabi-gcc
AS=arm-none-linux-gnueabi-as
LD=arm-none-linux-gnueabi-ld
OBJCOPY=arm-none-linux-gnueabi-objcopy
RAMDISK=./ramdiskMaker.o $(KLAUSNAME).bin

CCFLAGS=-c -mcpu=arm926ej-s -g -Iinclude/devices -Iinclude/system -I.
CCLINKFLAGS=-efunc -nostdlib -nodefaultlibs
ASFLAGS=-mcpu=arm926ej-s -g
LDFLAGS=-T
OBJCOPYFLAGS=-O binary -S

RM=rm -f $(1)

all: $(TARGET)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(TARGET) $(BIN)


rebuild: clean all KLAUS

###### Klaus stuff #####
KLAUSFILES=$(KLAUSNAME).o $(KLAUSNAME).bin

KLAUS:$(KLAUSFILES)
	$(call RAMDISK)

$(KLAUSNAME).o: $(KLAUSNAME).c 
	$(CC) $(CCFLAGS) $(CCLINKFLAGS) $(KLAUSNAME).c -o $(KLAUSNAME).o	
$(KLAUSNAME).bin: $(KLAUSNAME).o
	$(OBJCOPY) $(OBJCOPYFLAGS) $(KLAUSNAME).o $(KLAUSNAME).bin
###### Klaus Stuff #####

clean:
	$(call RM, startup/*.o )
	$(call RM, core/*.o )
	$(call RM, core/syscalls/*.o)
	$(call RM, core/devices/*.o )
	$(call RM, core/scheduler/*.o )
OBJS=ramdisk.o startup/arm_irq.o  \
	core/mops_create_thread.o \
	core/devices/p_vic.o \
	core/devices/vic.o core/devices/timer.o core/devices/p_timer.o\
	core/devices/uart.o core/devices/p_uart.o \
	core/scheduler/scheduler.o \
	startup/vector_mapping.o startup/arm_init.o main.o \
	startup/startup.o startup/initstacks.o  core/scheduler/thread.o \
	core/syscalls/syscalls.o core/mops_loader.o

HEADERS=include/devices/timer.h include/devices/uart.h \
		include/system/arm_init.h include/system/arm_irq.h \
		include/system/vic.h include/system/scheduler.h \
		include/system/syscalls.h include/system/thread.h \
		ramdisk.h include/system/mops_loader.h

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(LINKFILE) -o $(TARGET) $(OBJS) 

ramdisk.o: ramdisk.c $(HEADERS)
	$(CC) $(CCFLAGS) ramdisk.c -o ramdisk.o
main.o:	main.c $(HEADERS)
	$(CC) $(CCFLAGS) main.c -o main.o
startup/vector_mapping.o: startup/vector_mapping.c $(HEADERS)
	$(CC) $(CCFLAGS) startup/vector_mapping.c -o startup/vector_mapping.o
startup/arm_init.o: startup/arm_init.c $(HEADERS)
	$(CC) $(CCFLAGS) startup/arm_init.c -o startup/arm_init.o
core/devices/vic.o: core/devices/vic.c $(HEADERS)
	$(CC) $(CCFLAGS) core/devices/vic.c -o core/devices/vic.o
core/devices/timer.o: core/devices/timer.c $(HEADERS)
	$(CC) $(CCFLAGS) core/devices/timer.c -o core/devices/timer.o
core/devices/uart.o: core/devices/uart.c $(HEADERS)
	$(CC) $(CCFLAGS) core/devices/uart.c -o core/devices/uart.o
core/devices/p_uart.o: core/devices/p_uart.c $(HEADERS)
	$(CC) $(CCFLAGS) core/devices/p_uart.c -o core/devices/p_uart.o
core/devices/p_vic.o: core/devices/p_vic.c $(HEADERS)
	$(CC) $(CCFLAGS) core/devices/p_vic.c -o core/devices/p_vic.o
core/devices/p_timer.o: core/devices/p_timer.c $(HEADERS)
	$(CC) $(CCFLAGS) core/devices/p_timer.c -o core/devices/p_timer.o
core/scheduler/scheduler.o: core/scheduler/scheduler.c $(HEADERS)
	$(CC) $(CCFLAGS) core/scheduler/scheduler.c -o core/scheduler/scheduler.o
core/syscalls/syscalls.o: core/syscalls/syscalls.c $(HEADERS)
	$(CC) $(CCFLAGS) core/syscalls/syscalls.c -o core/syscalls/syscalls.o
core/scheduler/thread.o: core/scheduler/thread.c $(HEADERS)
	$(CC) $(CCFLAGS) core/scheduler/thread.c -o core/scheduler/thread.o
core/mops_loader.o: core/mops_loader.c $(HEADERS)
	$(CC) $(CCFLAGS) core/mops_loader.c -o core/mops_loader.o
# ASSEMBLER STUFF GOES HERE
startup/startup.o: startup/startup.s
	$(AS) $(ASFLAGS) startup/startup.s -o startup/startup.o
startup/arm_irq.o: startup/arm_irq.s 
	$(AS) $(ASFLAGS) startup/arm_irq.s -o startup/arm_irq.o
startup/initstacks.o: startup/initstacks.s
	$(AS) $(ASFLAGS) startup/initstacks.s -o startup/initstacks.o
core/mops_change_proc.o: core/mops_change_proc.s
	$(AS) $(ASFLAGS) core/mops_change_proc.s -o core/mops_change_proc.o
