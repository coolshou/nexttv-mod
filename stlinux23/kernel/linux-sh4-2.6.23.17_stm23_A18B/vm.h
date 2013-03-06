
vmlinux:     file format elf32-sh-linux

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .empty_zero_page 00001000  80001000  80001000  00001000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  1 .text         002742c4  80002000  80002000  00002000  2**12
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .text.unlikely 0000194c  802762e0  802762e0  002762e0  2**5
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  3 __ex_table    000017a8  80277c30  80277c30  00277c30  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .notes        00000024  802793d8  802793d8  002793d8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  5 .rodata       0008d270  8027a000  8027a000  0027a000  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .eh_frame     00000078  80307270  80307270  00307270  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 __ksymtab     00004c20  803072e8  803072e8  003072e8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 __ksymtab_gpl 00001270  8030bf08  8030bf08  0030bf08  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 __ksymtab_gpl_future 00000018  8030d178  8030d178  0030d178  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 __ksymtab_strings 0000dd0c  8030d190  8030d190  0030d190  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 11 __param       000006e0  8031ae9c  8031ae9c  0031ae9c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 12 __bug_table   00003940  8031c000  8031c000  0031c000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 13 .uncached.text 00000360  80320000  80320000  00320000  2**5
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .uncached.data 00000180  80320360  80320360  00320360  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 15 .data         00028b20  803204e0  803204e0  003204e0  2**5
                  CONTENTS, ALLOC, LOAD, DATA
 16 .got          00000004  80349000  80349000  00349000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 17 .got.plt      0000000c  80349004  80349004  00349004  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 18 .data.cacheline_aligned 000000c0  8034a000  8034a000  0034a000  2**5
                  CONTENTS, ALLOC, LOAD, DATA
 19 .data.init_task 00002000  8034c000  8034c000  0034c000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 20 .init.text    00016580  8034e000  8034e000  0034e000  2**5
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 21 .init.data    00002660  80364580  80364580  00364580  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 22 .init.setup   0000033c  80366be0  80366be0  00366be0  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 23 .initcall.init 000002a0  80366f1c  80366f1c  00366f1c  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 24 .con_initcall.init 00000008  803671bc  803671bc  003671bc  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 25 .exit.text    000010a4  803671c4  803671c4  003671c4  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 26 .init.ramfs   00000086  80369000  80369000  00369000  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 27 .machvec.init 00000088  80369088  80369088  00369088  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 28 .bss          0001c9cc  8036a000  8036a000  00369110  2**5
                  ALLOC
 29 .comment      00000044  00000000  00000000  00369110  2**0
                  CONTENTS, READONLY
 30 .debug_aranges 00006db8  00000000  00000000  00369154  2**0
                  CONTENTS, READONLY, DEBUGGING
 31 .debug_info   018d0264  00000000  00000000  0036ff0c  2**0
                  CONTENTS, READONLY, DEBUGGING
 32 .debug_abbrev 000e7729  00000000  00000000  01c40170  2**0
                  CONTENTS, READONLY, DEBUGGING
 33 .debug_line   001dfedb  00000000  00000000  01d27899  2**0
                  CONTENTS, READONLY, DEBUGGING
 34 .debug_frame  0005ede8  00000000  00000000  01f07774  2**2
                  CONTENTS, READONLY, DEBUGGING
 35 .debug_str    0009ad29  00000000  00000000  01f6655c  2**0
                  CONTENTS, READONLY, DEBUGGING
 36 .debug_loc    0061d873  00000000  00000000  02001285  2**0
                  CONTENTS, READONLY, DEBUGGING
 37 .debug_ranges 000e3298  00000000  00000000  0261eaf8  2**0
                  CONTENTS, READONLY, DEBUGGING
