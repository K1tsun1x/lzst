CC=$(TARGET)-gcc
LD=$(CC)
AS=nasm

DIR_BUILD=.
DIR_STAGE_FIRST=../stage_first
DIR_STAGE_SECOND=../stage_second
DIR_STAGE_THIRD=../stage_third
DIR_STAGE_FOURTH=../stage_fourth

RESULT_STAGE_FIRST=$(DIR_BUILD)/stage_first.bin
RESULT_STAGE_SECOND=$(DIR_BUILD)/stage_second.bin
RESULT_STAGE_THIRD=$(DIR_BUILD)/stage_third.bin
RESULT_STAGE_FOURTH=$(DIR_BUILD)/stage_fourth.bin
RESULT=$(DIR_BUILD)/loader_bios.bin

SRC_C_THIRD_STAGE=$(shell find $(DIR_STAGE_THIRD) -name *.c)
SRC_ASM_THIRD_STAGE=$(shell find $(DIR_STAGE_THIRD) -name *.asm)
OBJ_C_THIRD_STAGE=$(patsubst %.c, %.lb3.c.o, $(SRC_C_THIRD_STAGE))
OBJ_ASM_THIRD_STAGE=$(patsubst %.asm, %.lb3.asm.o, $(SRC_ASM_THIRD_STAGE))

SRC_C_FOURTH_STAGE=$(shell find $(DIR_STAGE_FOURTH) -name *.c)
SRC_ASM_FOURTH_STAGE=$(shell find $(DIR_STAGE_FOURTH) -name *.asm)
OBJ_C_FOURTH_STAGE=$(patsubst %.c, %.lb4.c.o, $(SRC_C_FOURTH_STAGE))
OBJ_ASM_FOURTH_STAGE=$(patsubst %.asm, %.lb4.asm.o, $(SRC_ASM_FOURTH_STAGE))

FLAGS_CC_THIRD_STAGE=-Wall -Wextra -ffreestanding -O0 -m16 -std=c17 -I $(DIR_STAGE_THIRD)/include
FLAGS_LD_THIRD_STAGE=-Wall -Wextra -ffreestanding -O0 -m16 -nostdlib -T $(DIR_STAGE_THIRD)/stage_third.ld -lgcc

FLAGS_CC_FOURTH_STAGE=-Wall -Wextra -ffreestanding -O0 -m32 -std=c17 -I $(DIR_STAGE_FOURTH)/include
FLAGS_LD_FOURTH_STAGE=-Wall -Wextra -ffreestanding -O0 -m32 -nostdlib -T $(DIR_STAGE_FOURTH)/stage_fourth.ld -lgcc

all:	build run clean

build:	build-stage-fourth build-stage-third build-stage-second build-stage-first
	cat $(RESULT_STAGE_FIRST) $(RESULT_STAGE_SECOND) $(RESULT_STAGE_THIRD) $(RESULT_STAGE_FOURTH) > $(RESULT)

build-stage-first:
	$(AS) -fbin $(DIR_STAGE_FIRST)/stage_first.asm -o $(RESULT_STAGE_FIRST)

build-stage-second:
	$(AS) -fbin $(DIR_STAGE_SECOND)/stage_second.asm -o $(RESULT_STAGE_SECOND)

build-stage-third:
ifneq ($(OBJ_C_THIRD_STAGE),)
	$(MAKE) $(OBJ_C_THIRD_STAGE)
endif
ifneq ($(OBJ_ASM_THIRD_STAGE),)
	$(MAKE) $(OBJ_ASM_THIRD_STAGE)
endif
	$(LD) $(OBJ_C_THIRD_STAGE) $(OBJ_ASM_THIRD_STAGE) $(FLAGS_LD_THIRD_STAGE) -o $(RESULT_STAGE_THIRD)

	size=$$(wc -c < $(RESULT_STAGE_THIRD)) ; \
	neededSize=$$(((($$size + 511) & ~511))) ; \
	truncate -s $$neededSize $(RESULT_STAGE_THIRD) ; \
	numSectors=$$((($$neededSize / 512))) ; \
	printf "%08x" $$numSectors | sed 's/\(..\)\(..\)\(..\)\(..\)/\4\3\2\1/' | xxd -r -p | dd of=$(RESULT_STAGE_THIRD) bs=1 seek=4 conv=notrunc

build-stage-fourth:
ifneq ($(OBJ_C_FOURTH_STAGE),)
	$(MAKE) $(OBJ_C_FOURTH_STAGE)
endif
ifneq ($(OBJ_ASM_FOURTH_STAGE),)
	$(MAKE) $(OBJ_ASM_FOURTH_STAGE)
endif
	$(LD) $(OBJ_C_FOURTH_STAGE) $(OBJ_ASM_FOURTH_STAGE) $(FLAGS_LD_FOURTH_STAGE) -o $(RESULT_STAGE_FOURTH)

	size=$$(wc -c < $(RESULT_STAGE_FOURTH)) ; \
	neededSize=$$(((($$size + 511) & ~511))) ; \
	truncate -s $$neededSize $(RESULT_STAGE_FOURTH) ; \
	numSectors=$$((($$neededSize / 512))) ; \
	printf "%08x" $$numSectors | sed 's/\(..\)\(..\)\(..\)\(..\)/\4\3\2\1/' | xxd -r -p | dd of=$(RESULT_STAGE_FOURTH) bs=1 seek=8 conv=notrunc

%.lb3.c.o:		%.c
	$(CC) -c $< $(FLAGS_CC_THIRD_STAGE) -o $@

%.lb3.asm.o:	%.asm
	$(AS) -felf $< -o $@

%.lb4.c.o:		%.c
	$(CC) -c $< $(FLAGS_CC_FOURTH_STAGE) -o $@

%.lb4.asm.o:	%.asm
	$(AS) -felf $< -o $@

clean:
	rm -f $(RESULT_STAGE_FOURTH) \
		$(RESULT_STAGE_THIRD) \
		$(RESULT_STAGE_SECOND) \
		$(RESULT_STAGE_FIRST) \
		$(OBJ_ASM_FOURTH_STAGE) \
		$(OBJ_C_FOURTH_STAGE) \
		$(OBJ_ASM_THIRD_STAGE) \
		$(OBJ_C_THIRD_STAGE)

run:
	qemu-system-x86_64 -monitor stdio -m 4G -enable-kvm -cpu qemu64,+sse4.2,+avx -drive format=raw,file=$(RESULT) -D $(DIR_BUILD)/debug.txt -d cpu_reset,int
#	qemu-system-i386 -monitor stdio -m 4G -enable-kvm -drive format=raw,file=$(RESULT) -D $(DIR_BUILD)/debug.txt -d cpu_reset