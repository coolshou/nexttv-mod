cmd_arch/sh/kernel/cpu/sh4/sata-init.o := sh4-linux-gcc -Wp,-MD,arch/sh/kernel/cpu/sh4/.sata-init.o.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -O2 -pipe -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml -Wa,-isa=st40-300-up -ffreestanding -fomit-frame-pointer -g  -fno-stack-protector -Wdeclaration-after-statement -Wno-pointer-sign    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(sata_init)"  -D"KBUILD_MODNAME=KBUILD_STR(sata_init)" -c -o arch/sh/kernel/cpu/sh4/sata-init.o arch/sh/kernel/cpu/sh4/sata-init.c

deps_arch/sh/kernel/cpu/sh4/sata-init.o := \
  arch/sh/kernel/cpu/sh4/sata-init.c \
  include/linux/stm/soc.h \
    $(wildcard include/config/cpu/subtype/stx5197.h) \
    $(wildcard include/config/cpu/subtype/stx7105.h) \
    $(wildcard include/config/sh/st/synopsys/pci.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/threshold128.h) \
    $(wildcard include/config/threshold256.h) \
    $(wildcard include/config/cpu/subtype/stx7141.h) \
  include/linux/lirc.h \
  include/asm/types.h \
  include/linux/ioctl.h \
  include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/compiler.h \
    $(wildcard include/config/enable/must/check.h) \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/forced/inlining.h) \
  include/linux/compiler-gcc.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbd.h) \
    $(wildcard include/config/lsf.h) \
    $(wildcard include/config/resources/64bit.h) \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/asm/posix_types.h \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/acpi/hotplug/memory.h) \
  include/linux/delay.h \
  include/asm/delay.h \
  include/linux/stm/sysconf.h \
    $(wildcard include/config/cpu/subtype/stx7108.h) \

arch/sh/kernel/cpu/sh4/sata-init.o: $(deps_arch/sh/kernel/cpu/sh4/sata-init.o)

$(deps_arch/sh/kernel/cpu/sh4/sata-init.o):
