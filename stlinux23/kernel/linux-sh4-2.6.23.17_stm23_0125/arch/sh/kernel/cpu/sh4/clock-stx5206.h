/*****************************************************************************
 *
 * File name   : clock-stx5206.h
 * Description : Low Level API - Clocks identifiers
 * Component   : STCLOCK
 * Module	  :
 *
 * COPYRIGHT (C) 2009 STMicroelectronics - All Rights Reserved
 * May be copied or modified under the terms of the GNU General Public
 * License.  See linux/COPYING for more information.
 *
 *****************************************************************************/

enum {
	/* Top level clocks */
	CLK_SYS,	/* SYSA_CLKIN/FE input clock */
	CLK_SYSALT,	/* Optional alternate input clock */

	/* Clockgen A */
	CLKA_REF,	/* Clockgen A reference clock = OSC clock */
	CLKA_PLL0,	/* PLL0 power control */
	CLKA_PLL0HS,	/* PLL0 HS output */
	CLKA_PLL0LS,	/* PLL0 LS output */
	CLKA_PLL1,	/* PLL1 power control & output clock */

	CLKA_IC_STNOC,	/* HS[0] */
	CLKA_FDMA0,
	CLKA_FDMA1,	/* Unused */
	CLKA_PP,	/* HS[3] */
	CLKA_SH4_ICK,	/* LS[4] */
	CLKA_IC_IF_100,
	CLKA_LX_DMU_CPU,
	CLKA_LX_AUD_CPU,
	CLKA_IC_BDISP_200,
	CLKA_IC_DISP_200,
	CLKA_IC_TS_200,
	CLKA_DISP_PIPE_200,
	CLKA_BLIT_PROC,
	CLKA_IC_DELTA_200,  /* Same clock than CLKA_BLIT_PROC */
	CLKA_ETH_PHY,
	CLKA_PCI,
	CLKA_EMI_MASTER,
	CLKA_IC_COMPO_200,
	CLKA_IC_IF_200,

	/* Clockgen B */
	CLKB_REF,	/* Clockgen B reference clock */
	CLKB_FS0,	/* FSYN 0 power control */
	CLKB_FS1,	/* FSYN 1 power control */

	CLKB_FS0_CH1,
	CLKB_FS0_CH2,
	CLKB_FS0_CH3,
	CLKB_FS0_CH4,

	CLKB_FS1_CH1,
	CLKB_FS1_CH2,
	CLKB_FS1_CH3,
	CLKB_FS1_CH4,

	CLKB_SRC_ED,
	CLKB_DSS,
	CLKB_DAA,
	CLKB_27_0,	/* Spare FS0, CH4 */
	CLKB_SRC_SD,
	CLKB_27_1,	/* Spare FS1, CH2 */
	CLKB_MMC,
	CLKB_LPC,

	/*
	* The following 7 clocks are _NOT_ in clockgenB.
	* Sourced from clk_disp_sd or clk_disp_hd
	*/
	CLKB_PIX_ED,
	CLKB_DISP_ED,
	CLKB_PIX_SD,
	CLKB_DISP_SD,
	CLKB_656,
	CLKB_GDP1,
	CLKB_PIP,

	/* Clockgen C (Audio) */
	CLKC_REF,
	CLKC_FS0,	   /* FSYN 0 power control */
	CLKC_FS0_CH1,
	CLKC_FS0_CH2,
	CLKC_FS0_CH3,
	CLKC_FS0_CH4,

	/* Clockgen D */
	CLKD_REF,	/* Clockgen D reference clock */
	CLKD_LMI2X,

	/* Clockgen E = USB PHY */
	CLKE_REF,	/* Clockgen E reference clock */

};
