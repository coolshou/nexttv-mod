cmd_net/sunrpc/xprtsock.o := sh4-linux-gcc -Wp,-MD,net/sunrpc/.xprtsock.o.d  -nostdinc -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -O2 -pipe -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml -Wa,-isa=st40-300-up -ffreestanding -fomit-frame-pointer -g  -fno-stack-protector -Wdeclaration-after-statement -Wno-pointer-sign    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(xprtsock)"  -D"KBUILD_MODNAME=KBUILD_STR(sunrpc)" -c -o net/sunrpc/xprtsock.o net/sunrpc/xprtsock.c

deps_net/sunrpc/xprtsock.o := \
  net/sunrpc/xprtsock.c \
    $(wildcard include/config/debug/lock/alloc.h) \
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
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/debug/slab.h) \
  include/linux/gfp.h \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/highmem.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/preempt.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
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
  include/linux/linkage.h \
  include/asm/linkage.h \
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
    $(wildcard include/config/vsyscall.h) \
  include/linux/const.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/out/of/line/pfn/to/page.h) \
  include/asm-generic/page.h \
  include/asm/processor.h \
    $(wildcard include/config/cpu/subtype/xxx.h) \
    $(wildcard include/config/cpu/sh3.h) \
  include/asm/cache.h \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/acpi/hotplug/memory.h) \
  include/asm/cpu/cache.h \
  include/asm/cpu-features.h \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
  include/linux/prefetch.h \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/printk.h) \
  /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include/stdarg.h \
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
  include/linux/wait.h \
  include/asm/current.h \
  include/linux/cache.h \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/seqlock.h \
  include/linux/nodemask.h \
  include/linux/bitmap.h \
  include/linux/string.h \
  include/asm/string.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/linux/notifier.h \
  include/linux/errno.h \
  include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/rwsem-spinlock.h \
  include/linux/srcu.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
  include/linux/cpumask.h \
  include/linux/smp.h \
  include/asm/topology.h \
  include/asm-generic/topology.h \
  include/linux/slab_def.h \
  include/linux/kmalloc_sizes.h \
  include/linux/capability.h \
  include/linux/pagemap.h \
  include/linux/mm.h \
    $(wildcard include/config/sysctl.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/shmem.h) \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/debug/pagealloc.h) \
  include/linux/rbtree.h \
  include/linux/prio_tree.h \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  include/linux/backing-dev.h \
  include/linux/mm_types.h \
  include/asm/pgtable.h \
  include/asm-generic/pgtable-nopmd.h \
  include/asm-generic/pgtable-nopud.h \
  include/asm/addrspace.h \
  include/asm/cpu/addrspace.h \
  include/asm/fixmap.h \
  include/asm-generic/pgtable.h \
  include/linux/page-flags.h \
    $(wildcard include/config/s390.h) \
    $(wildcard include/config/swap.h) \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  include/linux/percpu.h \
  include/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/limits.h \
  include/linux/ioctl.h \
  include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/kdev_t.h \
  include/linux/dcache.h \
    $(wildcard include/config/profiling.h) \
  include/linux/rcupdate.h \
  include/linux/namei.h \
  include/linux/stat.h \
  include/asm/stat.h \
  include/linux/time.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
  include/linux/kref.h \
  include/linux/radix-tree.h \
  include/linux/pid.h \
  include/linux/sysctl.h \
  include/asm/semaphore.h \
    $(wildcard include/config/kptrace/sync.h) \
  include/linux/quota.h \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/nfs_fs_i.h \
  include/linux/nfs.h \
  include/linux/sunrpc/msg_prot.h \
  include/linux/fcntl.h \
  include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
    $(wildcard include/config/64bit.h) \
  include/linux/err.h \
  include/linux/highmem.h \
  include/linux/uaccess.h \
  include/asm/uaccess.h \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/detect/softlockup.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/fault/injection.h) \
  include/linux/auxvec.h \
  include/asm/auxvec.h \
  include/asm/param.h \
    $(wildcard include/config/sh/fast/hz.h) \
    $(wildcard include/config/hz.h) \
  include/linux/timex.h \
  include/asm/timex.h \
  include/linux/io.h \
    $(wildcard include/config/has/ioport.h) \
  include/asm/io.h \
    $(wildcard include/config/generic/iomap.h) \
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
  include/asm-generic/iomap.h \
  include/asm/io_generic.h \
  include/asm/cpu/timer.h \
    $(wildcard include/config/cpu/subtype/shx3.h) \
  include/linux/jiffies.h \
  include/linux/calc64.h \
  include/asm/div64.h \
  include/asm-generic/div64.h \
  include/asm/mmu.h \
  include/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/sem.h \
  include/linux/ipc.h \
  include/asm/ipcbuf.h \
  include/asm/sembuf.h \
  include/linux/signal.h \
  include/asm/signal.h \
  include/asm-generic/signal.h \
  include/asm/sigcontext.h \
  include/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/securebits.h \
  include/linux/fs_struct.h \
  include/linux/completion.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/futex.h \
    $(wildcard include/config/futex.h) \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/param.h \
  include/linux/resource.h \
  include/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/aio.h \
  include/linux/workqueue.h \
  include/linux/aio_abi.h \
  include/linux/uio.h \
  include/asm/cacheflush.h \
  include/asm/cpu/cacheflush.h \
  include/asm/kmap_types.h \
    $(wildcard include/config/debug/highmem.h) \
  include/linux/socket.h \
  include/asm/socket.h \
  include/asm/sockios.h \
  include/linux/sockios.h \
  include/linux/in.h \
  include/linux/net.h \
  include/linux/random.h \
  include/linux/udp.h \
  include/linux/skbuff.h \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/net/dma.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/netdevices/multiqueue.h) \
  include/linux/textsearch.h \
  include/linux/module.h \
    $(wildcard include/config/lkm/elf/hash.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/kgdb.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/kallsyms.h) \
  include/linux/kmod.h \
    $(wildcard include/config/kmod.h) \
  include/linux/elf.h \
  include/linux/elf-em.h \
  include/asm/elf.h \
  include/asm/user.h \
  include/linux/moduleparam.h \
  include/asm/local.h \
  include/asm-generic/local.h \
  include/linux/hardirq.h \
    $(wildcard include/config/preempt/bkl.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
  include/linux/smp_lock.h \
    $(wildcard include/config/lock/kernel.h) \
  include/asm/hardirq.h \
  include/linux/irq.h \
    $(wildcard include/config/irq/per/cpu.h) \
    $(wildcard include/config/irq/release/method.h) \
    $(wildcard include/config/generic/pending/irq.h) \
    $(wildcard include/config/irqbalance.h) \
    $(wildcard include/config/auto/irq/affinity.h) \
    $(wildcard include/config/generic/hardirqs/no//do/irq.h) \
  include/linux/irqreturn.h \
  include/asm/irq.h \
    $(wildcard include/config/cpu/has/intevt.h) \
  include/asm/irq_regs.h \
  include/asm-generic/irq_regs.h \
  include/asm/hw_irq.h \
  include/linux/irq_cpustat.h \
  include/asm/module.h \
    $(wildcard include/config/cpu/little/endian.h) \
    $(wildcard include/config/cpu/sh2.h) \
  include/net/checksum.h \
  include/asm/checksum.h \
  include/linux/in6.h \
  include/linux/dmaengine.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
  include/linux/ioport.h \
  include/linux/klist.h \
  include/linux/pm.h \
    $(wildcard include/config/suspend.h) \
    $(wildcard include/config/pm/sleep.h) \
  include/asm/device.h \
  include/asm-generic/device.h \
  include/linux/dma-mapping.h \
    $(wildcard include/config/has/dma.h) \
  include/asm/dma-mapping.h \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/sh/pcidma/noncoherent.h) \
  include/asm/scatterlist.h \
  include/net/inet_sock.h \
    $(wildcard include/config/ipv6.h) \
  include/linux/jhash.h \
  include/net/flow.h \
  include/net/sock.h \
    $(wildcard include/config/security/network.h) \
  include/linux/netdevice.h \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/tr.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/netpoll/trap.h) \
  include/linux/if.h \
  include/linux/hdlc/ioctl.h \
  include/linux/if_ether.h \
  include/linux/if_packet.h \
  include/linux/interrupt.h \
    $(wildcard include/config/generic/irq/probe.h) \
  include/linux/security.h \
    $(wildcard include/config/security/network/xfrm.h) \
  include/linux/binfmts.h \
  include/linux/shm.h \
  include/asm/shmparam.h \
  include/asm/shmbuf.h \
  include/linux/msg.h \
  include/asm/msgbuf.h \
  include/linux/key.h \
  include/linux/xfrm.h \
  include/linux/filter.h \
  include/net/dst.h \
    $(wildcard include/config/net/cls/route.h) \
    $(wildcard include/config/xfrm.h) \
  include/linux/rtnetlink.h \
  include/linux/netlink.h \
  include/linux/if_link.h \
  include/linux/if_addr.h \
  include/linux/neighbour.h \
  include/net/neighbour.h \
  include/linux/seq_file.h \
  include/net/rtnetlink.h \
  include/net/netlink.h \
  include/net/request_sock.h \
  include/linux/tcp.h \
    $(wildcard include/config/tcp/md5sig.h) \
  include/net/inet_connection_sock.h \
  include/linux/poll.h \
  include/asm/poll.h \
  include/asm-generic/poll.h \
  include/net/inet_timewait_sock.h \
  include/net/tcp_states.h \
  include/net/timewait_sock.h \
  include/linux/sunrpc/clnt.h \
  include/linux/sunrpc/sched.h \
  include/linux/sunrpc/types.h \
  include/linux/sunrpc/debug.h \
  include/linux/sunrpc/xdr.h \
  include/linux/scatterlist.h \
  include/linux/sunrpc/xprt.h \
  include/linux/sunrpc/auth.h \
  include/linux/sunrpc/stats.h \
  include/linux/proc_fs.h \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
  include/linux/magic.h \
  include/linux/sunrpc/timer.h \
  include/linux/file.h \
  include/net/udp.h \
  include/net/snmp.h \
  include/linux/snmp.h \
  include/net/ip.h \
    $(wildcard include/config/inet.h) \
  include/linux/ip.h \
  include/linux/ipv6.h \
    $(wildcard include/config/ipv6/privacy.h) \
    $(wildcard include/config/ipv6/router/pref.h) \
    $(wildcard include/config/ipv6/route/info.h) \
    $(wildcard include/config/ipv6/optimistic/dad.h) \
    $(wildcard include/config/ipv6/mip6.h) \
    $(wildcard include/config/ipv6/subtrees.h) \
  include/linux/icmpv6.h \
  include/net/tcp.h \
  include/linux/crypto.h \
    $(wildcard include/config/crypto.h) \
  include/net/inet_hashtables.h \
  include/net/route.h \
  include/net/inetpeer.h \
  include/linux/in_route.h \
  include/linux/route.h \
  include/net/tcp_ecn.h \
  include/net/inet_ecn.h \
  include/net/dsfield.h \

net/sunrpc/xprtsock.o: $(deps_net/sunrpc/xprtsock.o)

$(deps_net/sunrpc/xprtsock.o):