cmd_arch/sh/lib/checksum.o := sh4-linux-gcc -Wp,-MD,arch/sh/lib/.checksum.o.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__ -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml -Wa,-isa=st40-300-up -ffreestanding    -c -o arch/sh/lib/checksum.o arch/sh/lib/checksum.S

deps_arch/sh/lib/checksum.o := \
  arch/sh/lib/checksum.S \
  include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/linkage.h \
  include/asm/linkage.h \

arch/sh/lib/checksum.o: $(deps_arch/sh/lib/checksum.o)

$(deps_arch/sh/lib/checksum.o):
