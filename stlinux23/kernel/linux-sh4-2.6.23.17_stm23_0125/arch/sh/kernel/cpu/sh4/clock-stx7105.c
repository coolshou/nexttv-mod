/*****************************************************************************
 *
 * File name   : clock-stx7105.c
 * Description : Low Level API - HW specific implementation
 *
 * COPYRIGHT (C) 2009 STMicroelectronics - All Rights Reserved
 * May be copied or modified under the terms of the GNU General Public
 * License V2 __ONLY__.  See linux/COPYING for more information.
 *
 *****************************************************************************/

/* ----- Modification history (most recent first)----
16/dec/09 francesco.virlinzi@st.com
	  minor fix on linux
30/nov/09 francesco.virlinzi@st.com
	  clkgenb_xable_clock()+clkgenb_observe() updates.
27/nov/09 fabrice.charpentier@st.com & francesco
	  clkgena/d/e_identify_parent() bugs fixes.
	  Replaced obsolete REGISTER_CLK() by _CLK() & _CLK_P() macros.
20/nov/09 fabrice.charpentier@st.com & francesco
	  Update towards common 7105 & 7106 file.
	  CLKB_656 renamed to CLKB_656_0. CLKB_ETH_PHY renamed to
	  CLKB_ETH0_PHY. CLKB_SPARE12 renamed to CLKB_MMC.
02/oct/09 francesco.virlinzi@st.com
	  Aligned Linux coding style
17/sep/09 fabrice.charpentier@st.com
	  Aligned on 7111+added clockgen E
24/aug/09 fabrice.charpentier@st.com
	  Revisited. Aligned on 7111 udpates.
10/jul/09 francesco.virlinzi@st.com
09/jul/09 fabrice.charpentier@st.com
	  Revisited to make it more Linux compliant + bug fixes.
07/may/09 Suvrat
	  Original version
*/

/* Includes ----------------------------------------------------------------- */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/stm/clk.h>
#include <linux/io.h>

#include "clock-stx7105.h"
#include "clock-regs-stx7105.h"

#include "clock-oslayer.h"
#include "clock-common.h"

static int clkgena_observe(clk_t *clk_p, unsigned long *div_p);
static int clkgenb_observe(clk_t *clk_p, unsigned long *div_p);
static int clkgena_set_parent(clk_t *clk_p, clk_t *src_p);
static int clkgenb_set_parent(clk_t *clk_p, clk_t *src_p);
static int clkgenc_set_parent(clk_t *clk_p, clk_t *src_p);
static int clkgend_set_parent(clk_t *clk_p, clk_t *src_p);
static int clkgene_set_parent(clk_t *clk_p, clk_t *src_p);
static int clkgena_set_rate(clk_t *clk_p, unsigned long freq);
static int clkgenb_set_rate(clk_t *clk_p, unsigned long freq);
static int clkgenc_set_rate(clk_t *clk_p, unsigned long freq);
static int clkgena_set_div(clk_t *clk_p, unsigned long *div_p);
static int clkgenb_set_div(clk_t *clk_p, unsigned long *div_p);
static int clkgenb_set_fsclock(clk_t *clk_p, unsigned long freq);
static int clkgena_recalc(clk_t *clk_p);
static int clkgenb_recalc(clk_t *clk_p);
static int clkgenc_recalc(clk_t *clk_p);
static int clkgend_recalc(clk_t *clk_p);
static int clkgene_recalc(clk_t *clk_p); /* Added to get infos for USB */
static int clkgena_enable(clk_t *clk_p);
static int clkgenb_enable(clk_t *clk_p);
static int clkgenc_enable(clk_t *clk_p);
static int clkgena_disable(clk_t *clk_p);
static int clkgenb_disable(clk_t *clk_p);
static int clkgenc_disable(clk_t *clk_p);
static unsigned long clkgena_get_measure(clk_t *clk_p);
static int clkgentop_init(clk_t *clk_p);
static int clkgena_init(clk_t *clk_p);
static int clkgenb_init(clk_t *clk_p);
static int clkgenc_init(clk_t *clk_p);
static int clkgend_init(clk_t *clk_p);
static int clkgene_init(clk_t *clk_p);

/* Per boards top input clocks. mb680 currently identical */
#define SYSCLKIN 	30	/* osc */
#define SYSCLKALT	30	/* Alternate osc */

static const unsigned long clkgena_offset_regs[] = {
	CKGA_OSC_DIV0_CFG,
	0, /* dummy */
	CKGA_PLL0HS_DIV0_CFG,
	CKGA_PLL0LS_DIV0_CFG,
	CKGA_PLL1_DIV0_CFG
};


/* Possible operations registration.
   Operations are usually grouped by clockgens due to specific HW
   implementation.

   Name, Desc, init, set_parent, set_rate, recalc, enable, disable,
   observe, measure

   where
	 Name: MUST be the same one declared with _CLK (ops field).
	 Desc: Clockgen group short description. Ex: "clockgen A", "USB", "LMI"
	 init: Clockgen init function (read HW to identify parent & rate).
	 set_parent: Parent/src setup function.
	 set_rate: Clockgen frequency setup function.
	 enable: Clockgen enable function.
	 disable: Clockgen disable function.
	 observe: Clockgen observation function.
	 recalc: Clockgen frequency recompute function. Called when parent
		 clock changed.
	 measure: Clockgen measure function (when HW available).

   Note: If no capability, put NULL instead of function name.
   Note: All functions should return 'clk_err_t'. */

_CLK_OPS(Top,
	"Top clocks",
	clkgentop_init,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,			/* No measure function */
	NULL			/* No observation point */
);
_CLK_OPS(clkgena,
	"Clockgen A",
	clkgena_init,
	clkgena_set_parent,
	clkgena_set_rate,
	clkgena_recalc,
	clkgena_enable,
	clkgena_disable,
	clkgena_observe,
	clkgena_get_measure,
	"TRIGGEROUT"
);
_CLK_OPS(clkgenb,
	"Clockgen B/Video",
	clkgenb_init,
	clkgenb_set_parent,
	clkgenb_set_rate,
	clkgenb_recalc,
	clkgenb_enable,
	clkgenb_disable,
	clkgenb_observe,
	NULL,	/* No measure function */
	"SYSCLKOUT"
);
_CLK_OPS(clkgenc,
	"Clockgen C/Audio",
	clkgenc_init,
	clkgenc_set_parent,
	clkgenc_set_rate,
	clkgenc_recalc,
	clkgenc_enable,
	clkgenc_disable,
	NULL,
	NULL,
	"PIO13[7]"
);
_CLK_OPS(clkgend,
	"Clockgen D/LMI",
	clkgend_init,
	clkgend_set_parent,
	NULL,
	clkgend_recalc,
	NULL,
	NULL,
	NULL,
	NULL,
	"PIO6[2]"
);
_CLK_OPS(clkgene,
	"USB",
	clkgene_init,
	clkgene_set_parent,
	NULL,
	clkgene_recalc,
	NULL,
	NULL,
	NULL,
	NULL,			/* No measure function */
	NULL			/* No observation point */
);

/* Physical clocks description */
clk_t clk_clocks[] = {
/* Top level clocks */
_CLK(CLK_SYS, &Top, 0,
		CLK_RATE_PROPAGATES | CLK_ALWAYS_ENABLED),
_CLK(CLK_SYSALT, &Top, 0,
		CLK_RATE_PROPAGATES | CLK_ALWAYS_ENABLED),

/* Clockgen A */
_CLK(CLKA_REF, &clkgena, 0,
		CLK_RATE_PROPAGATES | CLK_ALWAYS_ENABLED),
_CLK_P(CLKA_PLL0, &clkgena, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKA_REF]),
_CLK_P(CLKA_PLL0HS, &clkgena, 900000000,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKA_PLL0]),
_CLK_P(CLKA_PLL0LS, &clkgena, 450000000,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKA_PLL0]),
_CLK_P(CLKA_PLL1, &clkgena, 800000000,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKA_REF]),

_CLK(CLKA_IC_STNOC,	&clkgena, 400000000, 0),
_CLK(CLKA_FDMA0,	&clkgena, 400000000, 0),
_CLK(CLKA_FDMA1,	&clkgena, 400000000, 0),
/* Note: CLKA_ETH1_PHY is UNUSED on 7105 */
_CLK(CLKA_ETH1_PHY, &clkgena, 50000000, 0),

_CLK(CLKA_ST40_ICK,	&clkgena, 450000000, CLK_ALWAYS_ENABLED),
_CLK(CLKA_IC_IF_100,	&clkgena, 100000000, CLK_ALWAYS_ENABLED),
_CLK(CLKA_LX_DMU_CPU,	&clkgena, 450000000, 0),
_CLK(CLKA_LX_AUD_CPU,	&clkgena, 450000000, 0),
_CLK(CLKA_IC_BDISP_200, &clkgena, 200000000, 0),
_CLK(CLKA_IC_DISP_200,  &clkgena, 200000000, 0),
_CLK(CLKA_IC_TS_200,	&clkgena, 200000000, 0),
_CLK(CLKA_DISP_PIPE_200, &clkgena, 200000000, 0),
_CLK(CLKA_BLIT_PROC,	&clkgena, 266666666, 0),
_CLK(CLKA_IC_DELTA_200, &clkgena, 266666666, 0),
/* Note: CLKA_ETH0_PHY is named CLKA_ETH_PHY on 7105 datasheet */
_CLK(CLKA_ETH0_PHY,	&clkgena, 25000000,  0),
_CLK(CLKA_PCI,		&clkgena, 66666666,  0),
_CLK(CLKA_EMI_MASTER,	&clkgena, 100000000, 0),
_CLK(CLKA_IC_COMPO_200, &clkgena, 200000000, 0),
_CLK(CLKA_IC_IF_200,	&clkgena, 200000000, CLK_ALWAYS_ENABLED),

/* Clockgen B */
_CLK(CLKB_REF, &clkgenb, 0,
		CLK_RATE_PROPAGATES | CLK_ALWAYS_ENABLED),
_CLK_P(CLKB_FS0, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_REF]),
_CLK_P(CLKB_FS1, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_REF]),
_CLK_P(CLKB_FS0_CH1, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS0]),
_CLK_P(CLKB_FS0_CH2, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS0]),
_CLK_P(CLKB_FS0_CH3, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS0]),
_CLK_P(CLKB_FS0_CH4, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS0]),
_CLK_P(CLKB_FS1_CH1, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS1]),
_CLK_P(CLKB_FS1_CH2, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS1]),
_CLK_P(CLKB_FS1_CH3, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS1]),
_CLK_P(CLKB_FS1_CH4, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS1]),

_CLK_P(CLKB_TMDS_HDMI, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS0_CH1]),
_CLK_P(CLKB_656_1, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS0_CH1]),
_CLK(CLKB_PIX_HD, &clkgenb, 0, CLK_RATE_PROPAGATES),
_CLK_P(CLKB_DISP_HD, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS0_CH1]),
_CLK_P(CLKB_656_0, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS0_CH1]),
_CLK(CLKB_GDP3,		&clkgenb, 0, 0),
_CLK_P(CLKB_DISP_ID, &clkgenb, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKB_FS1_CH1]),
_CLK(CLKB_PIX_SD,	&clkgenb, 0, 0),
_CLK(CLKB_DVP,		&clkgenb, 0, 0),
_CLK(CLKB_PIX_FROM_DVP, &clkgenb, 0, 0),

_CLK_P(CLKB_DSS, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS0_CH1]),
_CLK_P(CLKB_DAA, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS0_CH3]),
_CLK_P(CLKB_PP, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS1_CH3]),
_CLK_P(CLKB_LPC, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS1_CH4]),

/* Note: FS1 CH2 is SPARE on 7105, and CLKB_MMC on 7106 */
_CLK_P(CLKB_MMC, &clkgenb, 0,
		0, &clk_clocks[CLKB_FS1_CH2]),


/* Clockgen C (AUDIO) */
_CLK(CLKC_REF, &clkgenc, 0,
		     CLK_RATE_PROPAGATES | CLK_ALWAYS_ENABLED),
_CLK_P(CLKC_FS0, &clkgenc, 0,
		CLK_RATE_PROPAGATES, &clk_clocks[CLKC_REF]),
_CLK_P(CLKC_FS0_CH1, &clkgenc, 0,
		0, &clk_clocks[CLKC_FS0]),
_CLK_P(CLKC_FS0_CH2, &clkgenc, 0,
		0, &clk_clocks[CLKC_FS0]),
_CLK_P(CLKC_FS0_CH3, &clkgenc, 0,
		0, &clk_clocks[CLKC_FS0]),
_CLK_P(CLKC_FS0_CH4, &clkgenc, 0,
		0, &clk_clocks[CLKC_FS0]),

/* Clockgen D (LMI) */
_CLK(CLKD_REF, &clkgend, 30000000,
		CLK_RATE_PROPAGATES | CLK_ALWAYS_ENABLED),
_CLK_P(CLKD_LMI2X, &clkgend, 800000000,
		0, &clk_clocks[CLKD_REF]),

/* Clockgen E (USB), not really a clockgen */
_CLK(CLKE_REF, &clkgene, 30000000,	 CLK_ALWAYS_ENABLED),

};


GENERIC_LINUX_CLKS(clk_clocks[CLKA_ST40_ICK], /* sh4_clk parent */
		clk_clocks[CLKA_IC_IF_100],   /* module_clk parent */
		clk_clocks[CLKA_IC_IF_100]);

SYSCONF(SYS_STA, 1, 0, 0);
SYSCONF(SYS_CFG, 6, 0, 0);
SYSCONF(SYS_CFG, 11, 1, 8);
SYSCONF(SYS_CFG, 11, 9, 11);
SYSCONF(SYS_CFG, 24, 4, 4);
SYSCONF(SYS_CFG, 40, 0, 0);
SYSCONF(SYS_CFG, 40, 2, 2);
/*
 * The Linux clk_init function
 */
int __init clk_init(void)
{
	int i;

	SYSCONF_CLAIM(SYS_STA, 1, 0, 0);
	SYSCONF_CLAIM(SYS_CFG, 6, 0, 0);
	SYSCONF_CLAIM(SYS_CFG, 11, 1, 8);
	SYSCONF_CLAIM(SYS_CFG, 11, 9, 11);
	SYSCONF_CLAIM(SYS_CFG, 24, 4, 4);
	SYSCONF_CLAIM(SYS_CFG, 40, 0, 0);
	SYSCONF_CLAIM(SYS_CFG, 40, 2, 2);

	for (i = 0; i < CLKB_REF; ++i)
		if (!clk_register(&clk_clocks[i]))
			clk_enable(&clk_clocks[i]);

	REGISTER_GENERIC_LINUX_CLKS();

	return 0;
}

static int __init postcore_clk_init(void)
{
	int i;

	for (i = CLKB_REF; i < ARRAY_SIZE(clk_clocks); ++i)
		if (!clk_register(&clk_clocks[i]))
			clk_enable(&clk_clocks[i]);

	return 0;
}

postcore_initcall(postcore_clk_init);

/******************************************************************************
Top level clocks group
******************************************************************************/

/* ========================================================================
   Name:	clkgentop_init
   Description: Read HW status to initialize 'clk_t' structure.
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgentop_init(clk_t *clk_p)
{
	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	/* Top recalc function */
	switch (clk_p->id) {
	case CLK_SYS:
		clk_p->rate = SYSCLKIN * 1000000;
		break;
	case CLK_SYSALT:
		clk_p->rate = SYSCLKALT * 1000000;
		break;
	}

	return CLK_ERR_NONE;
}

/******************************************************************************
CLOCKGEN A (CPU+interco+comms) clocks group
******************************************************************************/

/* ========================================================================
Name:		clkgena_get_index
Description: Returns index of given clockgenA clock and source reg infos
Returns:	 idx==-1 if error, else >=0
======================================================================== */

static int clkgena_get_index(int clkid, unsigned long *srcreg, int *shift)
{
	int idx;

	/* Warning: This function assumes clock IDs are perfectly
	   following real implementation order. Each "hole" has therefore
	   to be filled with "CLKx_NOT_USED" */
	if (clkid < CLKA_IC_STNOC || clkid > CLKA_IC_IF_200)
		return -1;

	/* Warning: CLKA_BLIT_PROC and CLKA_IC_DELTA_200 have the same index */
	if (clkid >= CLKA_IC_DELTA_200)
		idx = clkid - CLKA_IC_STNOC - 1;
	else
		idx = clkid - CLKA_IC_STNOC;

	if (idx <= 15) {
		*srcreg = CKGA_CLKOPSRC_SWITCH_CFG;
		*shift = idx * 2;
	} else {
		*srcreg = CKGA_CLKOPSRC_SWITCH_CFG2;
		*shift = (idx - 16) * 2;
	}

	return idx;
}

/* ========================================================================
   Name:	clkgena_set_parent
   Description: Set clock source for clockgenA when possible
   Returns:	0=NO error
   ======================================================================== */

static int clkgena_set_parent(clk_t *clk_p, clk_t *src_p)
{
	unsigned long clk_src, val;
	int idx, shift;
	unsigned long srcreg;

	if (!clk_p || !src_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id < CLKA_IC_STNOC || clk_p->id > CLKA_IC_IF_200)
		return CLK_ERR_BAD_PARAMETER;

	switch (src_p->id) {
	case CLKA_REF:
		clk_src = 0;
		break;
	case CLKA_PLL0LS:
	case CLKA_PLL0HS:
		clk_src = 1;
		break;
	case CLKA_PLL1:
		clk_src = 2;
		break;
	default:
		return CLK_ERR_BAD_PARAMETER;
	}

	idx = clkgena_get_index(clk_p->id, &srcreg, &shift);
	if (idx == -1)
		return CLK_ERR_BAD_PARAMETER;

	val = CLK_READ(CKGA_BASE_ADDRESS + srcreg) & ~(0x3 << shift);
	val = val | (clk_src << shift);
	CLK_WRITE(CKGA_BASE_ADDRESS + srcreg, val);

	clk_p->parent = &clk_clocks[src_p->id];

	return clkgena_recalc(clk_p);
}

/* ========================================================================
   Name:	clkgena_identify_parent
   Description: Identify parent clock for clockgen A clocks.
   Returns:	Pointer on parent 'clk_t' structure.
   ======================================================================== */

static int clkgena_identify_parent(clk_t *clk_p)
{
	int idx;
	unsigned long src_sel;
	unsigned long srcreg;
	int shift;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	if (clk_p->id == CLKA_REF) {
		src_sel = SYSCONF_READ(SYS_STA, 1, 0, 0);
		if (src_sel)
			clk_p->parent = &clk_clocks[CLK_SYS];
		else
			clk_p->parent = &clk_clocks[CLK_SYSALT];
		clk_p->rate = clk_p->parent->rate;
		return 0;
	}

	if (clk_p->id < CLKA_IC_STNOC)
		/* statically initialized */
		return 0;

	/* Which divider to setup ? */
	idx = clkgena_get_index(clk_p->id, &srcreg, &shift);
	if (idx == -1)
		return CLK_ERR_BAD_PARAMETER;

	/* Identifying source */
	src_sel = (CLK_READ(CKGA_BASE_ADDRESS + srcreg) >> shift) & 0x3;
	switch (src_sel) {
	case 0:
		clk_p->parent = &clk_clocks[CLKA_REF];
		break;
	case 1:
		if (idx <= 3)
			clk_p->parent = &clk_clocks[CLKA_PLL0HS];
		else
			clk_p->parent = &clk_clocks[CLKA_PLL0LS];
		break;
	case 2:
		clk_p->parent = &clk_clocks[CLKA_PLL1];
		break;
	case 3:
		clk_p->parent = NULL;
		clk_p->rate = 0;
		break;
	}

	return 0;
}

/* ========================================================================
   Name:	clkgena_xable_pll
   Description: Enable/disable PLL
   Returns:	'clk_err_t' error code
   ======================================================================== */

static int clkgena_xable_pll(clk_t *clk_p, int enable)
{
	unsigned long val;
	int bit, data;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	bit = (clk_p->id == CLKA_PLL0 ? 0 : 1);
	val = CLK_READ(CKGA_BASE_ADDRESS + CKGA_POWER_CFG);
	if (enable) {
		val &= ~(1 << bit);
		CLK_WRITE(CKGA_BASE_ADDRESS + CKGA_POWER_CFG, val);
		if (clk_p->id == CLKA_PLL0) {
			clk_p->rate = clk_p->parent->rate;
			return 0;
		}
		data = CLK_READ(CKGA_BASE_ADDRESS + CKGA_PLL1_CFG);
		clk_p->rate = clk_pll800_freq(clk_p->parent->rate, data);
	} else {
		val |= (1 << bit);
		CLK_WRITE(CKGA_BASE_ADDRESS + CKGA_POWER_CFG, val);
		clk_p->rate = 0;
	}

	return 0;
}

/* ========================================================================
   Name:	clkgena_enable
   Description: Enable clock
   Returns:	'clk_err_t' error code
   ======================================================================== */

static int clkgena_enable(clk_t *clk_p)
{
	int err;
	int data;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (!clk_p->parent)
		/* Unsupported. Init must be called first. */
		return CLK_ERR_BAD_PARAMETER;

	/* PLL power up */
	if (clk_p->id == CLKA_PLL0 || clk_p->id == CLKA_PLL1)
		return clkgena_xable_pll(clk_p, 1);

	if (clk_p->id == CLKA_PLL0HS || clk_p->id == CLKA_PLL0LS) {
		if (!clk_p->parent->rate)
			return CLK_ERR_INTERNAL;
		data = CLK_READ(CKGA_BASE_ADDRESS + CKGA_PLL0_CFG);
		clk_p->rate = clk_pll1600_freq(clk_p->parent->rate, data);
		if (clk_p->id == CLKA_PLL0LS)
			clk_p->rate /= 2;
		return 0;
	}

	err = clkgena_set_parent(clk_p, clk_p->parent);
	/* clkgena_set_parent() is performing also a recalc() */

	return err;
}

/* ========================================================================
   Name:	clkgena_disable
   Description: Disable clock
   Returns:	'clk_err_t' error code
   ======================================================================== */

static int clkgena_disable(clk_t *clk_p)
{
	unsigned long val;
	int idx;
	unsigned long srcreg;
	int shift;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	/* PLL power down */
	if (clk_p->id == CLKA_PLL0 || clk_p->id == CLKA_PLL1)
		return clkgena_xable_pll(clk_p, 0);

	if (clk_p->id == CLKA_PLL0HS || clk_p->id == CLKA_PLL0LS)
		return CLK_ERR_BAD_PARAMETER;

	/* Can this clock be disabled ? */
	if (clk_p->flags & CLK_ALWAYS_ENABLED)
		return 0;

	idx = clkgena_get_index(clk_p->id, &srcreg, &shift);
	if (idx == -1)
		return CLK_ERR_BAD_PARAMETER;

	/* Disabling clock */
	val = CLK_READ(CKGA_BASE_ADDRESS + srcreg) & ~(0x3 << shift);
	val = val | (3 << shift);	/* 3 = STOP clock */
	CLK_WRITE(CKGA_BASE_ADDRESS + srcreg, val);
	clk_p->rate = 0;

	return 0;
}

/* ========================================================================
   Name:	clkgena_set_div
   Description: Set divider ratio for clockgenA when possible
   ======================================================================== */

static int clkgena_set_div(clk_t *clk_p, unsigned long *div_p)
{
	int idx;
	unsigned long div_cfg = 0;
	unsigned long srcreg, offset;
	int shift;

	if (!clk_p || !clk_p->parent)
		return CLK_ERR_BAD_PARAMETER;

	/* Computing divider config */
	div_cfg = (*div_p - 1) & 0x1F;

	/* Which divider to setup ? */
	idx = clkgena_get_index(clk_p->id, &srcreg, &shift);
	if (idx == -1)
		return CLK_ERR_BAD_PARAMETER;

	/* Now according to parent, let's write divider ratio */
	offset = clkgena_offset_regs[clk_p->parent->id - CLKA_REF];
	CLK_WRITE(CKGA_BASE_ADDRESS + offset + (4 * idx), div_cfg);

	return 0;
}

/* ========================================================================
   Name:	clkgena_set_rate
   Description: Set clock frequency
   ======================================================================== */

static int clkgena_set_rate(clk_t *clk_p, unsigned long freq)
{
	unsigned long div;
	int err;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if ((clk_p->id < CLKA_PLL0HS) || (clk_p->id > CLKA_IC_IF_200))
		return CLK_ERR_BAD_PARAMETER;

	/* PLL set rate: to be completed */
	if ((clk_p->id >= CLKA_PLL0HS) && (clk_p->id <= CLKA_PLL1))
		return CLK_ERR_BAD_PARAMETER;

	/* We need a parent for these clocks */
	if (!clk_p->parent)
		return CLK_ERR_INTERNAL;

	div = clk_p->parent->rate / freq;
	err = clkgena_set_div(clk_p, &div);
	if (!err)
		clk_p->rate = clk_p->parent->rate / div;

	return err;
}

/* ========================================================================
   Name:	clkgena_recalc
   Description: Get CKGA programmed clocks frequencies
   Returns:	0=NO error
   ======================================================================== */

static int clkgena_recalc(clk_t *clk_p)
{
	unsigned long data, ratio;
	int idx;
	unsigned long srcreg, offset;
	int shift;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (!clk_p->parent)
		return CLK_ERR_INTERNAL;

	/* Reading clock programmed value */
	switch (clk_p->id) {
	case CLKA_REF:  /* Clockgen A reference clock */
	case CLKA_PLL0:	/* Not a clock but a PLL id. Therefore out=in */
		clk_p->rate = clk_p->parent->rate;
		break;

	case CLKA_PLL0HS:
	case CLKA_PLL0LS:
		data = CLK_READ(CKGA_BASE_ADDRESS + CKGA_PLL0_CFG);
		clk_p->rate = clk_pll1600_freq(clk_p->parent->rate, data);
		if (clk_p->id == CLKA_PLL0LS)
			clk_p->rate /= 2;
		break;
	case CLKA_PLL1:
		data = CLK_READ(CKGA_BASE_ADDRESS + CKGA_PLL1_CFG);
		clk_p->rate = clk_pll800_freq(clk_p->parent->rate, data);
		break;

	default:
		idx = clkgena_get_index(clk_p->id, &srcreg, &shift);
		if (idx == -1)
			return CLK_ERR_BAD_PARAMETER;

		/* Now according to source, let's get divider ratio */
		offset = clkgena_offset_regs[clk_p->parent->id - CLKA_REF];
		data = CLK_READ(CKGA_BASE_ADDRESS + offset + (4 * idx));

		ratio = (data & 0x1F) + 1;

		clk_p->rate = clk_p->parent->rate / ratio;
		break;
	}

	return 0;
}

/* ========================================================================
   Name:	clkgena_observe
   Description: allows to observe a clock on a SYSACLK_OUT
   Returns:	0=NO error
   ======================================================================== */

static int clkgena_observe(clk_t *clk_p, unsigned long *div_p)
{
	unsigned long src = 0;
	unsigned long divcfg;
	/* WARNING: the obs_table[] must strictly follows clockgen enum order
	 * taking into account any clock filled with 0xffffffff */
	static const unsigned long obs_table[] = {
		0x8, 0x9, 0xa, 0xffffffff, 0xc, 0xd, 0xe, 0xf, 0x10, 0x11,
		0x12, 0x13, 0x14, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
	};

	if (!clk_p || !div_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id < CLKA_IC_STNOC || clk_p->id > CLKA_IC_IF_200)
		return CLK_ERR_BAD_PARAMETER;

	src = obs_table[clk_p->id - CLKA_IC_STNOC];

	switch (*div_p) {
	case 2:
		divcfg = 0;
		break;
	case 4:
		divcfg = 1;
		break;
	default:
		divcfg = 2;
		*div_p = 1;
		break;
	}
	CLK_WRITE((CKGA_BASE_ADDRESS + CKGA_CLKOBS_MUX1_CFG),
		  (divcfg << 6) | src);

	return 0;
}

/* ========================================================================
   Name:	clkgena_get_measure
   Description: Use internal HW feature (when avail.) to measure clock
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static unsigned long clkgena_get_measure(clk_t *clk_p)
{
	unsigned long src, data;
	unsigned long measure;
	/* WARNING: the measure_table[] must strictly follows clockgen enum
	 * order taking into account any "holes" (CLKA_NOT_USED) filled with
	 * 0xffffffff */
	static const unsigned long measure_table[] = {
		0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10, 0x11,
		0x12, 0x13, 0x14, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
	};

	if (!clk_p)
		return 0;
	if (clk_p->id < CLKA_IC_STNOC || clk_p->id > CLKA_IC_IF_200)
		return 0;

	src = measure_table[clk_p->id - CLKA_IC_STNOC];
	measure = 0;

	/* Loading the MAX Count 1000 in 30MHz Oscillator Counter */
	CLK_WRITE(CKGA_BASE_ADDRESS + CKGA_CLKOBS_MASTER_MAXCOUNT, 0x3E8);
	CLK_WRITE(CKGA_BASE_ADDRESS + CKGA_CLKOBS_CMD, 3);

	/* Selecting clock to observe */
	CLK_WRITE(CKGA_BASE_ADDRESS + CKGA_CLKOBS_MUX1_CFG, (1 << 7) | src);

	/* Start counting */
	CLK_WRITE(CKGA_BASE_ADDRESS + CKGA_CLKOBS_CMD, 0);

	while (1) {
		mdelay(10);
		data = CLK_READ(CKGA_BASE_ADDRESS + CKGA_CLKOBS_STATUS);
		if (data & 1)
			break;	/* IT */
	}

	/* Reading value */
	data = CLK_READ(CKGA_BASE_ADDRESS + CKGA_CLKOBS_SLAVE0_COUNT);
	measure = 30 * data * 1000;

	CLK_WRITE(CKGA_BASE_ADDRESS + CKGA_CLKOBS_CMD, 3);

	return measure;
}

/* ========================================================================
   Name:	clkgena_init
   Description: Read HW status to initialize 'clk_t' structure.
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgena_init(clk_t *clk_p)
{
	int err;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	err = clkgena_identify_parent(clk_p);
	if (!err)
		err = clkgena_recalc(clk_p);

	return err;
}

/******************************************************************************
CLOCKGEN B
******************************************************************************/

static void clkgenb_unlock(void)
{
	CLK_WRITE(CKGB_BASE_ADDRESS + CKGB_LOCK, 0xc0de);
}

static void clkgenb_lock(void)
{
	CLK_WRITE(CKGB_BASE_ADDRESS + CKGB_LOCK, 0xc1a0);
}

/* ========================================================================
   Name:	clkgenb_xable_fsyn
   Description: enable/disable FSYN
   Returns:	0=NO error
   ======================================================================== */

static int clkgenb_xable_fsyn(clk_t *clk_p, unsigned long enable)
{
	unsigned long val, clkout, ctrl;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id == CLKB_FS0) {
		clkout = CKGB_FS0_CLKOUT_CTRL;
		ctrl = CKGB_FS0_CTRL;
	} else if (clk_p->id == CLKB_FS1) {
		clkout = CKGB_FS1_CLKOUT_CTRL;
		ctrl = CKGB_FS1_CTRL;
	} else
		return CLK_ERR_BAD_PARAMETER;

	clkgenb_unlock();

	/* Powering down/up digital part */
	val = CLK_READ(CKGB_BASE_ADDRESS + clkout);
	if (enable)
		val |= 0xF;
	else
		val &= ~0xF;
	CLK_WRITE(CKGB_BASE_ADDRESS + clkout, val);

	/* Powering down/up analog part */
	val = CLK_READ(CKGB_BASE_ADDRESS + ctrl);
	if (enable) {
		val |= (1 << 4);
		clk_p->rate = clk_p->parent->rate;
	} else {
		val &= ~(1 << 4);
		clk_p->rate = 0;
	}

	CLK_WRITE(CKGB_BASE_ADDRESS + ctrl, val);
	clkgenb_lock();
	return 0;
}

/* ========================================================================
   Name:	clkgenb_xable_clock
   Description: Enable/disable clock (Clockgen B)
   Returns:	0=NO error
   ======================================================================== */

struct gen_utility {
	unsigned long clk_id;
	unsigned long info;
};

static int clkgenb_xable_clock(clk_t *clk_p, unsigned long enable)
{
	unsigned long bit, power;
	unsigned long i;
	static const struct gen_utility enable_clock[] = {
		{ CLKB_DAA, 0},		{ CLKB_DSS, 1},
		{ CLKB_PIX_HD, 3},	{ CLKB_DISP_HD, 4 },
		{ CLKB_TMDS_HDMI, 5},
		{ CLKB_656_0, 6},	{ CLKB_GDP3, 7},
		{ CLKB_DISP_ID, 8},	{ CLKB_PIX_SD, 9},
		{ CLKB_656_1, 10},	{ CLKB_PP, 12},
		{ CLKB_LPC, 13},
	};

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	for (i = 0; i < ARRAY_SIZE(enable_clock); ++i)
		if (enable_clock[i].clk_id == clk_p->id)
			break;
	if (i == ARRAY_SIZE(enable_clock))
		return CLK_ERR_BAD_PARAMETER;
	bit = enable_clock[i].info;

	power = CLK_READ(CKGB_BASE_ADDRESS + CKGB_POWER_ENABLE);
	clkgenb_unlock();
	if (enable) {
		power |= (1 << bit);
		clkgenb_recalc(clk_p);
	} else {
		power &= ~(1 << bit);
		clk_p->rate = 0;
	}
	CLK_WRITE(CKGB_BASE_ADDRESS + CKGB_POWER_ENABLE, power);
	clkgenb_lock();

	return 0;
}

/* ========================================================================
   Name:	clkgenb_enable
   Description: enable clock or FSYN (clockgen B)
   Returns:	O=NO error
   ======================================================================== */

static int clkgenb_enable(clk_t *clk_p)
{
	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	if (clk_p->id == CLKB_FS0 || clk_p->id == CLKB_FS1)
		return clkgenb_xable_fsyn(clk_p, 1);

	return clkgenb_xable_clock(clk_p, 1);
}

/* ========================================================================
   Name:		clkgenb_disable
   Description: Disable clock
   Returns:	 O=NO error
   ======================================================================== */

static int clkgenb_disable(clk_t *clk_p)
{
	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	if (clk_p->id == CLKB_FS0 || clk_p->id == CLKB_FS1)
		return clkgenb_xable_fsyn(clk_p, 0);

	return clkgenb_xable_clock(clk_p, 0);
}

/* ========================================================================
   Name:	clkgenb_set_parent
   Description: Set clock source for clockgenB when possible
   Returns:	0=NO error
   ======================================================================== */

static int clkgenb_set_parent(clk_t *clk_p, clk_t *parent_p)
{
	unsigned long set = 0;	/* Each bit set to 1 will be SETTED */
	unsigned long reset = 0;	/* Each bit set to 1 will be RESETTED */
	unsigned long reg;	/* Register address */
	unsigned long val;

	if (!clk_p || !parent_p)
		return CLK_ERR_BAD_PARAMETER;

	reg = CKGB_BASE_ADDRESS + CKGB_FS_SELECT;
	switch (clk_p->id) {
	case CLKB_REF:
		switch (parent_p->id) {
		case CLK_SYS:
			reset = 1;
			break;
		case CLK_SYSALT:
			set = 1;
			break;
		}
		reg = CKGB_BASE_ADDRESS + CKGB_CRISTAL_SEL;
		break;

	case CLKB_GDP3:
		if ((parent_p->id == CLKB_DISP_HD)
		    || (parent_p->id == CLKB_FS0_CH1))
			reset = 1 << 0;
		else
			set = 1 << 0;
		break;

	case CLKB_PIX_SD:
		if (parent_p->id == CLKB_FS0_CH1)
			reset = 1 << 1;
		else
			set = 1 << 1;
		break;

	case CLKB_DVP:
		if (parent_p->id == CLKB_FS0_CH1) {
			set = 1 << 3;
			reset = 1 << 2;
		} else if (parent_p->id == CLKB_FS1_CH1) {
			set = 0x3 << 2;
		} else
			reset = 1 << 3;
		break;

	case CLKB_PIP:
		/* In fact NOT a clockgen B clock but closely linked to it */
		if (parent_p->id == CLKB_DISP_ID)
			val = 0;
		else if (parent_p->id == CLKB_DISP_HD)
			val = 1;
		else
			return CLK_ERR_BAD_PARAMETER;
		SYSCONF_WRITE(SYS_CFG, 6, 0, 0, val);
		clk_p->parent = parent_p;
		/* Special case since config done thru sys_conf register */
		return 0;

	default:
		return CLK_ERR_BAD_PARAMETER;
	}

	clkgenb_unlock();
	val = CLK_READ(reg);
	val = val & ~reset;
	val = val | set;
	CLK_WRITE(reg, val);
	clkgenb_lock();
	clk_p->parent = parent_p;

	return clkgenb_recalc(clk_p);
}

/* ========================================================================
   Name:	clkgenb_set_rate
   Description: Set clock frequency
   ======================================================================== */

static int clkgenb_set_rate(clk_t *clk_p, unsigned long freq)
{
	unsigned long div;
	int err;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	if ((clk_p->id >= CLKB_FS0_CH1) && (clk_p->id <= CLKB_FS1_CH4))
		/* clkgenb_set_fsclock() is updating clk_p->rate */
		return clkgenb_set_fsclock(clk_p, freq);

	if (!clk_p->parent)
		/* A parent is expected to these clocks */
		return(CLK_ERR_INTERNAL);

	div = clk_p->parent->rate / freq;
	err = clkgenb_set_div(clk_p, &div);
	if (!err)
		clk_p->rate = freq;

	return err;
}

/* ========================================================================
   Name:	clkgenb_set_fsclock
   Description: Set FS clock
   Returns:	0=NO error
   ======================================================================== */

static int clkgenb_set_fsclock(clk_t *clk_p, unsigned long freq)
{
	int md, pe, sdiv;
	int bank, channel;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (!clk_p->parent)
		return CLK_ERR_INTERNAL;
	if (clk_p->id < CLKB_FS0_CH1 || clk_p->id > CLKB_FS1_CH4)
		return CLK_ERR_BAD_PARAMETER;

	/* Computing FSyn params. Should be common function with FSyn type */
	if ((clk_fsyn_get_params(clk_p->parent->rate, freq, &md, &pe, &sdiv)) !=
		0)
		return CLK_ERR_BAD_PARAMETER;

	bank = (clk_p->id - CLKB_FS0_CH1) / 4;
	channel = (clk_p->id - CLKB_FS0_CH1) % 4;

	clkgenb_unlock();
	CLK_WRITE(CKGB_BASE_ADDRESS + CKGB_FS_MD(bank, channel), md);
	CLK_WRITE(CKGB_BASE_ADDRESS + CKGB_FS_PE(bank, channel), pe);
	CLK_WRITE(CKGB_BASE_ADDRESS + CKGB_FS_SDIV(bank, channel), sdiv);
	CLK_WRITE(CKGB_BASE_ADDRESS + CKGB_FS_EN_PRG(bank, channel), 0x1);
	clkgenb_lock();
	clk_p->rate = freq;

	return 0;
}

/* ========================================================================
   Name:	clkgenb_set_div
   Description: Set divider ratio for clockgenB when possible
   Returns:	0=NO error
   ======================================================================== */

static int clkgenb_set_div(clk_t *clk_p, unsigned long *div_p)
{
	unsigned long set = 0;	/* Each bit set to 1 will be SETTED */
	unsigned long reset = 0;	/* Each bit set to 1 will be RESETTED */
	unsigned long reg;
	unsigned long val;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	reg = CKGB_DISPLAY_CFG;
	switch (clk_p->id) {
	case CLKB_TMDS_HDMI:
		switch (*div_p) {
		case 2:
			reset = 0x3;
			break;
		case 4:
			reset = 1 << 1;
			set = 1 << 0;
			break;
		case 1024:
			reg = CKGB_POWER_DOWN;
			set = 1 << 1;
			break;
		}
		break;
	case CLKB_656_1:
		switch (*div_p) {
		case 2:
			reset = 0x3 << 2;
			break;
		case 8:
			set = 1 << 3;
			reset = 1 << 2;
			break;
		case 1024:
			reg = CKGB_POWER_DOWN;
			set = 1 << 2;
			break;
		}
		break;
	case CLKB_PIX_HD:
		reg = CKGB_POWER_DOWN;
		if (*div_p == 1024)
			set = 1 << 3;
		else
			reset = 1 << 3;
		break;
	case CLKB_DISP_HD:
		switch (*div_p) {
		case 2:
			reset = 0x3 << 4;
			break;
		case 4:
			reset = 1 << 5;
			set = 1 << 4;
			break;
		case 8:
			set = 1 << 5;
			reset = 1 << 4;
			break;
		case 1024:
			reg = CKGB_POWER_DOWN;
			set = 1 << 4;
			break;
		}
		break;
	case CLKB_656_0:
		switch (*div_p) {
		case 2:
			reset = 0x3 << 6;
			break;
		case 4:
			reset = 1 << 7;
			set = 1 << 6;
			break;
		case 1024:
			reg = CKGB_POWER_DOWN;
			set = 1 << 5;
			break;
		}
		break;
	case CLKB_DISP_ID:
		switch (*div_p) {
		case 2:
			reset = 0x3 << 8;
			break;
		case 1024:
			reg = CKGB_POWER_DOWN;
			set = 1 << 6;
			break;
		}
		break;
	case CLKB_PIX_SD:
		/* clk_pix_sd sourced from Fsyn1 */
		if (CLK_READ(CKGB_BASE_ADDRESS + CKGB_FS_SELECT) & 0x2) {
			switch (*div_p) {
			case 1024:
				reg = CKGB_POWER_DOWN;
				set = 1 << 7;
				break;
			}
		} else {	/* clk_pix_sd sourced from Fsyn0 */
			switch (*div_p) {
			case 4:
				reset = 1 << 11;
				set = 1 << 10;
				break;
			case 8:
				reset = 1 << 10;
				set = 1 << 11;
				break;
			case 1024:
				reg = CKGB_POWER_DOWN;
				set = 1 << 7;
				break;
			}
		}
		break;
	case CLKB_DVP:
		/* clk_dvp sourced from Fsyn1 */
		if (CLK_READ(CKGB_BASE_ADDRESS + CKGB_FS_SELECT) & 0x4) {
		} else {
			switch (*div_p) {
			case 4:
				reset = 1 << 11;
				set = 1 << 10;
				break;
			case 8:
				set = 1 << 11;
				reset = 1 << 10;
				break;
			}
		}
		break;
	default:
		return CLK_ERR_BAD_PARAMETER;
	}

	val = CLK_READ(CKGB_BASE_ADDRESS + reg);
	val = val & ~reset;
	val = val | set;
	clkgenb_unlock();
	CLK_WRITE(CKGB_BASE_ADDRESS + reg, val);
	clkgenb_lock();

	return 0;
}

/* ========================================================================
   Name:	clkgenb_observe
   Description: Allows to observe a clock on a PIO5_2
   Returns:	0=NO error
   ======================================================================== */

static int clkgenb_observe(clk_t *clk_p, unsigned long *div_p)
{
	unsigned long i, out0, out1 = 0;
	static const struct gen_utility observe_table_stx7105[] = {
		{CLKB_TMDS_HDMI, 1},		{CLKB_656_1, 2},
		{CLKB_PIX_HD, 3},		{CLKB_DISP_HD, 4},
		{CLKB_656_0, 5},			{CLKB_GDP3, 6},
		{CLKB_DISP_ID, 7},		{CLKB_PIX_SD, 8},
		{CLKB_DSS, 9},			{CLKB_DAA, 10},
		{CLKB_MMC, 11},		{CLKB_LPC, 13 },
		{CLKB_DVP, 14 },		{CLKB_PP, 22}
	};
	static const struct gen_utility observe_table_stx7106[] = {
		{CLKB_TMDS_HDMI, 1}, {CLKB_656_1, 15},
		{CLKB_PIX_HD, 3}, {CLKB_DISP_HD, 4},
		{CLKB_656_0, 5}, {CLKB_GDP3, 6},
		{CLKB_DISP_ID, 7}, {CLKB_PIX_SD, 8},
		{CLKB_DVP, 14}, {CLKB_DSS, 9},
		{CLKB_DAA, 10}, {CLKB_LPC, 13},
		/* Clocks available thru mux 1 */
		{CLKB_PP, 11}, {CLKB_MMC, 14}
	};
	struct gen_utility *observe_table = observe_table_stx7105;

	if (cpu_data->type != CPU_STX7105)
		observe_table = observe_table_stx7106;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	for (i = 0; i < 14; ++i)
		if (observe_table[i].clk_id == clk_p->id)
			break;

	if (i == 14)
		return CLK_ERR_BAD_PARAMETER;	/* Not found */

	if (clk_p->id == CLKB_PP || clk_p->id == CLKB_MMC) {
		out1 = observe_table[i].info;
		out0 = 12;
	} else
		out0 = observe_table[i].info;

	/* Selecting clock for observation */
	clkgenb_unlock();
	CLK_WRITE((CKGB_BASE_ADDRESS + CKGB_OUT_CTRL), (out1 << 4) | out0);
	clkgenb_lock();

	/* Enabling SYSCLOCKOUT */
	SYSCONF_WRITE(SYS_CFG, 24, 4, 4, 1);

	/* No possible predivider on clockgen B */
	*div_p = 1;

	return 0;
}

/* ========================================================================
   Name:	clkgenb_fsyn_recalc
   Description: Check FSYN & channels status... active, disabled, standbye
		'clk_p->rate' is updated accordingly.
   Returns:	Error code.
   ======================================================================== */

static int clkgenb_fsyn_recalc(clk_t *clk_p)
{
	unsigned long val, clkout, ctrl, bit;
	unsigned long pe, md, sdiv;
	int bank, channel;

	if (!clk_p || !clk_p->parent)
		return CLK_ERR_BAD_PARAMETER;

	/* Which FSYN control registers to use ? */
	switch (clk_p->id) {
	case CLKB_FS0:
	case CLKB_FS0_CH1 ... CLKB_FS0_CH4:
		clkout = CKGB_FS0_CLKOUT_CTRL;
		ctrl = CKGB_FS0_CTRL;
		break;
	case CLKB_FS1:
	case CLKB_FS1_CH1 ... CLKB_FS1_CH4:
		clkout = CKGB_FS1_CLKOUT_CTRL;
		ctrl = CKGB_FS1_CTRL;
		break;
	default:
		return CLK_ERR_BAD_PARAMETER;
	}

	/* Is FSYN analog part UP ? */
	val = CLK_READ(CKGB_BASE_ADDRESS + ctrl);
	if ((val & (1 << 4)) == 0) {	/* NO. Analog part is powered down */
		clk_p->rate = 0;
		return 0;
	}

	/* Is FSYN digital part UP ? */
	switch (clk_p->id) {
	case CLKB_FS0_CH1 ... CLKB_FS1_CH4:
		bit = (clk_p->id - CLKB_FS0_CH1) % 4;
		break;
	default:
		bit = 99;
		break;
	}
	if (bit != 99) {
		val = CLK_READ(CKGB_BASE_ADDRESS + clkout);
		if ((val & (1 << bit)) == 0) {
			/* Digital standbye */
			clk_p->rate = 0;
			return 0;
		}
	}

	/* FSYN is up and running.
	   Now computing frequency */
	switch (clk_p->id) {
	case CLKB_FS0:
	case CLKB_FS1:
		clk_p->rate = clk_p->parent->rate;
		break;

	case CLKB_FS0_CH1 ... CLKB_FS1_CH4:
		bank = (clk_p->id - CLKB_FS0_CH1) / 4;
		channel = (clk_p->id - CLKB_FS0_CH1) % 4;
		pe = CLK_READ(CKGB_BASE_ADDRESS + CKGB_FS_PE(bank, channel));
		md = CLK_READ(CKGB_BASE_ADDRESS + CKGB_FS_MD(bank, channel));
		sdiv = CLK_READ(CKGB_BASE_ADDRESS +
					CKGB_FS_SDIV(bank, channel));
		clk_p->rate = clk_fsyn_get_rate(clk_p->parent->rate, pe,
						md, sdiv);
		break;
	}

	return 0;
}

/* ========================================================================
   Name:	clkgenb_recalc
   Description: Get CKGB clocks frequencies function
   Returns:	0=NO error
   ======================================================================== */

/* Check clock enable value for clockgen B.
   Returns: 1=RUNNING, 0=DISABLED */
static int clkgenb_is_running(unsigned long power, int bit)
{
	if (power & (1 << bit))
		return 1;

	return 0;
}

static int clkgenb_recalc(clk_t *clk_p)
{
	unsigned long displaycfg, powerdown, fs_sel, power;
	static const unsigned int tab2481[] = { 2, 4, 8, 1 };
	static const unsigned int tab2482[] = { 2, 4, 8, 2 };

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (!clk_p->parent)
		return CLK_ERR_INTERNAL;	/* parent_p clock is unknown */

	/* Read mux */
	displaycfg = CLK_READ(CKGB_BASE_ADDRESS + CKGB_DISPLAY_CFG);
	powerdown = CLK_READ(CKGB_BASE_ADDRESS + CKGB_POWER_DOWN);
	fs_sel = CLK_READ(CKGB_BASE_ADDRESS + CKGB_FS_SELECT);
	power = CLK_READ(CKGB_BASE_ADDRESS + CKGB_POWER_ENABLE);

	switch (clk_p->id) {
	case CLKB_FS0:	  /* FSyn 0 power control */
	case CLKB_FS1:	  /* FSyn 1 power control */
	case CLKB_FS0_CH1 ... CLKB_FS1_CH4:
		return clkgenb_fsyn_recalc(clk_p);

	case CLKB_TMDS_HDMI:	/* tmds_hdmi_clk */
		if (powerdown & (1 << 1))
			clk_p->rate = clk_p->parent->rate / 1024;
		else
			clk_p->rate =
			    clk_p->parent->rate / tab2481[displaycfg & 0x3];
		if (!clkgenb_is_running(power, 5))
			clk_p->rate = 0;
		break;

	case CLKB_656_1: /* pix_hdmi */
		if (powerdown & (1 << 2))
			clk_p->rate = clk_p->parent->rate / 1024;
		else
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2481[(displaycfg >> 2) & 0x3];
		if (!clkgenb_is_running(power, 10))
			clk_p->rate = 0;
		break;

	case CLKB_PIX_HD:   /* pix_hd */
		if (!clkgenb_is_running(power, 3))
			clk_p->rate = 0;
		else if (powerdown & (1 << 3))
			clk_p->rate = clk_p->rate / 1024;
		else
			clk_p->rate = clk_p->parent->rate;
		break;

	case CLKB_DISP_HD:	/* disp_hd */
		if (powerdown & (1 << 4))
			clk_p->rate = clk_p->parent->rate / 1024;
		else
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2481[(displaycfg >> 4) & 0x3];
		if (!clkgenb_is_running(power, 4))
			clk_p->rate = 0;
		break;

	case CLKB_656_0:	/* ccir656_clk */
		if (powerdown & (1 << 5))
			clk_p->rate = clk_p->parent->rate / 1024;
		else
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2482[(displaycfg >> 6) & 0x3];
		if (!clkgenb_is_running(power, 6))
			clk_p->rate = 0;
		break;

	case CLKB_DISP_ID:	/* disp_id */
		if (powerdown & (1 << 6))
			clk_p->rate = clk_p->parent->rate / 1024;
		else
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2482[(displaycfg >> 8) & 0x3];
		if (!clkgenb_is_running(power, 8))
			clk_p->rate = 0;
		break;

	case CLKB_PIX_SD:   /* pix_sd */
		if (fs_sel & 0x2) {
			/* source is FS1 */
			if (powerdown & (1 << 7))
				clk_p->rate = clk_p->parent->rate / 1024;
			else
				clk_p->rate =
				    clk_p->parent->rate /
				    tab2481[(displaycfg >> 12) & 0x3];
		} else {
			/* source is FS0 */
			if (powerdown & (1 << 7))
				clk_p->rate = clk_p->parent->rate / 1024;
			else
				clk_p->rate =
				    clk_p->parent->rate /
				    tab2482[(displaycfg >> 10) & 0x3];
		}
		if (!clkgenb_is_running(power, 9))
			clk_p->rate = 0;
		break;

	case CLKB_GDP3:   /* gdp3_clk */
		if (!clkgenb_is_running(power, 7))
			clk_p->rate = 0;
		else if (fs_sel & 0x1) {
			/* Source is FS1. Same clock value than clk_disp_id */
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2482[(displaycfg >> 8) & 0x3];
		} else {
			/* Source is FS0. Same clock value than clk_disp_hd */
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2481[(displaycfg >> 4) & 0x3];
		}
		break;

	case CLKB_DVP:   /* CKGB_DVP */
		switch (clk_p->parent->id) {
		case CLKB_FS0_CH1:
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2482[(displaycfg >> 10) & 0x3];
			break;
		case CLKB_FS1_CH1:
			clk_p->rate =
			    clk_p->parent->rate /
			    tab2481[(displaycfg >> 12) & 0x3];
			break;
		default:	/* pix from pad. Don't have any value */
			break;
		}
		break;

	case CLKB_DSS:
		if (!clkgenb_is_running(power, 0))
			clk_p->rate = 0;
		else
			clk_p->rate = clk_p->parent->rate;
		break;

	case CLKB_DAA:
		if (!clkgenb_is_running(power, 1))
			clk_p->rate = 0;
		else
			clk_p->rate = clk_p->parent->rate;
		break;

	case CLKB_PP:
		if (!clkgenb_is_running(power, 12))
			clk_p->rate = 0;
		else
			clk_p->rate = clk_p->parent->rate;
		break;

	case CLKB_LPC:
		if (!clkgenb_is_running(power, 13))
			clk_p->rate = 0;
		else
			clk_p->rate = clk_p->parent->rate / 1024;
		break;

	case CLKB_SPARE04:
	case CLKB_MMC:
	case CLKB_PIP:
	case CLKB_REF:
		clk_p->rate = clk_p->parent->rate;
		break;

	default:
		return CLK_ERR_BAD_PARAMETER;
	}

	return 0;
}

/* ========================================================================
   Name:	clkgenb_identify_parent
   Description: Identify parent clock
   Returns:	clk_err_t
   ======================================================================== */

static int clkgenb_identify_parent(clk_t *clk_p)
{
	unsigned long sel, fs_sel;
	unsigned long displaycfg;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id < CLKB_REF || clk_p->id > CLKB_MMC)
		return CLK_ERR_BAD_PARAMETER;

	/* Note: Several clocks are statically linked with
	   their parent. This is set thru _CLK_P macro */

	fs_sel = CLK_READ(CKGB_BASE_ADDRESS + CKGB_FS_SELECT);

	switch (clk_p->id) {
	case CLKB_REF:	  /* What is clockgen B ref clock ? */
		sel = CLK_READ(CKGB_BASE_ADDRESS + CKGB_CRISTAL_SEL);
		switch (sel & 0x3) {
		case 0:
			clk_p->parent = &clk_clocks[CLK_SYS];
			break;
		case 1:
			clk_p->parent = &clk_clocks[CLK_SYSALT];
			break;
		default:
			clk_p->parent = NULL;
			break;
		}
		break;

	case CLKB_PIX_HD:   /* pix_hd */
		displaycfg = CLK_READ(CKGB_BASE_ADDRESS + CKGB_DISPLAY_CFG);
		if (displaycfg & (1 << 14)) 	/* pix_hd source = FSYN1 */
			clk_p->parent = &clk_clocks[CLKB_FS1_CH1];
		else	/* pix_hd source = FSYN0 */
			clk_p->parent = &clk_clocks[CLKB_FS0_CH1];
		break;

	case CLKB_PIX_SD:   /* pix_sd */
		if (fs_sel & 0x2)
			/* source is FS1 */
			clk_p->parent = &clk_clocks[CLKB_FS1_CH1];
		else
			/* source is FS0 */
			clk_p->parent = &clk_clocks[CLKB_FS0_CH1];
		break;

	case CLKB_GDP3:   /* gdp3_clk */
		if (fs_sel & 0x1)
			/* source is FS1 */
			clk_p->parent = &clk_clocks[CLKB_FS1_CH1];
		else
			/* source is FS0 */
			clk_p->parent = &clk_clocks[CLKB_FS0_CH1];
		break;

	case CLKB_DVP:   /* CKGB_DVP */
		switch ((fs_sel >> 2) & 0x3) {
		case 0:
		case 1:
			clk_p->parent = &clk_clocks[CLKB_PIX_FROM_DVP];
			break;
		case 2:
			clk_p->parent = &clk_clocks[CLKB_FS0_CH1];
			break;
		case 3:
			clk_p->parent = &clk_clocks[CLKB_FS1_CH1];
			break;
		}
		break;
	}

	return 0;
}

/* ========================================================================
   Name:	clkgenb_init
   Description: Read HW status to initialize 'clk_t' structure.
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgenb_init(clk_t *clk_p)
{
	int err;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	err = clkgenb_identify_parent(clk_p);
	if (!err)
		err = clkgenb_recalc(clk_p);

	return err;
}

/******************************************************************************
CLOCKGEN C (audio)
******************************************************************************/

/* ========================================================================
   Name:	clkgenc_fsyn_recalc
   Description: Get CKGC FSYN clocks frequencies function
   Returns:	0=NO error
   ======================================================================== */

static int clkgenc_fsyn_recalc(clk_t *clk_p)
{
	unsigned long cfg, dig_bit, en_bit;
	unsigned long pe, md, sdiv;
	int channel;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id == CLKC_REF)
		return 0;
	if (clk_p->id == CLKC_FS0) {
		clk_p->rate = clk_p->parent->rate;
		return 0;
	}

	/* Is FSYN analog UP ? */
	cfg = CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS0_CFG);
	if (!(cfg & (1 << 14))) {	/* Analog power down */
		clk_p->rate = 0;
		return 0;
	}

	/* Is FSYN digital part UP & enabled ? */

	dig_bit = 10 + (clk_p->id - CLKC_FS0_CH1);
	en_bit = 6 + (clk_p->id - CLKC_FS0_CH1);

	if ((cfg & (1 << dig_bit)) == 0) {	/* digital part in standbye */
		clk_p->rate = 0;
		return 0;
	}
	if ((cfg & (1 << en_bit)) == 0) {	/* disabled */
		clk_p->rate = 0;
		return 0;
	}

	/* FSYN up & running.
	   Computing frequency */
	channel = (clk_p->id - CLKC_FS0_CH1) % 4;
	pe = CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS_PE(0, channel));
	md = CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS_MD(0, channel));
	sdiv = CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS_SDIV(0, channel));
	clk_p->rate = clk_fsyn_get_rate(clk_p->parent->rate, pe, md, sdiv);

	return 0;
}

/* ========================================================================
   Name:	clkgenc_recalc
   Description: Get CKGC clocks frequencies function
   Returns:	0=NO error
   ======================================================================== */

static int clkgenc_recalc(clk_t *clk_p)
{
	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	switch (clk_p->id) {
	case CLKC_REF:
		clk_p->rate = clk_p->parent->rate;
		break;

	case CLKC_FS0:	  /* FSyn 0 power control => output=input */
	case CLKC_FS0_CH1 ... CLKC_FS0_CH4:  /* FS0 clocks */
		return  clkgenc_fsyn_recalc(clk_p);
	default:
		return CLK_ERR_BAD_PARAMETER;
	}

	return 0;
}

/* ========================================================================
   Name:	clkgenc_set_rate
   Description: Set CKGC clocks frequencies
   Returns:	0=NO error
   ======================================================================== */

static int clkgenc_set_rate(clk_t *clk_p, unsigned long freq)
{
	int md, pe, sdiv;
	unsigned long reg_value = 0;
	int channel;
	static const unsigned long set_rate_table[] =
	    { 0x06, 0x0A, 0x012, 0x022 };

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id < CLKC_FS0_CH1 || clk_p->id > CLKC_FS0_CH4)
		return CLK_ERR_BAD_PARAMETER;

	/* Computing FSyn params. Should be common function with FSyn type */
	if (clk_fsyn_get_params(clk_p->parent->rate, freq, &md, &pe, &sdiv))
		return CLK_ERR_BAD_PARAMETER;

	reg_value = CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS0_CFG);
	channel = (clk_p->id - CLKC_FS0_CH1) % 4;
	reg_value |= set_rate_table[clk_p->id - CLKC_FS0_CH1];

	/* Select FS clock only for the clock specified */
	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS0_CFG, reg_value);

	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS_PE(0, channel), pe);
	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS_MD(0, channel), md);
	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS_SDIV(0, channel), sdiv);
	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS_EN_PRG(0, channel), 0x01);
	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS_EN_PRG(0, channel), 0x00);

	clk_p->rate = freq;

	return 0;
}

/* ========================================================================
   Name:	clkgenc_identify_parent
   Description: Identify parent clock
   Returns:	clk_err_t
   ======================================================================== */

static int clkgenc_identify_parent(clk_t *clk_p)
{
	unsigned long sel;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	if (clk_p->id == CLKC_REF) {
		sel = (CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS0_CFG) >> 23) & 0x3;

		if (cpu_data->type == CPU_STX7106)
			sel = !sel;

		switch (sel) {
		case 0:
			clk_p->parent = &clk_clocks[CLK_SYS];
			break;
		case 1:
			clk_p->parent = &clk_clocks[CLK_SYSALT];
			break;
		default:
			clk_p->parent = NULL;
			break;
		}
	}

	return 0;
}

/* ========================================================================
   Name:	clkgenc_set_parent
   Description: Set parent clock
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgenc_set_parent(clk_t *clk_p, clk_t *parent_p)
{
	unsigned long sel, data;

	if (!clk_p || !parent_p)
		return CLK_ERR_BAD_PARAMETER;

	if (clk_p->id == CLKC_REF) {
		switch (parent_p->id) {
		case CLK_SYS:
			sel = 0;
			break;
		case CLK_SYSALT:
			sel = 1;
			break;
		default:
			return CLK_ERR_BAD_PARAMETER;
		}

		if (cpu_data->type == CPU_STX7106)
			sel = !sel;

		data =
		    CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS0_CFG) & ~(0x3 << 23);
		CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS0_CFG, data | (sel << 23));
		clk_p->parent = parent_p;
	} else
		clk_p->parent = &clk_clocks[CLKC_REF];

	return clkgenc_recalc(clk_p);
}

/* ========================================================================
   Name:	clkgenc_init
   Description: Read HW status to initialize 'clk_t' structure.
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgenc_init(clk_t *clk_p)
{
	int err;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	err = clkgenc_identify_parent(clk_p);
	if (!err)
		err = clkgenc_recalc(clk_p);

	/* In 7106 CLK_SYS is _not_ a reset-default clock source... */
	if (clk_p->id == CLKC_REF && clk_p->parent->id != CLK_SYS)
		clk_set_parent(&clk_clocks[CLKC_REF], &clk_clocks[CLK_SYS]);

	return err;
}

/* ========================================================================
   Name:	clkgenc_enable
   Description: enable clock
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static const unsigned long clkgenc_enable_mask[] =
	{ 0x440, 0x880, 0x1100, 0x2200 };

static int clkgenc_enable(clk_t *clk_p)
{
	unsigned long reg_value = 0;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	reg_value = CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS0_CFG);
	reg_value |= clkgenc_enable_mask[clk_p->id - CLKC_FS0_CH1];

	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS0_CFG, reg_value);
	if ((reg_value & 0x1DC0) && !(reg_value & 0x4000)) {
		reg_value = reg_value | 0x4000;
		CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS0_CFG, reg_value);
	}

	clkgenc_recalc(clk_p);

	return 0;
}

/* ========================================================================
   Name:	clkgenc_disable
   Description: disable clock
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgenc_disable(clk_t *clk_p)
{
	unsigned long reg_value = 0;

	reg_value = CLK_READ(CKGC_BASE_ADDRESS + CKGC_FS0_CFG);
	reg_value &= ~clkgenc_enable_mask[clk_p->id - CLKC_FS0_CH1];

	CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS0_CFG, reg_value);
	if (!(reg_value & 0x1DC0)) {
		reg_value = reg_value & 0xFFFFBFFF;
		CLK_WRITE(CKGC_BASE_ADDRESS + CKGC_FS0_CFG, reg_value);
	}
	clk_p->rate = 0;

	return 0;
}

/******************************************************************************
CLOCKGEN D (LMI)
******************************************************************************/

/* ========================================================================
   Name:	clkgend_recalc
   Description: Get CKGD (LMI) clocks frequencies (in Hz)
   Returns:	0=NO error
   ======================================================================== */

static int clkgend_recalc(clk_t *clk_p)
{
	unsigned long rdiv, ddiv;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	/* Cleaning structure first */
	clk_p->rate = 0;

	if (clk_p->id == CLKD_REF)
		clk_p->rate = clk_p->parent->rate;
	else if (clk_p->id == CLKD_LMI2X) {
		rdiv = SYSCONF_READ(SYS_CFG, 11, 9, 11);
		ddiv = SYSCONF_READ(SYS_CFG, 11, 1, 8);
		clk_p->rate =
		    (((clk_p->parent->rate / 1000000) * ddiv) / rdiv) * 1000000;
	} else
		return CLK_ERR_BAD_PARAMETER;   /* Unknown clock */

	return 0;
}

/* ========================================================================
   Name:	clkgend_identify_parent
   Description: Identify parent clock
   Returns:	clk_err_t
   ======================================================================== */

static int clkgend_identify_parent(clk_t *clk_p)
{
	unsigned long sel;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	if (clk_p->id == CLKD_REF) {
		sel = SYSCONF_READ(SYS_CFG, 40, 0, 0);
		if (sel)
			clk_p->parent = &clk_clocks[CLK_SYS];
		else
			clk_p->parent = &clk_clocks[CLK_SYSALT];
	}

	return 0;
}

/* ========================================================================
   Name:	clkgend_set_parent
   Description: Set parent clock
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgend_set_parent(clk_t *clk_p, clk_t *parent_p)
{
	unsigned long sel;

	if (!clk_p || !parent_p)
		return CLK_ERR_BAD_PARAMETER;

	if (clk_p->id == CLKD_REF) {
		switch (parent_p->id) {
		case CLK_SYS:
			sel = 0;
			break;
		case CLK_SYSALT:
			sel = 1;
			break;
		default:
			return CLK_ERR_BAD_PARAMETER;
		}
		SYSCONF_WRITE(SYS_CFG, 40, 0, 0, sel);
		clk_p->parent = parent_p;
	} else
		clk_p->parent = &clk_clocks[CLKD_REF];

	return clkgend_recalc(clk_p);
}

/* ========================================================================
   Name:	clkgend_init
   Description: Read HW status to initialize 'clk_t' structure.
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgend_init(clk_t *clk_p)
{
	int err;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	err = clkgend_identify_parent(clk_p);
	if (!err)
		err = clkgend_recalc(clk_p);

	return err;
}

/******************************************************************************
CLOCKGEN E (USB)
******************************************************************************/

/* ========================================================================
   Name:	clkgene_recalc
   Description: Get CKGE (USB) clocks frequencies (in Hz)
   Returns:	0=NO error
   ======================================================================== */

static int clkgene_recalc(clk_t *clk_p)
{
	/* Cleaning structure first */
	clk_p->rate = 0;

	if (clk_p->id == CLKE_REF)
		clk_p->rate = clk_p->parent->rate;
	else
		return CLK_ERR_BAD_PARAMETER;   /* Unknown clock */

	return 0;
}

/* ========================================================================
   Name:	clkgene_identify_parent
   Description: Identify parent clock
   Returns:	clk_err_t
   ======================================================================== */

static int clkgene_identify_parent(clk_t *clk_p)
{
	unsigned long sel;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id != CLKE_REF)
		return CLK_ERR_BAD_PARAMETER;

	sel = SYSCONF_READ(SYS_CFG, 40, 2, 2);
	if (sel)
		clk_p->parent = &clk_clocks[CLK_SYS];
	else
		clk_p->parent = &clk_clocks[CLK_SYSALT];

	return 0;
}

/* ========================================================================
   Name:	clkgene_set_parent
   Description: Change parent clock
   Returns:	Pointer on parent 'clk_t' structure, or NULL (none or error)
   ======================================================================== */

static int clkgene_set_parent(clk_t *clk_p, clk_t *parent_p)
{
	unsigned long sel;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;
	if (clk_p->id != CLKE_REF)
		return CLK_ERR_BAD_PARAMETER;

	switch (parent_p->id) {
	case CLK_SYS:
		sel = 0;
		break;
	case CLK_SYSALT:
		sel = 1;
		break;
	default:
		return CLK_ERR_BAD_PARAMETER;
	}
	SYSCONF_WRITE(SYS_CFG, 40, 2, 2, sel);
	clk_p->parent = parent_p;

	return clkgene_recalc(clk_p);
}

/* ========================================================================
   Name:	clkgene_init
   Description: Read HW status to initialize 'clk_t' structure.
   Returns:	'clk_err_t' error code.
   ======================================================================== */

static int clkgene_init(clk_t *clk_p)
{
	int err;

	if (!clk_p)
		return CLK_ERR_BAD_PARAMETER;

	err = clkgene_identify_parent(clk_p);
	if (!err)
		err = clkgene_recalc(clk_p);

	return err;
}
