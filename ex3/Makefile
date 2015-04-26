# Makefile to compile all the modules of exercise 3 TDT4258.

.PHONY:all
all:
	ptxdist images
	ptxdist test flash-all

.PHONY:game
game:
	ptxdist drop game compile
	ptxdist compile game


.PHONY:gameup
gameup:
	ptxdist targetinstall game
	ptxdist image root.romfs
	ptxdist test flash-rootfs

.PHONY:gameclean
gameclean:
	ptxdist clean game

.PHONY:pad
pad:
	ptxdist drop driver-gamepad prepare
	ptxdist go

.PHONY:padup
padup:
	ptxdist targetinstall driver-gamepad
	ptxdist image root.romfs
	ptxdist test flash-rootfs

.PHONY:padclean
padclean:
	ptxdist clean driver-gamepad


