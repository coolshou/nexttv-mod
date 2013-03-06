cmd_kernel/time/jiffies.o := sh4-linux-gcc -Wp,-MD,kernel/time/.jiffies.o.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -O2 -pipe -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml -Wa,-isa=st40-300-up -ffreestanding -fomit-frame-pointer -g  -fno-stack-protector -Wdeclaration-after-statement -Wno-pointer-sign    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(jiffies)"  -D"KBUILD_MODNAME=KBUILD_STR(jiffies)" -c -o kernel/time/jiffies.o kernel/time/jiffies.c

deps_kernel/time/jiffies.o := \
  kernel/time/jiffies.c \
  include/linux/clocksource.h \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/generic/time/vsyscall.h) \
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
  include/linux/timex.h \
    $(wildcard include/config/no/hz.h) \
  include/linux/time.h \
  include/linux/cache.h \
    $(wildcard include/config/smp.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/numa.h) \
  /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include/stdarg.h \
  include/linux/linkage.h \
  include/asm/linkage.h \
  include/linux/bitops.h \
  include/asm/bitops.h \
    $(wildcard include/config/sh/grb.h) \
  include/asm/system.h \
    $(wildcard include/config/cpu/sh4a.h) \
    $(wildcard include/config/ltt.h) \
    $(wildcard include/config/cpu/sh2a.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
    $(wildcard include/config/x86.h) \
  include/asm/irqflags.h \
    $(wildcard include/config/cpu/has/sr/rb.h) \
  include/asm/ptrace.h \
    $(wildcard include/config/sh/dsp.h) \
  include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/byteorder/swab.h \
  include/linux/byteorder/generic.h \
  include/asm/bitops-irq.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/find.h \
  include/asm-generic/bitops/ffs.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/ext2-non-atomic.h \
  include/asm-generic/bitops/le.h \
  include/asm-generic/bitops/ext2-atomic.h \
  include/asm-generic/bitops/minix.h \
  include/asm-generic/bitops/fls.h \
  include/asm-generic/bitops/fls64.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/marker.h \
    $(wildcard include/config/markers.h) \
  include/linux/immediate.h \
    $(wildcard include/config/immediate.h) \
  include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
  include/asm/cache.h \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/acpi/hotplug/memory.h) \
  include/asm/cpu/cache.h \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
  include/asm/thread_info.h \
    $(wildcard include/config/4kstacks.h) \
    $(wildcard include/config/page/size/4kb.h) \
    $(wildcard include/config/page/size/8kb.h) \
    $(wildcard include/config/page/size/64kb.h) \
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
  include/asm/processor.h \
    $(wildcard include/config/cpu/subtype/xxx.h) \
    $(wildcard include/config/cpu/sh3.h) \
  include/asm/cpu-features.h \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
  include/linux/prefetch.h \
  include/linux/stringify.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_up.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/prove/locking.h) \
  include/linux/spinlock_up.h \
  include/linux/spinlock_api_up.h \
  include/asm/atomic.h \
  include/asm/atomic-irq.h \
  include/asm-generic/atomic.h \
  include/asm/param.h \
    $(wildcard include/config/sh/fast/hz.h) \
    $(wildcard include/config/hz.h) \
  include/asm/timex.h \
  include/linux/io.h \
    $(wildcard include/config/has/ioport.h) \
  include/asm/io.h \
    $(wildcard include/config/generic/iomap.h) \
  include/asm/addrspace.h \
  include/asm/cpu/addrspace.h \
  include/asm/machvec.h \
  include/asm/machtypes.h \
    $(wildcard include/config/sh/solution/engine.h) \
    $(wildcard include/config/sh/7722/solution/engine.h) \
    $(wildcard include/config/sh/7343/solution/engine.h) \
    $(wildcard include/config/sh/7206/solution/engine.h) \
    $(wildcard include/config/sh/7619/solution/engine.h) \
    $(wildcard include/config/sh/7751/solution/engine.h) \
    $(wildcard include/config/sh/7780/solution/engine.h) \
    $(wildcard include/config/sh/7751/systemh.h) \
    $(wildcard include/config/sh/hp6xx.h) \
    $(wildcard include/config/hd64461.h) \
    $(wildcard include/config/hd64465.h) \
    $(wildcard include/config/sh/dreamcast.h) \
    $(wildcard include/config/sh/mpc1211.h) \
    $(wildcard include/config/sh/secureedge5410.h) \
    $(wildcard include/config/sh/hs7751rvoip.h) \
    $(wildcard include/config/sh/rts7751r2d.h) \
    $(wildcard include/config/sh/edosk7705.h) \
    $(wildcard include/config/sh/sh4202/microdev.h) \
    $(wildcard include/config/sh/sh03.h) \
    $(wildcard include/config/sh/landisk.h) \
    $(wildcard include/config/sh/r7780rp.h) \
    $(wildcard include/config/sh/r7780mp.h) \
    $(wildcard include/config/sh/r7785rp.h) \
    $(wildcard include/config/sh/titan.h) \
    $(wildcard include/config/sh/shmin.h) \
    $(wildcard include/config/sh/7710voipgw.h) \
    $(wildcard include/config/sh/lbox/re2.h) \
  include/asm/pgtable.h \
  include/asm-generic/pgtable-nopmd.h \
  include/asm-generic/pgtable-nopud.h \
  include/asm/fixmap.h \
    $(wildcard include/config/highmem.h) \
  include/asm-generic/pgtable.h \
  include/asm-generic/iomap.h \
  include/asm/io_generic.h \
  include/asm/cpu/timer.h \
    $(wildcard include/config/cpu/subtype/shx3.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/jiffies.h \
  include/linux/calc64.h \
  include/asm/div64.h \
  include/asm-generic/div64.h \

kernel/time/jiffies.o: $(deps_kernel/time/jiffies.o)

$(deps_kernel/time/jiffies.o):
