:
	ptxdist images
	ptxdist test flash-rootfs

game:
	ptxdist drop game compile
	ptxdist compile game
	ptxdist targetinstall game
	ptxdist image root.romfs
	ptxdist test flash-rootfs

gameclean:
	ptxdist clean game

gamepad:
	ptxdist images
	ptxdist test flash-rootfs


gamepadclean:
	ptxdist clean driver-gamepad


