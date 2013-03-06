/*
 * Automatically generated C config: don't edit
 * Linux kernel version: 2.6.23.17
 * Thu Jan 24 00:19:03 2013
 */
/* $Id: vmlinux.lds.S,v 1.8 2003/05/16 17:18:14 lethal Exp $
 * ld script to make SuperH Linux kernel
 * Written by Niibe Yutaka
 */

/* SuperH version
 * Copyright (C) 2002  Niibe Yutaka
 *
 * The copyright of original i386 version is:
 *
 *  Copyright (C) 2002  David Howells (dhowells@redhat.com)
 *  - Incorporating suggestions made by Linus Torvalds and Dave Miller
 */
/*
 * Copyright (C) 1999  Niibe Yutaka
 */


/* const.h: Macros for dealing with constants.  */


/* Some constant macros are used in both assembler and
 * C code.  Therefore we cannot annotate them always with
 * 'UL' and other type specifiers unilaterally.  We
 * use the following macros to deal with this.
 */




/* PAGE_SHIFT determines the page size */





/* to align the pointer to the (next) page boundary */

/*
 * __MEMORY_START and SIZE are the physical addresses and size of RAM.
 */

/*
 * PAGE_OFFSET is the virtual address of the start of kernel address
 * space.
 */

/*
 * Virtual to physical RAM address translation.
 * In 29 bit mode, the physical offset of RAM from address 0 is visible in
 * the kernel virtual address space, and thus we don't have to take
 * this into account when translating. However in 32 bit mode this offset
 * is not visible (it is part of the PMB mapping) and so needs to be
 * added or subtracted as required.
 */


/*
 * PFN = physical frame number (ie PFN 0 == physical address 0)
 * PFN_START is the PFN of the first page of RAM. By defining this we
 * don't have struct page entries for the portion of address space
 * between physical address 0 and the start of RAM.
 */







/* vDSO support */

/*
 * Slub defaults to 8-byte alignment, we're only interested in 4.
 * Slab defaults to BYTES_PER_WORD, which ends up being the same anyways.
 *
 * However some drivers need to perform DMA into kmalloc'ed buffers
 * and so we have to increase the alignment for this.
 */
/* #define ARCH_KMALLOC_MINALIGN	4 */






/*
 * macros/functions for gaining access to the thread information structure
 */

/*
 * thread information flags
 * - these are process state flags that various assembly files may need to access
 * - pending work-to-be-done flags are in LSW
 * - other flags in MSW
 */




/* PR_[GS]ET_UNALIGN prctls */




/* $Id: cache.h,v 1.6 2004/03/11 18:08:05 lethal Exp $
 *
 * include/asm-sh/cache.h
 *
 * Copyright 1999 (C) Niibe Yutaka
 * Copyright 2002, 2003 (C) Paul Mundt
 */




/*
 * Allow us to mark functions as 'deprecated' and have gcc emit a nice
 * warning for each use, in hopes of speeding the functions removal.
 * Usage is:
 * 		int __deprecated foo(void)
 */




/*
 * Allow us to avoid 'defined but not used' warnings on functions and data,
 * as well as force them to be emitted to the assembly file.
 *
 * As of gcc 3.4, static functions that are not marked with attribute((used))
 * may be elided from the assembly file.  As of gcc 3.4, static data not so
 * marked will not be elided, but this may change in a future gcc version.
 *
 * NOTE: Because distributions shipped with a backported unit-at-a-time
 * compiler in gcc 3.3, we must define __used to be __attribute__((used))
 * for gcc >=3.3 instead of 3.4.
 *
 * In prior versions of gcc, such functions and data would be emitted, but
 * would be warned about except with attribute((unused)).
 *
 * Mark functions that are referenced only in inline assembly as __used so
 * the code is emitted even though it appears to be unreferenced.
 */



/*
 * From the GCC manual:
 *
 * Many functions have no effects except the return value and their
 * return value depends only on the parameters and/or global
 * variables.  Such a function can be subject to common subexpression
 * elimination and loop optimization just as an arithmetic operator
 * would be.
 * [...]
 */




/*
 * From the GCC manual:
 *
 * Many functions do not examine any values except their arguments,
 * and have no effects except the return value.  Basically this is
 * just slightly more strict class than the `pure' attribute above,
 * since function is not allowed to read global memory.
 *
 * Note that a function that has pointer arguments and examines the
 * data pointed to must _not_ be declared `const'.  Likewise, a
 * function that calls a non-`const' function usually must not be
 * `const'.  It does not make sense for a `const' function to return
 * `void'.
 */

/*
 * Tell gcc if a function is cold. The compiler will assume any path
 * directly leading to the call is unlikely.
 */



/* These macros are used to mark some functions or 
 * initialized data (doesn't apply to uninitialized data)
 * as `initialization' functions. The kernel can take this
 * as hint that the function is used only during the initialization
 * phase and free up used memory resources after
 *
 * Usage:
 * For functions:
 * 
 * You should add __init immediately before the function name, like:
 *
 * static void __init initme(int x, int y)
 * {
 *    extern int z; z = x * y;
 * }
 *
 * If the function has a prototype somewhere, you can also add
 * __init between closing brace of the prototype and semicolon:
 *
 * extern int initialize_foobar_device(int, int, int) __init;
 *
 * For initialized data:
 * You should insert __initdata between the variable name and equal
 * sign followed by value, e.g.:
 *
 * static int init_variable __initdata = 0;
 * static char linux_logo[] __initdata = { 0x32, 0x36, ... };
 *
 * Don't forget to initialize data not at file scope, i.e. within a function,
 * as gcc otherwise puts the data into the bss section and not into the init
 * section.
 * 
 * Also note, that this data cannot be "const".
 */

/* These are for everybody (although not all archs will actually
   discard it in modules) */

/* modpost check for section mismatches during the kernel build.
 * A section mismatch happens when there are references from a
 * code or data section to an init section (both code or data).
 * The init sections are (for most archs) discarded by the kernel
 * when early init has completed so all such references are potential bugs.
 * For exit sections the same issue exists.
 * The following markers are used for the cases where the reference to
 * the init/exit section (code or data) is valid and will teach modpost
 * not to issue a warning.
 * The markers follow same syntax rules as __init / __initdata. */


/* For assembly routines */

  


/**
 * module_init() - driver initialization entry point
 * @x: function to be run at kernel boot time or module insertion
 * 
 * module_init() will either be called during do_initcalls() (if
 * builtin) or at module insertion time (if a module).  There can only
 * be one per module.
 */

/**
 * module_exit() - driver exit entry point
 * @x: function to be run when driver is removed
 * 
 * module_exit() will wrap the driver clean-up code
 * with cleanup_module() when used with rmmod when
 * the driver is a module.  If the driver is statically
 * compiled into the kernel, module_exit() has no effect.
 * There can only be one per module.
 */


/* Data marked not to be saved by software suspend */

/* This means "can be init if no module support, otherwise module load
   may call it." */




/* Functions marked as __devexit may be discarded at kernel link time, depending
   on config options.  Newer versions of binutils detect references from
   retained sections to discarded sections and flag an error.  Pointers to
   __devexit functions must use __devexit_p(function_name), the wrapper will
   insert either the function_name or NULL, depending on the config options.
 */


/*
 * include/asm-sh/cpu-sh4/cache.h
 *
 * Copyright (C) 1999 Niibe Yutaka
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */



/* Default CCR setup: 8k+16k-byte cache,P1-wb,enable */









/* Align . to a 8 byte boundary equals to maximum function alignment. */

/* .data section */


/* RODATA provided for backward compatibility.
 * All archs are supposed to use RO_DATA() */


/* .text section. Map to function alignment to avoid address changes
 * during second ld run in second ld pass when generating System.map */

/* sched.text is aling to function alignment to secure we have same
 * address even at second ld pass when generating System.map */

/* spinlock.text is aling to function alignment to secure we have same
 * address even at second ld pass when generating System.map */


		/* DWARF debug sections.
		Symbols in the DWARF debugging sections are relative to
		the beginning of the section so we begin them at 0.  */
		/* Stabs debugging sections.  */





OUTPUT_FORMAT("elf32-sh-linux", "elf32-sh-linux", "elf32-sh-linux")
OUTPUT_ARCH(sh)
ENTRY(_start)
SECTIONS
{
	. = 0x80000000 + 0x00001000;
	_text = .;			/* Text and read-only data */
	text = .;			/* Text and read-only data */
	.empty_zero_page : {
	*(.empty_zero_page)
	} = 0
  .text : {
  	*(.text.head)
	. = ALIGN(8);							*(.text)								*(.text.init.refok)
	. = ALIGN(8);							__sched_text_start = .;					*(.sched.text)								__sched_text_end = .;
	. = ALIGN(8);							__lock_text_start = .;					*(.spinlock.text)							__lock_text_end = .;
	*(.fixup)
	*(.gnu.warning)
	} = 0x0009

  . = ALIGN(16);		/* Exception table */
  __start___ex_table = .;
  __ex_table : { *(__ex_table) }
  __stop___ex_table = .;

  _etext = .;			/* End of text section */

  .notes : AT(ADDR(.notes) - 0) {					__start_notes = .;					*(.note.*)								__stop_notes = .;				}

  . = ALIGN((4096));							.rodata           : AT(ADDR(.rodata) - 0) {				__start_rodata = .;					*(.rodata) *(.rodata.*)							*(__vermagic)					*(__markers_strings)					. = ALIGN(8);								__start___immediate = .;				*(__immediate)		 		__stop___immediate = .;				}																		.rodata1          : AT(ADDR(.rodata1) - 0) {				*(.rodata1)							}																									.pci_fixup        : AT(ADDR(.pci_fixup) - 0) {			__start_pci_fixups_early = .;				*(.pci_fixup_early)							__end_pci_fixups_early = .;				__start_pci_fixups_header = .;				*(.pci_fixup_header)							__end_pci_fixups_header = .;				__start_pci_fixups_final = .;				*(.pci_fixup_final)							__end_pci_fixups_final = .;				__start_pci_fixups_enable = .;				*(.pci_fixup_enable)							__end_pci_fixups_enable = .;				__start_pci_fixups_resume = .;				*(.pci_fixup_resume)							__end_pci_fixups_resume = .;			}																									.rio_route        : AT(ADDR(.rio_route) - 0) {			__start_rio_route_ops = .;				*(.rio_route_ops)							__end_rio_route_ops = .;			}																					__ksymtab.htable         : AT(ADDR(__ksymtab.htable) - 0) {		__start___ksymtab_htable = .;				*(__ksymtab.htable)						}																					__ksymtab_gpl.htable  : AT(ADDR(__ksymtab_gpl.htable) - 0) { 		__start___ksymtab_gpl_htable = .;			*(__ksymtab_gpl.htable)						}																				__ksymtab_gpl_future.htable : AT(ADDR(__ksymtab_gpl_future.htable) - 0) {		__start___ksymtab_gpl_future_htable = .;		*(__ksymtab_gpl_future.htable)					}																				__ksymtab_unused.htable : AT(ADDR(__ksymtab_unused.htable) - 0) { 		__start___ksymtab_unused_htable = .;			*(__ksymtab_unused.htable)					}																				__ksymtab_unused_gpl.htable : AT(ADDR(__ksymtab_unused_gpl.htable) - 0) {			__start___ksymtab_unused_gpl_htable = .;		*(__ksymtab_unused_gpl.htable)					}																						__ksymtab         : AT(ADDR(__ksymtab) - 0) {				__start___ksymtab = .;					*(__ksymtab)								__stop___ksymtab = .;				}																						__ksymtab_gpl     : AT(ADDR(__ksymtab_gpl) - 0) {			__start___ksymtab_gpl = .;				*(__ksymtab_gpl)							__stop___ksymtab_gpl = .;			}																					__ksymtab_unused  : AT(ADDR(__ksymtab_unused) - 0) {			__start___ksymtab_unused = .;				*(__ksymtab_unused)							__stop___ksymtab_unused = .;			}																					__ksymtab_unused_gpl : AT(ADDR(__ksymtab_unused_gpl) - 0) { 		__start___ksymtab_unused_gpl = .;			*(__ksymtab_unused_gpl)							__stop___ksymtab_unused_gpl = .;		}																					__ksymtab_gpl_future : AT(ADDR(__ksymtab_gpl_future) - 0) { 		__start___ksymtab_gpl_future = .;			*(__ksymtab_gpl_future)							__stop___ksymtab_gpl_future = .;		}																						__kcrctab         : AT(ADDR(__kcrctab) - 0) {				__start___kcrctab = .;					*(__kcrctab)								__stop___kcrctab = .;				}																						__kcrctab_gpl     : AT(ADDR(__kcrctab_gpl) - 0) {			__start___kcrctab_gpl = .;				*(__kcrctab_gpl)							__stop___kcrctab_gpl = .;			}																					__kcrctab_unused  : AT(ADDR(__kcrctab_unused) - 0) {			__start___kcrctab_unused = .;				*(__kcrctab_unused)							__stop___kcrctab_unused = .;			}																					__kcrctab_unused_gpl : AT(ADDR(__kcrctab_unused_gpl) - 0) { 		__start___kcrctab_unused_gpl = .;			*(__kcrctab_unused_gpl)							__stop___kcrctab_unused_gpl = .;		}																					__kcrctab_gpl_future : AT(ADDR(__kcrctab_gpl_future) - 0) { 		__start___kcrctab_gpl_future = .;			*(__kcrctab_gpl_future)							__stop___kcrctab_gpl_future = .;		}																						        __ksymtab_strings : AT(ADDR(__ksymtab_strings) - 0) {			*(__ksymtab_strings)						}																							__param : AT(ADDR(__param) - 0) {					__start___param = .;					*(__param)								__stop___param = .;					__end_rodata = .;				}																		. = ALIGN((4096));

  . = ALIGN(8);								__bug_table : AT(ADDR(__bug_table) - 0) {				__start___bug_table = .;						*(__bug_table)								__stop___bug_table = .;						}

	/*
	 * Code which must be executed uncached and the associated data
	 */
	. = ALIGN((1 << 12));
	_start_uncached = .;
  .uncached.text : { *(.uncached) }
  .uncached.data : { *(.uncached.data) }
  _end_uncached = .;

  .data : {			/* Data */
	*(.data)								*(.data.init.refok)							. = ALIGN(8);								__start___markers = .;					*(__markers)								__stop___markers = .;

 	 /* Align the initial ramdisk image (INITRD) on page boundaries. */
 	 . = ALIGN((1 << 12));
 	 __rd_start = .;
 	 *(.initrd)
 	 . = ALIGN((1 << 12));
 	 __rd_end = .;

	CONSTRUCTORS
	}

	. = ALIGN((1 << 12));
  .data.page_aligned : { *(.data.page_aligned) }
  __nosave_begin = .;
  .data_nosave : { *(.data.nosave) }
  . = ALIGN((1 << 12));
  __nosave_end = .;

  . = ALIGN((1 << 12));							__per_cpu_start = .;							.data.percpu  : AT(ADDR(.data.percpu) - 0) {				*(.data.percpu)								*(.data.percpu.shared_aligned)					}									__per_cpu_end = .;

  . = ALIGN((1 << 5));
  .data.cacheline_aligned : { *(.data.cacheline_aligned) }

  _edata = .;			/* End of data section */

  . = ALIGN(((1 << 12) << (1)));		/* init_task */
  .data.init_task : { *(.data.init_task) }

  . = ALIGN((1 << 12));		/* Init code and data */
  __init_begin = .;
  _sinittext = .;
  .init.text : { *(.init.text) }
  _einittext = .;
  .init.data : { *(.init.data) }
  . = ALIGN(16);
  __setup_start = .;
  .init.setup : { *(.init.setup) }
  __setup_end = .;
  __initcall_start = .;
  .initcall.init : {
	*(.initcall0.init)						  	*(.initcall0s.init)						  	*(.initcall1.init)						  	*(.initcall1s.init)						  	*(.initcall2.init)						  	*(.initcall2s.init)						  	*(.initcall3.init)						  	*(.initcall3s.init)						  	*(.initcall4.init)						  	*(.initcall4s.init)						  	*(.initcall5.init)						  	*(.initcall5s.init)							*(.initcallrootfs.init)						  	*(.initcall6.init)						  	*(.initcall6s.init)						  	*(.initcall7.init)						  	*(.initcall7s.init)
  }
  __initcall_end = .;
  __con_initcall_start = .;
  .con_initcall.init : { *(.con_initcall.init) }
  __con_initcall_end = .;
  .security_initcall.init : AT(ADDR(.security_initcall.init) - 0) { 		__security_initcall_start = .;				*(.security_initcall.init) 						__security_initcall_end = .;			}

  /* .exit.text is discarded at runtime, not link time, to deal with
     references from .rodata */
  .exit.text : { *(.exit.text) }
  .exit.data : { *(.exit.data) }

  . = ALIGN((1 << 12));

  __initramfs_start = .;
  .init.ramfs : { *(.init.ramfs) }
  __initramfs_end = .;

 . = ALIGN(4);
  __machvec_start = .;
  .machvec.init : { *(.machvec.init) }
  __machvec_end = .;

  . = ALIGN((1 << 12));
  .bss : {
	__init_end = .;
	__bss_start = .;		/* BSS */
  	*(.bss.page_aligned)
  	*(.bss)
	. = ALIGN(4);
	_ebss = .;			/* uClinux MTD sucks */
	_end = . ;
  }

  /* When something in the kernel is NOT compiled as a module, the
   * module cleanup code and data are put into these segments.  Both
   * can then be thrown away, as cleanup code is never called unless
   * it's a module.
   */
  /DISCARD/ : {
	*(.exitcall.exit)
	}

  .stab 0 : { *(.stab) }							.stabstr 0 : { *(.stabstr) }						.stab.excl 0 : { *(.stab.excl) }					.stab.exclstr 0 : { *(.stab.exclstr) }					.stab.index 0 : { *(.stab.index) }					.stab.indexstr 0 : { *(.stab.indexstr) }				.comment 0 : { *(.comment) }
  .debug          0 : { *(.debug) }					.line           0 : { *(.line) }											.debug_srcinfo  0 : { *(.debug_srcinfo) }				.debug_sfnames  0 : { *(.debug_sfnames) }										.debug_aranges  0 : { *(.debug_aranges) }				.debug_pubnames 0 : { *(.debug_pubnames) }												.debug_info     0 : { *(.debug_info							.gnu.linkonce.wi.*) }					.debug_abbrev   0 : { *(.debug_abbrev) }				.debug_line     0 : { *(.debug_line) }					.debug_frame    0 : { *(.debug_frame) }					.debug_str      0 : { *(.debug_str) }					.debug_loc      0 : { *(.debug_loc) }					.debug_macinfo  0 : { *(.debug_macinfo) }									.debug_weaknames 0 : { *(.debug_weaknames) }				.debug_funcnames 0 : { *(.debug_funcnames) }				.debug_typenames 0 : { *(.debug_typenames) }				.debug_varnames  0 : { *(.debug_varnames) }


}
