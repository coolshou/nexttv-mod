cmd_.tmp_vmlinux1 := sh4-linux-ld  -EL -e _stext --defsym jiffies=jiffies_64 --build-id -o .tmp_vmlinux1 -T arch/sh/kernel/vmlinux.lds arch/sh/kernel/head.o arch/sh/kernel/init_task.o  init/built-in.o --start-group  usr/built-in.o  arch/sh/kernel/built-in.o  arch/sh/mm/built-in.o  arch/sh/boards/st/pdk7105/built-in.o  kernel/built-in.o  mm/built-in.o  fs/built-in.o  ipc/built-in.o  security/built-in.o  crypto/built-in.o  block/built-in.o  ltt/built-in.o  arch/sh/lib/lib.a  lib/lib.a /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/m4-nofpu/libgcc.a  arch/sh/lib/built-in.o  lib/built-in.o /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/m4-nofpu/libgcc.a  drivers/built-in.o  sound/built-in.o  arch/sh/drivers/built-in.o  net/built-in.o --end-group 
