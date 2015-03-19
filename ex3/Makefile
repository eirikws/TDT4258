# Makefile to compile all the modules of exercise 3 TDT4258.

.PHONY:all
all:
	ptxdist images
	ptxdist test flash-rootfs

.PHONY:game
game:
	ptxdist drop game compile
	ptxdist compile game
	ptxdist targetinstall game
	ptxdist image root.romfs
	ptxdist test flash-rootfs

.PHONY:gameclean
gameclean:
	ptxdist clean game

.PHONY:gamepad
gamepad:
	ptxdist images
	ptxdist test flash-rootfs

.PHONY:gamepadclean
gamepadclean:
	ptxdist clean driver-gamepad


