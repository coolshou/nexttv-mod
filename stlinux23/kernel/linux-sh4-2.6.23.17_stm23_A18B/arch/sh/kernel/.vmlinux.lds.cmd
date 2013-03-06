cmd_arch/sh/kernel/vmlinux.lds := sh4-linux-gcc -E -Wp,-MD,arch/sh/kernel/.vmlinux.lds.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h  -traditional -P -C -Ush -D__ASSEMBLY__ -o arch/sh/kernel/vmlinux.lds arch/sh/kernel/vmlinux.lds.S

deps_arch/sh/kernel/vmlinux.lds := \
  arch/sh/kernel/vmlinux.lds.S \
    $(wildcard include/config/cpu/little/endian.h) \
    $(wildcard include/config/32bit.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/zero/page/offset.h) \
    $(wildcard include/config/memory/start.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/wireless/rt73/frmw.h) \
    $(wildcard include/config/blk/dev/initrd.h) \
  include/asm/thread_info.h \
    $(wildcard include/config/4kstacks.h) \
    $(wildcard include/config/page/size/4kb.h) \
    $(wildcard include/config/page/size/8kb.h) \
    $(wildcard include/config/page/size/64kb.h) \
    $(wildcard include/config/cpu/has/sr/rb.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  include/asm/page.h \
    $(wildcard include/config/hugetlb/page/size/64k.h) \
    $(wildcard include/config/hugetlb/page/size/256k.h) \
    $(wildcard include/config/hugetlb/page/size/1mb.h) \
    $(wildcard include/config/hugetlb/page/size/4mb.h) \
    $(wildcard include/config/hugetlb/page/size/64mb.h) \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/cache/off.h) \
    $(wildcard include/config/cpu/sh4.h) \
    $(wildcard include/config/sh7705/cache/32kb.h) \
    $(wildcard include/config/x2tlb.h) \
    $(wildcard include/config/memory/size.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/vsyscall.h) \
  include/linux/const.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/out/of/line/pfn/to/page.h) \
  include/asm-generic/page.h \
  include/asm/cache.h \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/acpi/hotplug/memory.h) \
  include/linux/compiler.h \
    $(wildcard include/config/enable/must/check.h) \
  include/asm/cpu/cache.h \
    $(wildcard include/config/cpu/sh4a.h) \
  include/asm-generic/vmlinux.lds.h \

arch/sh/kernel/vmlinux.lds: $(deps_arch/sh/kernel/vmlinux.lds)

$(deps_arch/sh/kernel/vmlinux.lds):
