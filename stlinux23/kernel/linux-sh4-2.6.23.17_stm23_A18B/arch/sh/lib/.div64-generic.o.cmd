cmd_arch/sh/lib/div64-generic.o := sh4-linux-gcc -Wp,-MD,arch/sh/lib/.div64-generic.o.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -O2 -pipe -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml -Wa,-isa=st40-300-up -ffreestanding -fomit-frame-pointer -g  -fno-stack-protector -Wdeclaration-after-statement -Wno-pointer-sign    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(div64_generic)"  -D"KBUILD_MODNAME=KBUILD_STR(div64_generic)" -c -o arch/sh/lib/div64-generic.o arch/sh/lib/div64-generic.c

deps_arch/sh/lib/div64-generic.o := \
  arch/sh/lib/div64-generic.c \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbd.h) \
    $(wildcard include/config/lsf.h) \
    $(wildcard include/config/resources/64bit.h) \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/enable/must/check.h) \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/forced/inlining.h) \
  include/linux/compiler-gcc.h \
  include/asm/posix_types.h \
  include/asm/types.h \

arch/sh/lib/div64-generic.o: $(deps_arch/sh/lib/div64-generic.o)

$(deps_arch/sh/lib/div64-generic.o):
