cmd_arch/sh/kernel/cpu/sh4/entry.o := sh4-linux-gcc -Wp,-MD,arch/sh/kernel/cpu/sh4/.entry.o.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__ -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml -Wa,-isa=st40-300-up -ffreestanding    -c -o arch/sh/kernel/cpu/sh4/entry.o arch/sh/kernel/cpu/sh4/entry.S

deps_arch/sh/kernel/cpu/sh4/entry.o := \
  arch/sh/kernel/cpu/sh4/entry.S \
    $(wildcard include/config/gusa.h) \
    $(wildcard include/config/kgdb.h) \
    $(wildcard include/config/cpu/has/ptea.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/sh/standard/bios.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/sh/fpu.h) \
  include/linux/sys.h \
  include/linux/errno.h \
  include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/linkage.h \
  include/asm/linkage.h \
  include/asm/asm-offsets.h \
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
    $(wildcard include/config/cache/off.h) \
    $(wildcard include/config/cpu/sh4.h) \
    $(wildcard include/config/sh7705/cache/32kb.h) \
    $(wildcard include/config/x2tlb.h) \
    $(wildcard include/config/memory/start.h) \
    $(wildcard include/config/memory/size.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/32bit.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/vsyscall.h) \
  include/linux/const.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/out/of/line/pfn/to/page.h) \
  include/asm-generic/page.h \
  include/asm/unistd.h \
  include/asm/cpu/mmu_context.h \
    $(wildcard include/config/sh/store/queues.h) \
  include/asm/pgtable.h \
    $(wildcard include/config/cpu/sh3.h) \
  include/asm-generic/pgtable-nopmd.h \
  include/asm/entry-macros.S \

arch/sh/kernel/cpu/sh4/entry.o: $(deps_arch/sh/kernel/cpu/sh4/entry.o)

$(deps_arch/sh/kernel/cpu/sh4/entry.o):