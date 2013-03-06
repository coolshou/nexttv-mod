	.file	"asm-offsets.c"
	.text
	.little
! GNU C (GCC) version 4.7.2 20121106 (STMicroelectronics/Linux Base 4.7.2-113) (sh4-linux)
!	compiled by GNU C version 3.4.6 20060404 (Red Hat 3.4.6-11), GMP version 5.0.2, MPFR version 3.1.0, MPC version 0.9
! GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
! 傳遞的選項： -nostdinc -I include -imultilib m4-nofpu -D __KERNEL__
! -D KBUILD_STR(s)=#s -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
! -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
! -isystem /opt/STM/STLinux-2.4/devkit/sh4/lib/gcc/sh4-linux/4.7.2/include
! -include include/linux/autoconf.h -MD arch/sh/kernel/.asm-offsets.s.d
! arch/sh/kernel/asm-offsets.c -m4 -m4-nofpu -m4-300 -m4-300-nofpu -ml
! -auxbase-strip arch/sh/kernel/asm-offsets.s -g -O2 -Wall -Wundef
! -Wstrict-prototypes -Wno-trigraphs -Werror=implicit-function-declaration
! -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-aliasing
! -fno-common -ffreestanding -fomit-frame-pointer -fno-stack-protector
! -fverbose-asm
! 啟用的選項： -fauto-inc-dec -fbranch-count-reg
! -fbranch-target-load-optimize -fcaller-saves -fcombine-stack-adjustments
! -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
! -fcse-sincos -fdebug-types-section -fdefer-pop -fdelayed-branch
! -fdelete-null-pointer-checks -fdevirtualize -fdwarf2-cfi-asm
! -fearly-inlining -feliminate-unused-debug-types -fexpensive-optimizations
! -fforward-propagate -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime
! -fguess-branch-probability -fident -fif-conversion -fif-conversion2
! -findirect-inlining -finline -finline-atomics
! -finline-functions-called-once -finline-small-functions -fipa-cp
! -fipa-profile -fipa-pure-const -fipa-reference -fipa-sra
! -fira-share-save-slots -fira-share-spill-slots -fivopts
! -fkeep-static-consts -fleading-underscore -fmath-errno -fmerge-constants
! -fmerge-debug-strings -fmove-loop-invariants -fomit-frame-pointer
! -foptimize-register-move -foptimize-sibling-calls -foptimize-strlen
! -fpartial-inlining -fpeephole -fpeephole2 -fprefetch-loop-arrays
! -freg-struct-return -fregmove -freorder-blocks -freorder-functions
! -frerun-cse-after-loop -fsched-critical-path-heuristic
! -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
! -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
! -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-insns
! -fschedule-insns2 -fshow-column -fshrink-wrap -fsigned-zeros
! -fsplit-ivs-in-unroller -fsplit-wide-types -fstrict-overflow
! -fstrict-volatile-bitfields -fthread-jumps -ftoplevel-reorder
! -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce -ftree-ccp
! -ftree-ch -ftree-copy-prop -ftree-copyrename -ftree-dce
! -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
! -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
! -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
! -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink
! -ftree-slp-vectorize -ftree-sra -ftree-switch-conversion
! -ftree-tail-merge -ftree-ter -ftree-vect-loop-version -ftree-vrp
! -funit-at-a-time -fvar-tracking -fvar-tracking-assignments -fverbose-asm
! -fzero-initialized-in-bss -maccumulate-outgoing-args -mglibc -ml
! -msoft-atomic -musermode

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup,"ax",@progbits
	.align 1
	.align 2
	.global	main
	.type	main, @function
main:
.LFB393:
	.file 1 "arch/sh/kernel/asm-offsets.c"
	.loc 1 22 0
	.cfi_startproc
	.loc 1 24 0
#APP
! 24 "arch/sh/kernel/asm-offsets.c" 1
	
->TI_TASK #0 offsetof(struct thread_info, task)	!
! 0 "" 2
	.loc 1 25 0
! 25 "arch/sh/kernel/asm-offsets.c" 1
	
->TI_EXEC_DOMAIN #4 offsetof(struct thread_info, exec_domain)	!
! 0 "" 2
	.loc 1 26 0
! 26 "arch/sh/kernel/asm-offsets.c" 1
	
->TI_FLAGS #8 offsetof(struct thread_info, flags)	!
! 0 "" 2
	.loc 1 27 0
! 27 "arch/sh/kernel/asm-offsets.c" 1
	
->TI_CPU #12 offsetof(struct thread_info, cpu)	!
! 0 "" 2
	.loc 1 28 0
! 28 "arch/sh/kernel/asm-offsets.c" 1
	
->TI_PRE_COUNT #16 offsetof(struct thread_info, preempt_count)	!
! 0 "" 2
	.loc 1 29 0
! 29 "arch/sh/kernel/asm-offsets.c" 1
	
->TI_RESTART_BLOCK #24 offsetof(struct thread_info, restart_block)	!
! 0 "" 2
	.loc 1 32 0
#NO_APP
	rts	
	mov	#0,r0	!,
	.cfi_endproc
.LFE393:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "include/asm/posix_types.h"
	.file 3 "include/linux/types.h"
	.file 4 "include/linux/list.h"
	.file 5 "include/linux/spinlock_types_up.h"
	.file 6 "include/linux/spinlock_types.h"
	.file 7 "include/asm/atomic.h"
	.file 8 "include/asm-generic/atomic.h"
	.file 9 "include/linux/wait.h"
	.file 10 "include/linux/mmzone.h"
	.file 11 "include/linux/mm_types.h"
	.file 12 "include/linux/slab_def.h"
	.file 13 "include/linux/vmstat.h"
	.file 14 "include/asm/thread_info.h"
	.file 15 "include/linux/kernel.h"
	.file 16 "include/linux/mm.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.ualong	0x762
	.uaword	0x2
	.ualong	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ualong	.LASF106
	.byte	0x1
	.ualong	.LASF107
	.ualong	.LASF108
	.ualong	.Ldebug_ranges0+0
	.ualong	0
	.ualong	0
	.ualong	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ualong	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ualong	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.ualong	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ualong	.LASF3
	.uleb128 0x4
	.ualong	.LASF12
	.byte	0x2
	.byte	0x12
	.ualong	0x57
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ualong	.LASF4
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ualong	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.ualong	.LASF6
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ualong	.LASF7
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.ualong	.LASF8
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.ualong	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.ualong	.LASF10
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.ualong	.LASF11
	.uleb128 0x4
	.ualong	.LASF13
	.byte	0x3
	.byte	0x43
	.ualong	0x4c
	.uleb128 0x5
	.byte	0x4
	.ualong	0xa0
	.uleb128 0x6
	.ualong	0x5e
	.uleb128 0x7
	.ualong	.LASF76
	.byte	0x1
	.uleb128 0x5
	.byte	0x4
	.ualong	0xa5
	.uleb128 0x8
	.ualong	.LASF22
	.byte	0x8
	.byte	0x4
	.byte	0x15
	.ualong	0xda
	.uleb128 0x9
	.ualong	.LASF14
	.byte	0x4
	.byte	0x16
	.ualong	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF15
	.byte	0x4
	.byte	0x16
	.ualong	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.ualong	0xb1
	.uleb128 0xa
	.byte	0x4
	.uleb128 0xb
	.byte	0
	.byte	0x5
	.byte	0x19
	.uleb128 0x4
	.ualong	.LASF16
	.byte	0x5
	.byte	0x19
	.ualong	0xe2
	.uleb128 0xc
	.byte	0
	.byte	0x6
	.byte	0x14
	.ualong	0x108
	.uleb128 0x9
	.ualong	.LASF17
	.byte	0x6
	.byte	0x15
	.ualong	0xe6
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x4
	.ualong	.LASF18
	.byte	0x6
	.byte	0x20
	.ualong	0xf1
	.uleb128 0xc
	.byte	0x4
	.byte	0x7
	.byte	0xa
	.ualong	0x12a
	.uleb128 0x9
	.ualong	.LASF19
	.byte	0x7
	.byte	0xa
	.ualong	0x12a
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0xd
	.ualong	0x37
	.uleb128 0x4
	.ualong	.LASF20
	.byte	0x7
	.byte	0xa
	.ualong	0x113
	.uleb128 0x4
	.ualong	.LASF21
	.byte	0x8
	.byte	0x8d
	.ualong	0x12f
	.uleb128 0x8
	.ualong	.LASF23
	.byte	0x8
	.byte	0x9
	.byte	0x32
	.ualong	0x16e
	.uleb128 0x9
	.ualong	.LASF24
	.byte	0x9
	.byte	0x33
	.ualong	0x108
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF25
	.byte	0x9
	.byte	0x34
	.ualong	0xb1
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x4
	.ualong	.LASF26
	.byte	0x9
	.byte	0x36
	.ualong	0x145
	.uleb128 0x8
	.ualong	.LASF27
	.byte	0xc
	.byte	0xa
	.byte	0x23
	.ualong	0x1a2
	.uleb128 0x9
	.ualong	.LASF28
	.byte	0xa
	.byte	0x24
	.ualong	0xb1
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF29
	.byte	0xa
	.byte	0x25
	.ualong	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x8
	.ualong	.LASF30
	.byte	0x14
	.byte	0xa
	.byte	0x55
	.ualong	0x1e7
	.uleb128 0x9
	.ualong	.LASF31
	.byte	0xa
	.byte	0x56
	.ualong	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF32
	.byte	0xa
	.byte	0x57
	.ualong	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x9
	.ualong	.LASF33
	.byte	0xa
	.byte	0x58
	.ualong	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x9
	.ualong	.LASF34
	.byte	0xa
	.byte	0x59
	.ualong	0xb1
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x8
	.ualong	.LASF35
	.byte	0x28
	.byte	0xa
	.byte	0x5c
	.ualong	0x202
	.uleb128 0xe
	.string	"pcp"
	.byte	0xa
	.byte	0x5d
	.ualong	0x202
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0xf
	.ualong	0x1a2
	.ualong	0x212
	.uleb128 0x10
	.ualong	0x29
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.ualong	.LASF36
	.uaword	0x140
	.byte	0xa
	.byte	0xbf
	.ualong	0x399
	.uleb128 0x9
	.ualong	.LASF37
	.byte	0xa
	.byte	0xc1
	.ualong	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF38
	.byte	0xa
	.byte	0xc1
	.ualong	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x9
	.ualong	.LASF39
	.byte	0xa
	.byte	0xc1
	.ualong	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x9
	.ualong	.LASF40
	.byte	0xa
	.byte	0xca
	.ualong	0x399
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x9
	.ualong	.LASF41
	.byte	0xa
	.byte	0xd5
	.ualong	0x3a9
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x9
	.ualong	.LASF24
	.byte	0xa
	.byte	0xda
	.ualong	0x108
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x9
	.ualong	.LASF27
	.byte	0xa
	.byte	0xdf
	.ualong	0x3b9
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x9
	.ualong	.LASF42
	.byte	0xa
	.byte	0xe5
	.ualong	0x108
	.byte	0x3
	.byte	0x23
	.uleb128 0xc0
	.uleb128 0x9
	.ualong	.LASF43
	.byte	0xa
	.byte	0xe6
	.ualong	0xb1
	.byte	0x3
	.byte	0x23
	.uleb128 0xc0
	.uleb128 0x9
	.ualong	.LASF44
	.byte	0xa
	.byte	0xe7
	.ualong	0xb1
	.byte	0x3
	.byte	0x23
	.uleb128 0xc8
	.uleb128 0x9
	.ualong	.LASF45
	.byte	0xa
	.byte	0xe8
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0xd0
	.uleb128 0x9
	.ualong	.LASF46
	.byte	0xa
	.byte	0xe9
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0xd4
	.uleb128 0x9
	.ualong	.LASF47
	.byte	0xa
	.byte	0xea
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0xd8
	.uleb128 0x9
	.ualong	.LASF48
	.byte	0xa
	.byte	0xeb
	.ualong	0x37
	.byte	0x3
	.byte	0x23
	.uleb128 0xdc
	.uleb128 0x9
	.ualong	.LASF49
	.byte	0xa
	.byte	0xee
	.ualong	0x12f
	.byte	0x3
	.byte	0x23
	.uleb128 0xe0
	.uleb128 0x9
	.ualong	.LASF50
	.byte	0xa
	.byte	0xf1
	.ualong	0x3c9
	.byte	0x3
	.byte	0x23
	.uleb128 0xe4
	.uleb128 0x12
	.ualong	.LASF51
	.byte	0xa
	.uaword	0x100
	.ualong	0x37
	.byte	0x3
	.byte	0x23
	.uleb128 0x11c
	.uleb128 0x12
	.ualong	.LASF52
	.byte	0xa
	.uaword	0x11e
	.ualong	0x3d9
	.byte	0x3
	.byte	0x23
	.uleb128 0x120
	.uleb128 0x12
	.ualong	.LASF53
	.byte	0xa
	.uaword	0x11f
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x124
	.uleb128 0x12
	.ualong	.LASF54
	.byte	0xa
	.uaword	0x120
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x128
	.uleb128 0x12
	.ualong	.LASF55
	.byte	0xa
	.uaword	0x125
	.ualong	0x4ad
	.byte	0x3
	.byte	0x23
	.uleb128 0x12c
	.uleb128 0x12
	.ualong	.LASF56
	.byte	0xa
	.uaword	0x127
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x130
	.uleb128 0x12
	.ualong	.LASF57
	.byte	0xa
	.uaword	0x133
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x134
	.uleb128 0x12
	.ualong	.LASF58
	.byte	0xa
	.uaword	0x134
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x138
	.uleb128 0x12
	.ualong	.LASF59
	.byte	0xa
	.uaword	0x139
	.ualong	0x9a
	.byte	0x3
	.byte	0x23
	.uleb128 0x13c
	.byte	0
	.uleb128 0xf
	.ualong	0x30
	.ualong	0x3a9
	.uleb128 0x10
	.ualong	0x29
	.byte	0x1
	.byte	0
	.uleb128 0xf
	.ualong	0x1e7
	.ualong	0x3b9
	.uleb128 0x10
	.ualong	0x29
	.byte	0
	.byte	0
	.uleb128 0xf
	.ualong	0x179
	.ualong	0x3c9
	.uleb128 0x10
	.ualong	0x29
	.byte	0xa
	.byte	0
	.uleb128 0xf
	.ualong	0x13a
	.ualong	0x3d9
	.uleb128 0x10
	.ualong	0x29
	.byte	0xd
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.ualong	0x16e
	.uleb128 0x13
	.ualong	.LASF60
	.uaword	0x2cc
	.byte	0xa
	.uaword	0x1c8
	.ualong	0x4ad
	.uleb128 0x12
	.ualong	.LASF61
	.byte	0xa
	.uaword	0x1c9
	.ualong	0x501
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x12
	.ualong	.LASF62
	.byte	0xa
	.uaword	0x1ca
	.ualong	0x511
	.byte	0x3
	.byte	0x23
	.uleb128 0x280
	.uleb128 0x12
	.ualong	.LASF63
	.byte	0xa
	.uaword	0x1cb
	.ualong	0x37
	.byte	0x3
	.byte	0x23
	.uleb128 0x2a0
	.uleb128 0x12
	.ualong	.LASF64
	.byte	0xa
	.uaword	0x1cd
	.ualong	0x570
	.byte	0x3
	.byte	0x23
	.uleb128 0x2a4
	.uleb128 0x12
	.ualong	.LASF65
	.byte	0xa
	.uaword	0x1cf
	.ualong	0x57c
	.byte	0x3
	.byte	0x23
	.uleb128 0x2a8
	.uleb128 0x12
	.ualong	.LASF66
	.byte	0xa
	.uaword	0x1da
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x2ac
	.uleb128 0x12
	.ualong	.LASF67
	.byte	0xa
	.uaword	0x1db
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x2b0
	.uleb128 0x12
	.ualong	.LASF68
	.byte	0xa
	.uaword	0x1dc
	.ualong	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x2b4
	.uleb128 0x12
	.ualong	.LASF69
	.byte	0xa
	.uaword	0x1de
	.ualong	0x37
	.byte	0x3
	.byte	0x23
	.uleb128 0x2b8
	.uleb128 0x12
	.ualong	.LASF70
	.byte	0xa
	.uaword	0x1df
	.ualong	0x16e
	.byte	0x3
	.byte	0x23
	.uleb128 0x2bc
	.uleb128 0x12
	.ualong	.LASF71
	.byte	0xa
	.uaword	0x1e0
	.ualong	0xab
	.byte	0x3
	.byte	0x23
	.uleb128 0x2c4
	.uleb128 0x12
	.ualong	.LASF72
	.byte	0xa
	.uaword	0x1e1
	.ualong	0x37
	.byte	0x3
	.byte	0x23
	.uleb128 0x2c8
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.ualong	0x3df
	.uleb128 0x14
	.ualong	.LASF73
	.byte	0x10
	.byte	0xa
	.uaword	0x195
	.ualong	0x4df
	.uleb128 0x12
	.ualong	.LASF74
	.byte	0xa
	.uaword	0x196
	.ualong	0x4e5
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x12
	.ualong	.LASF75
	.byte	0xa
	.uaword	0x197
	.ualong	0x4eb
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x7
	.ualong	.LASF77
	.byte	0x1
	.uleb128 0x5
	.byte	0x4
	.ualong	0x4df
	.uleb128 0xf
	.ualong	0x4fb
	.ualong	0x4fb
	.uleb128 0x10
	.ualong	0x29
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.ualong	0x212
	.uleb128 0xf
	.ualong	0x212
	.ualong	0x511
	.uleb128 0x10
	.ualong	0x29
	.byte	0x1
	.byte	0
	.uleb128 0xf
	.ualong	0x4b3
	.ualong	0x521
	.uleb128 0x10
	.ualong	0x29
	.byte	0x1
	.byte	0
	.uleb128 0x8
	.ualong	.LASF78
	.byte	0x20
	.byte	0xb
	.byte	0x12
	.ualong	0x570
	.uleb128 0x9
	.ualong	.LASF79
	.byte	0xb
	.byte	0x13
	.ualong	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF80
	.byte	0xb
	.byte	0x15
	.ualong	0x12f
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x15
	.ualong	0x5a7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x15
	.ualong	0x63f
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x15
	.ualong	0x657
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xe
	.string	"lru"
	.byte	0xb
	.byte	0x40
	.ualong	0xb1
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.ualong	0x521
	.uleb128 0x7
	.ualong	.LASF81
	.byte	0x1
	.uleb128 0x5
	.byte	0x4
	.ualong	0x576
	.uleb128 0xc
	.byte	0x4
	.byte	0xb
	.byte	0x1b
	.ualong	0x5a7
	.uleb128 0x9
	.ualong	.LASF82
	.byte	0xb
	.byte	0x1c
	.ualong	0x3e
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF83
	.byte	0xb
	.byte	0x1d
	.ualong	0x3e
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x16
	.byte	0x4
	.byte	0xb
	.byte	0x16
	.ualong	0x5c0
	.uleb128 0x17
	.ualong	.LASF91
	.byte	0xb
	.byte	0x17
	.ualong	0x12f
	.uleb128 0x18
	.ualong	0x582
	.byte	0
	.uleb128 0xc
	.byte	0x8
	.byte	0xb
	.byte	0x21
	.ualong	0x5e5
	.uleb128 0x9
	.ualong	.LASF84
	.byte	0xb
	.byte	0x22
	.ualong	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF85
	.byte	0xb
	.byte	0x29
	.ualong	0x5eb
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x7
	.ualong	.LASF86
	.byte	0x1
	.uleb128 0x5
	.byte	0x4
	.ualong	0x5e5
	.uleb128 0xc
	.byte	0x8
	.byte	0xb
	.byte	0x34
	.ualong	0x616
	.uleb128 0x9
	.ualong	.LASF87
	.byte	0xb
	.byte	0x35
	.ualong	0x616
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF88
	.byte	0xb
	.byte	0x36
	.ualong	0x622
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.ualong	0xe0
	.uleb128 0x7
	.ualong	.LASF89
	.byte	0x1
	.uleb128 0x5
	.byte	0x4
	.ualong	0x61c
	.uleb128 0xc
	.byte	0x4
	.byte	0xb
	.byte	0x38
	.ualong	0x63f
	.uleb128 0x9
	.ualong	.LASF90
	.byte	0xb
	.byte	0x39
	.ualong	0x570
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x16
	.byte	0x8
	.byte	0xb
	.byte	0x20
	.ualong	0x657
	.uleb128 0x18
	.ualong	0x5c0
	.uleb128 0x18
	.ualong	0x5f1
	.uleb128 0x18
	.ualong	0x628
	.byte	0
	.uleb128 0x16
	.byte	0x4
	.byte	0xb
	.byte	0x3c
	.ualong	0x676
	.uleb128 0x17
	.ualong	.LASF92
	.byte	0xb
	.byte	0x3d
	.ualong	0x30
	.uleb128 0x17
	.ualong	.LASF93
	.byte	0xb
	.byte	0x3e
	.ualong	0xe0
	.byte	0
	.uleb128 0x8
	.ualong	.LASF94
	.byte	0x8
	.byte	0xc
	.byte	0x13
	.ualong	0x69f
	.uleb128 0x9
	.ualong	.LASF95
	.byte	0xc
	.byte	0x14
	.ualong	0x8f
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ualong	.LASF96
	.byte	0xc
	.byte	0x15
	.ualong	0x622
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x8
	.ualong	.LASF97
	.byte	0x68
	.byte	0xd
	.byte	0x36
	.ualong	0x6ba
	.uleb128 0x9
	.ualong	.LASF98
	.byte	0xd
	.byte	0x37
	.ualong	0x6ba
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0xf
	.ualong	0x30
	.ualong	0x6ca
	.uleb128 0x10
	.ualong	0x29
	.byte	0x19
	.byte	0
	.uleb128 0x19
	.byte	0x1
	.ualong	.LASF109
	.byte	0x1
	.byte	0x15
	.byte	0x1
	.ualong	0x37
	.ualong	.LFB393
	.ualong	.LFE393
	.byte	0x2
	.byte	0x7f
	.sleb128 0
	.byte	0x1
	.uleb128 0x1a
	.ualong	.LASF99
	.byte	0xe
	.byte	0x47
	.ualong	0x30
	.byte	0x1
	.byte	0x1
	.byte	0x5f
	.uleb128 0xf
	.ualong	0x37
	.ualong	0x6fc
	.uleb128 0x1b
	.byte	0
	.uleb128 0x1c
	.ualong	.LASF100
	.byte	0xf
	.byte	0x41
	.ualong	0x6f1
	.byte	0x1
	.byte	0x1
	.uleb128 0x1d
	.ualong	.LASF101
	.byte	0xa
	.uaword	0x1b9
	.ualong	0x570
	.byte	0x1
	.byte	0x1
	.uleb128 0x1d
	.ualong	.LASF102
	.byte	0xa
	.uaword	0x26f
	.ualong	0x3df
	.byte	0x1
	.byte	0x1
	.uleb128 0xf
	.ualong	0x676
	.ualong	0x730
	.uleb128 0x1b
	.byte	0
	.uleb128 0x1c
	.ualong	.LASF103
	.byte	0xc
	.byte	0x1a
	.ualong	0x725
	.byte	0x1
	.byte	0x1
	.uleb128 0x1c
	.ualong	.LASF104
	.byte	0xd
	.byte	0x3a
	.ualong	0x69f
	.byte	0x1
	.byte	0x1
	.uleb128 0x1c
	.ualong	.LASF50
	.byte	0xd
	.byte	0x7a
	.ualong	0x3c9
	.byte	0x1
	.byte	0x1
	.uleb128 0x1d
	.ualong	.LASF105
	.byte	0x10
	.uaword	0x272
	.ualong	0x5e5
	.byte	0x1
	.byte	0x1
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.ualong	0x1c
	.uaword	0x2
	.ualong	.Ldebug_info0
	.byte	0x4
	.byte	0
	.uaword	0
	.uaword	0
	.ualong	.LFB393
	.ualong	.LFE393-.LFB393
	.ualong	0
	.ualong	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.ualong	.LFB393
	.ualong	.LFE393
	.ualong	0
	.ualong	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF82:
	.string	"inuse"
.LASF51:
	.string	"prev_priority"
.LASF16:
	.string	"raw_spinlock_t"
.LASF88:
	.string	"slab"
.LASF81:
	.string	"bootmem_data"
.LASF24:
	.string	"lock"
.LASF22:
	.string	"list_head"
.LASF57:
	.string	"spanned_pages"
.LASF68:
	.string	"node_spanned_pages"
.LASF9:
	.string	"short int"
.LASF13:
	.string	"size_t"
.LASF47:
	.string	"pages_scanned"
.LASF96:
	.string	"cs_cachep"
.LASF69:
	.string	"node_id"
.LASF35:
	.string	"per_cpu_pageset"
.LASF91:
	.string	"_mapcount"
.LASF76:
	.string	"task_struct"
.LASF6:
	.string	"long long int"
.LASF46:
	.string	"nr_scan_inactive"
.LASF98:
	.string	"event"
.LASF27:
	.string	"free_area"
.LASF44:
	.string	"inactive_list"
.LASF86:
	.string	"address_space"
.LASF92:
	.string	"index"
.LASF100:
	.string	"console_printk"
.LASF64:
	.string	"node_mem_map"
.LASF7:
	.string	"signed char"
.LASF108:
	.string	"/home/coolshou/develop/nextvod/org/linux-sh4-2.6.23.17_stm23_A18B/linux-sh4-2.6.23.17_stm23_A18B"
.LASF50:
	.string	"vm_stat"
.LASF40:
	.string	"lowmem_reserve"
.LASF29:
	.string	"nr_free"
.LASF37:
	.string	"pages_min"
.LASF78:
	.string	"page"
.LASF3:
	.string	"long int"
.LASF95:
	.string	"cs_size"
.LASF32:
	.string	"high"
.LASF105:
	.string	"swapper_space"
.LASF62:
	.string	"node_zonelists"
.LASF85:
	.string	"mapping"
.LASF107:
	.string	"arch/sh/kernel/asm-offsets.c"
.LASF55:
	.string	"zone_pgdat"
.LASF43:
	.string	"active_list"
.LASF80:
	.string	"_count"
.LASF59:
	.string	"name"
.LASF65:
	.string	"bdata"
.LASF72:
	.string	"kswapd_max_order"
.LASF17:
	.string	"raw_lock"
.LASF8:
	.string	"unsigned char"
.LASF19:
	.string	"counter"
.LASF26:
	.string	"wait_queue_head_t"
.LASF15:
	.string	"prev"
.LASF102:
	.string	"contig_page_data"
.LASF41:
	.string	"pageset"
.LASF79:
	.string	"flags"
.LASF10:
	.string	"long long unsigned int"
.LASF21:
	.string	"atomic_long_t"
.LASF4:
	.string	"unsigned int"
.LASF53:
	.string	"wait_table_hash_nr_entries"
.LASF30:
	.string	"per_cpu_pages"
.LASF45:
	.string	"nr_scan_active"
.LASF52:
	.string	"wait_table"
.LASF104:
	.string	"per_cpu__vm_event_states"
.LASF70:
	.string	"kswapd_wait"
.LASF2:
	.string	"short unsigned int"
.LASF83:
	.string	"offset"
.LASF60:
	.string	"pglist_data"
.LASF97:
	.string	"vm_event_state"
.LASF39:
	.string	"pages_high"
.LASF5:
	.string	"char"
.LASF109:
	.string	"main"
.LASF42:
	.string	"lru_lock"
.LASF63:
	.string	"nr_zones"
.LASF34:
	.string	"list"
.LASF25:
	.string	"task_list"
.LASF11:
	.string	"_Bool"
.LASF48:
	.string	"all_unreclaimable"
.LASF77:
	.string	"zonelist_cache"
.LASF36:
	.string	"zone"
.LASF38:
	.string	"pages_low"
.LASF1:
	.string	"long unsigned int"
.LASF106:
	.string	"GNU C 4.7.2 20121106 (STMicroelectronics/Linux Base 4.7.2-113)"
.LASF90:
	.string	"first_page"
.LASF75:
	.string	"zones"
.LASF93:
	.string	"freelist"
.LASF31:
	.string	"count"
.LASF74:
	.string	"zlcache_ptr"
.LASF71:
	.string	"kswapd"
.LASF94:
	.string	"cache_sizes"
.LASF23:
	.string	"__wait_queue_head"
.LASF61:
	.string	"node_zones"
.LASF66:
	.string	"node_start_pfn"
.LASF49:
	.string	"reclaim_in_progress"
.LASF101:
	.string	"mem_map"
.LASF28:
	.string	"free_list"
.LASF89:
	.string	"kmem_cache"
.LASF0:
	.string	"sizetype"
.LASF12:
	.string	"__kernel_size_t"
.LASF67:
	.string	"node_present_pages"
.LASF87:
	.string	"lockless_freelist"
.LASF54:
	.string	"wait_table_bits"
.LASF99:
	.string	"current_stack_pointer"
.LASF84:
	.string	"private"
.LASF103:
	.string	"malloc_sizes"
.LASF56:
	.string	"zone_start_pfn"
.LASF33:
	.string	"batch"
.LASF58:
	.string	"present_pages"
.LASF14:
	.string	"next"
.LASF20:
	.string	"atomic_t"
.LASF73:
	.string	"zonelist"
.LASF18:
	.string	"spinlock_t"
	.ident	"GCC: (GNU) 4.7.2 20121106 (STMicroelectronics/Linux Base 4.7.2-113)"
	.section	.note.GNU-stack,"",@progbits
