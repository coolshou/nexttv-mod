cmd_arch/sh/kernel/debugtraps.o := sh4-linux-gcc -Wp,-MD,arch/sh/kernel/.debugtraps.o.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__ -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml -Wa,-isa=st40-300-up -ffreestanding    -c -o arch/sh/kernel/debugtraps.o arch/sh/kernel/debugtraps.S

deps_arch/sh/kernel/debugtraps.o := \
  arch/sh/kernel/debugtraps.S \
    $(wildcard include/config/kgdb.h) \
    $(wildcard include/config/sh/standard/bios.h) \
  include/linux/sys.h \
  include/linux/linkage.h \
  include/asm/linkage.h \

arch/sh/kernel/debugtraps.o: $(deps_arch/sh/kernel/debugtraps.o)

$(deps_arch/sh/kernel/debugtraps.o):