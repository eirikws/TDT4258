game:
	ptxdist clean game
	ptxdist compile game
	ptxdist targetinstall game
	ptxdist image root.romfs
	ptxdist test flash-rootfs

gameclean:
	ptxdist clean game

gamepad:
	ptxdist clean driver-gamepad
	ptxdist compile driver-gamepad
	ptxdist targetinstall game
	ptxdist image root.romfs
	ptxdist test flash-romfs

gamepadclean:
	ptxdist clean driver-gamepad
