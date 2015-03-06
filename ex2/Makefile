# Example Makefile
#
# Exercise 2, TDT4258

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 -Wall -fomit-frame-pointer -O1
LDFLAGS=-mcpu=cortex-m3 -mthumb -g -lgcc -lc -lcs3 -lcs3unhosted -lefm32gg -Llib
ASFLAGS=-mcpu=cortex-m3 -mthumb -g
LINKERSCRIPT=lib/efm32gg.ld

ex2.bin : ex2.elf
	${OBJCOPY} -O binary $< $@

ex2.elf : ex2.o timer.o dac.o gpio.o interrupt_handlers.o tones_play.o sounds.o pachelbel.o c_scale.o loser.o hit_wall.o winner.o mario_theme.o dr_wily.o
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY : upload
upload :
	-eACommander.sh -r --address 0x00000000 -f "ex2.bin" -r

.PHONY : clean
clean :
	-rm -rf *.o *.elf *.bin *.hex *~
