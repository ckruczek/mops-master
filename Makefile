TARGET=system.elf
BIN=system.bin
LINKFILE=link.ld

CC=arm-none-linux-gnueabi-gcc
AS=arm-none-linux-gnueabi-as
LD=arm-none-linux-gnueabi-ld
OBJCOPY=arm-none-linux-gnueabi-objcopy

CCFLAGS=-O0 -c -mcpu=arm926ej-s -g -Iinclude/devices -Iinclude/system
ASFLAGS=-mcpu=arm926ej-s -g
LDFLAGS=-T
OBJCOPYFLAGS=-O binary

RM=rm -f $(1)

all: $(TARGET)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(TARGET) $(BIN)

rebuild: clean all

clean:
	$(call RM, *.o )
	$(call RM, startup/*.o )
	$(call RM, core/devices/*.o )

OBJS=startup/arm_irq.o  \
	core/devices/p_vic.o \
	core/devices/vic.o core/devices/timer.o core/devices/p_timer.o\
	core/devices/uart.o core/devices/p_uart.o \
	startup/vector_mapping.o startup/arm_init.o main.o  startup/startup.o startup/initstacks.o

HEADERS=include/devices/timer.h include/devices/uart.h \
		include/system/arm_init.h include/system/arm_irq.h \
		include/system/vic.h

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(LINKFILE) -o $(TARGET) $(OBJS) 

main.o:	main.c $(HEADERS)
	$(CC) $(CCFLAGS) main.c -o main.o
startup/vector_mapping.o: startup/vector_mapping.c $(HEADERS)
	$(CC) $(CCFLAGS) startup/vector_mapping.c -o startup/vector_mapping.o
startup/arm_init.o: startup/arm_init.c $(HEADERS)
	$(CC) $(CCFLAGS) startup/arm_init.c -o startup/arm_init.o
#versatile/secondary_vic.o: versatile/secondary_vic.c 
#	$(CC) $(CCFLAGS) versatile/secondary_vic.c -o versatile/secondary_vic.o
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
#versatile/periphs/p_vic2.o: versatile/periphs/p_vic2.c 
#	$(CC) $(CCFLAGS) versatile/periphs/p_vic2.c -o versatile/periphs/p_vic2.o

# ASSEMBLER STUFF GOES HERE
startup/startup.o: startup/startup.s
	$(AS) $(ASFLAGS) startup/startup.s -o startup/startup.o
startup/arm_irq.o: startup/arm_irq.s 
	$(AS) $(ASFLAGS) startup/arm_irq.s -o startup/arm_irq.o
startup/initstacks.o: startup/initstacks.s
	$(AS) $(ASFLAGS) startup/initstacks.s -o startup/initstacks.o
