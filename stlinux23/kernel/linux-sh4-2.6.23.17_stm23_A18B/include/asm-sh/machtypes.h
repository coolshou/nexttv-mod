/*
 * Automagically generated, don't touch.
 */
#ifndef __ASM_SH_MACHTYPES_H
#define __ASM_SH_MACHTYPES_H

/*
 * We'll use the following MACH_xxx defs for placeholders for the time
 * being .. these will all go away once sh_machtype is assigned per-board.
 *
 * For now we leave things the way they are for backwards compatibility.
 */

/* Mach types */
#ifdef CONFIG_SH_SOLUTION_ENGINE
  #define MACH_SE		1
#else
  #define MACH_SE		0
#endif
#ifdef CONFIG_SH_7722_SOLUTION_ENGINE
  #define MACH_7722SE		1
#else
  #define MACH_7722SE		0
#endif
#ifdef CONFIG_SH_7343_SOLUTION_ENGINE
  #define MACH_7343SE		1
#else
  #define MACH_7343SE		0
#endif
#ifdef CONFIG_SH_7206_SOLUTION_ENGINE
  #define MACH_7206SE		1
#else
  #define MACH_7206SE		0
#endif
#ifdef CONFIG_SH_7619_SOLUTION_ENGINE
  #define MACH_7619SE		1
#else
  #define MACH_7619SE		0
#endif
#ifdef CONFIG_SH_7751_SOLUTION_ENGINE
  #define MACH_7751SE		1
#else
  #define MACH_7751SE		0
#endif
#ifdef CONFIG_SH_7780_SOLUTION_ENGINE
  #define MACH_7780SE		1
#else
  #define MACH_7780SE		0
#endif
#ifdef CONFIG_SH_7751_SYSTEMH
  #define MACH_7751SYSTEMH		1
#else
  #define MACH_7751SYSTEMH		0
#endif
#ifdef CONFIG_SH_HP6XX
  #define MACH_HP6XX		1
#else
  #define MACH_HP6XX		0
#endif
#ifdef CONFIG_HD64461
  #define MACH_HD64461		1
#else
  #define MACH_HD64461		0
#endif
#ifdef CONFIG_HD64465
  #define MACH_HD64465		1
#else
  #define MACH_HD64465		0
#endif
#ifdef CONFIG_SH_DREAMCAST
  #define MACH_DREAMCAST		1
#else
  #define MACH_DREAMCAST		0
#endif
#ifdef CONFIG_SH_MPC1211
  #define MACH_MPC1211		1
#else
  #define MACH_MPC1211		0
#endif
#ifdef CONFIG_SH_SECUREEDGE5410
  #define MACH_SNAPGEAR		1
#else
  #define MACH_SNAPGEAR		0
#endif
#ifdef CONFIG_SH_HS7751RVOIP
  #define MACH_HS7751RVOIP		1
#else
  #define MACH_HS7751RVOIP		0
#endif
#ifdef CONFIG_SH_RTS7751R2D
  #define MACH_RTS7751R2D		1
#else
  #define MACH_RTS7751R2D		0
#endif
#ifdef CONFIG_SH_EDOSK7705
  #define MACH_EDOSK7705		1
#else
  #define MACH_EDOSK7705		0
#endif
#ifdef CONFIG_SH_SH4202_MICRODEV
  #define MACH_SH4202_MICRODEV		1
#else
  #define MACH_SH4202_MICRODEV		0
#endif
#ifdef CONFIG_SH_SH03
  #define MACH_SH03		1
#else
  #define MACH_SH03		0
#endif
#ifdef CONFIG_SH_LANDISK
  #define MACH_LANDISK		1
#else
  #define MACH_LANDISK		0
#endif
#ifdef CONFIG_SH_R7780RP
  #define MACH_R7780RP		1
#else
  #define MACH_R7780RP		0
#endif
#ifdef CONFIG_SH_R7780MP
  #define MACH_R7780MP		1
#else
  #define MACH_R7780MP		0
#endif
#ifdef CONFIG_SH_R7785RP
  #define MACH_R7785RP		1
#else
  #define MACH_R7785RP		0
#endif
#ifdef CONFIG_SH_TITAN
  #define MACH_TITAN		1
#else
  #define MACH_TITAN		0
#endif
#ifdef CONFIG_SH_SHMIN
  #define MACH_SHMIN		1
#else
  #define MACH_SHMIN		0
#endif
#ifdef CONFIG_SH_7710VOIPGW
  #define MACH_7710VOIPGW		1
#else
  #define MACH_7710VOIPGW		0
#endif
#ifdef CONFIG_SH_LBOX_RE2
  #define MACH_LBOXRE2		1
#else
  #define MACH_LBOXRE2		0
#endif

/* Machtype checks */
#define mach_is_se()			(MACH_SE)
#define mach_is_7722se()			(MACH_7722SE)
#define mach_is_7343se()			(MACH_7343SE)
#define mach_is_7206se()			(MACH_7206SE)
#define mach_is_7619se()			(MACH_7619SE)
#define mach_is_7751se()			(MACH_7751SE)
#define mach_is_7780se()			(MACH_7780SE)
#define mach_is_7751systemh()			(MACH_7751SYSTEMH)
#define mach_is_hp6xx()			(MACH_HP6XX)
#define mach_is_hd64461()			(MACH_HD64461)
#define mach_is_hd64465()			(MACH_HD64465)
#define mach_is_dreamcast()			(MACH_DREAMCAST)
#define mach_is_mpc1211()			(MACH_MPC1211)
#define mach_is_snapgear()			(MACH_SNAPGEAR)
#define mach_is_hs7751rvoip()			(MACH_HS7751RVOIP)
#define mach_is_rts7751r2d()			(MACH_RTS7751R2D)
#define mach_is_edosk7705()			(MACH_EDOSK7705)
#define mach_is_sh4202_microdev()			(MACH_SH4202_MICRODEV)
#define mach_is_sh03()			(MACH_SH03)
#define mach_is_landisk()			(MACH_LANDISK)
#define mach_is_r7780rp()			(MACH_R7780RP)
#define mach_is_r7780mp()			(MACH_R7780MP)
#define mach_is_r7785rp()			(MACH_R7785RP)
#define mach_is_titan()			(MACH_TITAN)
#define mach_is_shmin()			(MACH_SHMIN)
#define mach_is_7710voipgw()			(MACH_7710VOIPGW)
#define mach_is_lboxre2()			(MACH_LBOXRE2)

#endif /* __ASM_SH_MACHTYPES_H */
