BUILD_DIR = ./build
ENTRY_POINT = 0xc0001500
AS = nasm
CC = gcc
LD = ld
LIB =  -m32 -I ./lib -m32 -I ./lib/kernel -m32 -I ./lib/usr -m32 -I ./kernel -m32 -I ./device -m32 -I ./thread -m32 -I ./userprog -I ./lib/user
ASFLAGS = -f elf
CFLAGS = -Wall -m32 -fno-stack-protector $(LIB) -c -fno-builtin -W -Wstrict-prototypes -Wmissing-prototypes
LDFLAGS = -m elf_i386 -Ttext $(ENTRY_POINT) -e main 
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/init.o $(BUILD_DIR)/interrupt.o \
	   $(BUILD_DIR)/timer.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/print.o \
	   $(BUILD_DIR)/debug.o $(BUILD_DIR)/string.o $(BUILD_DIR)/bitmap.o \
	   $(BUILD_DIR)/memory.o $(BUILD_DIR)/thread.o $(BUILD_DIR)/list.o $(BUILD_DIR)/switch.o\
	   $(BUILD_DIR)/sync.o $(BUILD_DIR)/console.o $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/ioqueue.o\
	   $(BUILD_DIR)/tss.o $(BUILD_DIR)/process.o $(BUILD_DIR)/syscall.o $(BUILD_DIR)/syscall-init.o\
	   $(BUILD_DIR)/stdio.o $(BUILD_DIR)/stdio-kernel.o $(BUILD_DIR)/ide.o		

########## C Code Compile Part #############
$(BUILD_DIR)/main.o: kernel/main.c lib/kernel/print.h \
			lib/stdint.h kernel/init.h kernel/debug.h
			$(CC) $(CFLAGS) -o $@ $< 

$(BUILD_DIR)/init.o: kernel/init.c kernel/init.h lib/kernel/print.h \
			lib/stdint.h kernel/interrupt.h device/timer.h thread/thread.h
			$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/interrupt.o: kernel/interrupt.c kernel/interrupt.h \
			lib/stdint.h kernel/global.h lib/kernel/io.h lib/kernel/print.h
			$(CC) $(CFLAGS) -o $@ $< 

$(BUILD_DIR)/timer.o: device/timer.c device/timer.h lib/stdint.h\
			lib/kernel/io.h lib/kernel/print.h kernel/debug.h
			$(CC) $(CFLAGS) -o $@ $< 

$(BUILD_DIR)/debug.o: kernel/debug.c kernel/debug.h \
			lib/kernel/print.h lib/stdint.h kernel/interrupt.h lib/string.h
			$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/string.o: lib/string.c lib/string.h\
			kernel/global.h kernel/debug.h
			$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/bitmap.o: lib/kernel/bitmap.c lib/kernel/bitmap.h\
			kernel/global.h kernel/debug.h lib/stdint.h lib/string.c
			$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/memory.o: kernel/memory.c kernel/memory.h\
			kernel/debug.h lib/stdint.h lib/kernel/bitmap.h lib/kernel/print.h
			$(CC) $(CFLAGS) -o $@ $<



$(BUILD_DIR)/thread.o: thread/thread.c thread/thread.h \
	lib/stdint.h lib/string.h kernel/global.h kernel/memory.h \
	kernel/debug.h kernel/interrupt.h lib/kernel/print.h
	$(CC) $(CFLAGS) $< -o $@
	
$(BUILD_DIR)/list.o: lib/kernel/list.c lib/kernel/list.h \
	kernel/interrupt.h lib/stdint.h kernel/debug.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/sync.o: thread/sync.c thread/sync.h \
	thread/thread.h lib/stdint.h kernel/debug.h lib/kernel/list.h \
	kernel/interrupt.h kernel/debug.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/console.o: device/console.c device/console.h \
	lib/stdint.h lib/kernel/print.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/keyboard.o: device/keyboard.c device/keyboard.h \
	lib/kernel/io.h lib/kernel/print.h kernel/debug.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/ioqueue.o: device/ioqueue.c device/ioqueue.h \
	lib/kernel/io.h lib/kernel/print.h kernel/debug.h lib/stdint.h\
	kernel/interrupt.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/tss.o: userprog/tss.c userprog/tss.h \
	kernel/global.h lib/kernel/print.h lib/string.h lib/stdint.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/process.o: userprog/process.c userprog/process.h \
	kernel/global.h lib/kernel/print.h lib/string.h lib/stdint.h\
	kernel/memory.h thread/thread.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/syscall.o: lib/user/syscall.c lib/user/syscall.h 
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/syscall-init.o: userprog/syscall-init.c userprog/syscall-init.h 
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/stdio.o: lib/stdio.c lib/stdio.h 
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/stdio-kernel.o: kernel/stdio-kernel.c kernel/stdio-kernel.h 
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/ide.o: device/ide.c device/ide.h 
	$(CC) $(CFLAGS) $< -o $@

######### ASM Code Compile Part #############
$(BUILD_DIR)/kernel.o: kernel/kernel.S
		$(AS) $(ASFLAGS) -o $@  $< 

$(BUILD_DIR)/print.o: lib/kernel/print.S
		$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/switch.o: thread/switch.S
		$(AS) $(ASFLAGS) -o $@ $<
		
######### LD All Files ##############
$(BUILD_DIR)/kernel.bin: $(OBJS)
			$(LD) $(LDFLAGS) $^ -o $@ 


.PHONY :mk_dir os clean all 

mk_dir:
		if [[! -d $(BUILD_DIR) ]];then mkdir $(BUILD_DIR);fi 

os:
		dd if=$(BUILD_DIR)/kernel.bin \
			of=../geniusos.img bs=512 count=200 seek=6 conv=notrunc

clean:
		cd $(BUILD_DIR) && rm -f ./*

build: $(BUILD_DIR)/kernel.bin

all: mk_dir build os