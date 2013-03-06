/*
 *  sata_stm.c - STMicroelectronics SATA
 *
 *  Copyright 2005 STMicroelectronics Ltd.
 *
 *  The contents of this file are subject to the Open
 *  Software License version 1.1 that can be found at
 *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein
 *  by reference.
 *
 *  Alternatively, the contents of this file may be used under the terms
 *  of the GNU General Public License version 2 (the "GPL") as distributed
 *  in the kernel source COPYING file, in which case the provisions of
 *  the GPL are applicable instead of the above.  If you wish to allow
 *  the use of your version of this file only under the terms of the
 *  GPL and not to allow others to use your version of this file under
 *  the OSL, indicate your decision by deleting the provisions above and
 *  replace them with the notice and other provisions required by the GPL.
 *  If you do not delete the provisions above, a recipient may use your
 *  version of this file under either the OSL or the GPL.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <scsi/scsi.h>
#include <scsi/scsi_host.h>
#include <scsi/scsi_cmnd.h>
#include <linux/libata.h>
#include <linux/stm/soc.h>
#include <linux/stm/pm.h>

#define DRV_NAME			"sata_stm"
#define DRV_VERSION			"0.6"

/* Offsets of the component blocks */
#define SATA_AHB2STBUS_BASE			0x00000000
#define SATA_AHBDMA_BASE			0x00000400
#define SATA_AHBHOST_BASE			0x00000800

/* AHB_STBus protocol converter */
#define SATA_AHB2STBUS_STBUS_OPC		(SATA_AHB2STBUS_BASE + 0x0000)
#define SATA_AHB2STBUS_MESSAGE_SIZE_CONFIG	(SATA_AHB2STBUS_BASE + 0x0004)
#define SATA_AHB2STBUS_CHUNK_SIZE_CONFIG	(SATA_AHB2STBUS_BASE + 0x0008)
#define SATA_AHB2STBUS_SW_RESET			(SATA_AHB2STBUS_BASE + 0x000c)
#define SATA_AHB2STBUS_PC_STATUS		(SATA_AHB2STBUS_BASE + 0x0010)
#define SATA_PC_GLUE_LOGIC			(SATA_AHB2STBUS_BASE + 0x0014)
#define SATA_PC_GLUE_LOGICH			(SATA_AHB2STBUS_BASE + 0x0018)

/* AHB DMA controller */
#define DMAC_SAR0				(SATA_AHBDMA_BASE + 0x00000000)
#define DMAC_DAR0				(SATA_AHBDMA_BASE + 0x00000008)
#define DMAC_LLP0				(SATA_AHBDMA_BASE + 0x00000010)
#define DMAC_CTL0_0				(SATA_AHBDMA_BASE + 0x00000018)
#define DMAC_CTL0_1				(SATA_AHBDMA_BASE + 0x0000001c)
#define DMAC_SSTAT0				(SATA_AHBDMA_BASE + 0x00000020)
#define DMAC_DSTAT0				(SATA_AHBDMA_BASE + 0x00000028)
#define DMAC_SSTATAR0				(SATA_AHBDMA_BASE + 0x00000030)
#define DMAC_DSTATAR0				(SATA_AHBDMA_BASE + 0x00000038)
#define DMAC_CFG0_0				(SATA_AHBDMA_BASE + 0x00000040)
#define DMAC_CFG0_1				(SATA_AHBDMA_BASE + 0x00000044)
#define DMAC_SGR0				(SATA_AHBDMA_BASE + 0x00000048)
#define DMAC_DSR0				(SATA_AHBDMA_BASE + 0x00000050)
#define DMAC_RAWTFR				(SATA_AHBDMA_BASE + 0x000002c0)
#define DMAC_RAWBLOCK				(SATA_AHBDMA_BASE + 0x000002c8)
#define DMAC_RAWSRCTRAN				(SATA_AHBDMA_BASE + 0x000002d0)
#define DMAC_RAWDSTTRAN				(SATA_AHBDMA_BASE + 0x000002d8)
#define DMAC_RAWERR				(SATA_AHBDMA_BASE + 0x000002e0)
#define DMAC_STATUSTFR				(SATA_AHBDMA_BASE + 0x000002e8)
#define DMAC_STATUSBLOCK			(SATA_AHBDMA_BASE + 0x000002f0)
#define DMAC_STATUSSRCTRAN			(SATA_AHBDMA_BASE + 0x000002f8)
#define DMAC_STATUSDSTTRAN			(SATA_AHBDMA_BASE + 0x00000300)
#define DMAC_STATUSERR				(SATA_AHBDMA_BASE + 0x00000308)
#define DMAC_MASKTFR				(SATA_AHBDMA_BASE + 0x00000310)
#define DMAC_MASKBLOCK				(SATA_AHBDMA_BASE + 0x00000318)
#define DMAC_MASKSRCTRAN			(SATA_AHBDMA_BASE + 0x00000320)
#define DMAC_MASKDSTTRAN			(SATA_AHBDMA_BASE + 0x00000328)
#define DMAC_MASKERR				(SATA_AHBDMA_BASE + 0x00000330)
#define DMAC_CLEARTFR				(SATA_AHBDMA_BASE + 0x00000338)
#define DMAC_CLEARBLOCK				(SATA_AHBDMA_BASE + 0x00000340)
#define DMAC_CLEARSRCTRAN			(SATA_AHBDMA_BASE + 0x00000348)
#define DMAC_CLEARDSTTRAN			(SATA_AHBDMA_BASE + 0x00000350)
#define DMAC_CLEARERR				(SATA_AHBDMA_BASE + 0x00000358)
#define DMAC_STATUSINT				(SATA_AHBDMA_BASE + 0x00000360)
#define DMAC_REQSRCREG				(SATA_AHBDMA_BASE + 0x00000368)
#define DMAC_REQDSTREG				(SATA_AHBDMA_BASE + 0x00000370)
#define DMAC_SGLREQSRCREG			(SATA_AHBDMA_BASE + 0x00000378)
#define DMAC_SGLREQDSTREG			(SATA_AHBDMA_BASE + 0x00000380)
#define DMAC_LSTSRCREG				(SATA_AHBDMA_BASE + 0x00000388)
#define DMAC_LSTDSTREG				(SATA_AHBDMA_BASE + 0x00000390)
#define DMAC_DmaCfgReg				(SATA_AHBDMA_BASE + 0x00000398)
#define DMAC_ChEnReg				(SATA_AHBDMA_BASE + 0x000003a0)
#define DMAC_DMAIDREG				(SATA_AHBDMA_BASE + 0x000003a8)
#define DMAC_DMATESTREG				(SATA_AHBDMA_BASE + 0x000003b0)
#define DMAC_DMA_COMP_VERSION			(SATA_AHBDMA_BASE + 0x000003b8)
#define DMAC_COMP_PARAMS_2			(SATA_AHBDMA_BASE + 0x000003e8)
#define DMAC_COMP_TYPE				(SATA_AHBDMA_BASE + 0x000003f8)
#define DMAC_COMP_VERSION			(SATA_AHBDMA_BASE + 0x000003fc)

#define DMAC_CTL_INT_EN			(1<<0)
#define DMAC_CTL_DST_TR_WIDTH_32	(2<<1)
#define DMAC_CTL_SRC_TR_WIDTH_32	(2<<4)
#define DMAC_CTL_DINC_INC		(0<<7)
#define DMAC_CTL_DINC_DEC		(1<<7)
#define DMAC_CTL_DINC_NC		(2<<7)
#define DMAC_CTL_SINC_INC		(0<<9)
#define DMAC_CTL_SINC_DEC		(1<<9)
#define DMAC_CTL_SINC_NC		(2<<9)
#define DMAC_CTL_DEST_MSIZE_1		(0<<11)
#define DMAC_CTL_DEST_MSIZE_4		(1<<11)
#define DMAC_CTL_DEST_MSIZE_8		(2<<11)
#define DMAC_CTL_DEST_MSIZE_16		(3<<11)
#define DMAC_CTL_SRC_MSIZE_1		(0<<14)
#define DMAC_CTL_SRC_MSIZE_4		(1<<14)
#define DMAC_CTL_SRC_MSIZE_8		(2<<14)
#define DMAC_CTL_SRC_MSIZE_16		(3<<14)
#define DMAC_CTL_SRC_GATHER_EN		(1<<17)
#define DMAC_CTL_DST_SCATTER_EN		(1<<18)
#define DMAC_CTL_TT_FC_M2M_DMAC		(0<<20)	/* memory to memory | DMAC */
#define DMAC_CTL_TT_FC_M2P_DMAC		(1<<20)	/* memory to periph | DMAC */
#define DMAC_CTL_TT_FC_P2M_DMAC		(2<<20)	/* periph to memory | DMAC */
#define DMAC_CTL_TT_FC_P2P_DMAC		(3<<20)	/* periph to periph | DMAC */
#define DMAC_CTL_TT_FC_P2M_PER		(4<<20)	/* periph to memory | periph */
#define DMAC_CTL_TT_FC_P2P_SPER		(5<<20)	/* periph to periph | src periph */
#define DMAC_CTL_TT_FC_M2P_PER		(6<<20)	/* memory to periph | periph */
#define DMAC_CTL_TT_FC_P2P_DPER		(7<<20)	/* periph to periph | dest periph */
#define DMAC_CTL_DMS_1		(0<<23)
#define DMAC_CTL_DMS_2		(1<<23)
#define DMAC_CTL_SMS_1		(0<<25)
#define DMAC_CTL_SMS_2		(1<<25)
#define DMAC_CTL_LLP_DST_EN	(1<<27)
#define DMAC_CTL_LLP_SRC_EN	(1<<28)

#define DMAC_CTL_BLOCK_TS	(1<<32)
#define DMAC_CTL_DONE		(1<<44)

#define DMA_CFG_CH_PRIOR_0	(0<<5)
#define DMA_CFG_CH_SUSP		(1<<8)
#define DMA_CFG_FIFO_EMPTY	(1<<9)
#define DMA_CFG_HS_SEL_DST_HW	(0<<10)
#define DMA_CFG_HS_SEL_DST_SW	(1<<10)
#define DMA_CFG_HS_SEL_SRC_HW	(0<<11)
#define DMA_CFG_HS_SEL_SRC_SW	(1<<11)
/*efine DMA_CFG_LOCK_CH_L	(1<<12) not in config */
/*efine DMA_CFG_LOCK_B_L	(1<<14) not in config */
/*efine DMA_CFG_LOCK_CH		(1<<16) not in config */
/*efine DMA_CFG_LOCK_B		(1<<17) not in config */
#define DMA_CFG_DST_HS_POL_HI	(0<<18)
#define DMA_CFG_DST_HS_POL_LO	(1<<18)
#define DMA_CFG_SRC_HS_POL_HI	(0<<19)
#define DMA_CFG_SRC_HS_POL_LO	(1<<19)
#define DMA_CFG_MAX_ABRST_UNLIMITED	(0<<20)
#define DMA_CFG_RELOAD_SRC	(1<<30)
#define DMA_CFG_RELOAD_DST	(1<<31)

#define DMA_CFG_1_FCMODE		(1<<(32-32))
#define DMA_CFG_1_FIFO_MODE		(1<<(33-32))
#define DMA_CFG_1_PROTCTL		(1<<(34-32))
#define DMA_CFG_1_DS_UPD_EN		(1<<(37-32))
/*efine DMA_CFG_1_SS_UPD_EN		(1<<(38-32)) not in config */
#define DMA_CFG_1_SRC_PER_0		(0<<(39-32))
#define DMA_CFG_1_SRC_PER_1		(1<<(39-32))
#define DMA_CFG_1_DEST_PER_0		(0<<(43-32))
#define DMA_CFG_1_DEST_PER_1		(1<<(43-32))

#define DMAC_DmaCfgReg_DMA_EN	(1<<0)

#define DMAC_COMP_PARAMS_2_CH0_HC_LLP	(1<<13)

/* AHB host controller */
#define SATA_CDR0				(SATA_AHBHOST_BASE + 0x00000000)
#define SATA_CDR1				(SATA_AHBHOST_BASE + 0x00000004)
#define SATA_CDR2				(SATA_AHBHOST_BASE + 0x00000008)
#define SATA_CDR3				(SATA_AHBHOST_BASE + 0x0000000c)
#define SATA_CDR4				(SATA_AHBHOST_BASE + 0x00000010)
#define SATA_CDR5				(SATA_AHBHOST_BASE + 0x00000014)
#define SATA_CDR6				(SATA_AHBHOST_BASE + 0x00000018)
#define SATA_CDR7				(SATA_AHBHOST_BASE + 0x0000001c)
#define SATA_CLR0				(SATA_AHBHOST_BASE + 0x00000020)
#define SATA_SCR0				(SATA_AHBHOST_BASE + 0x00000024)
#define SATA_SCR1				(SATA_AHBHOST_BASE + 0x00000028)
#define SATA_SCR2				(SATA_AHBHOST_BASE + 0x0000002c)
#define SATA_SCR3				(SATA_AHBHOST_BASE + 0x00000030)
#define SATA_SCR4				(SATA_AHBHOST_BASE + 0x00000034)
#define SATA_FPTAGR				(SATA_AHBHOST_BASE + 0x00000064)
#define SATA_FPBOR				(SATA_AHBHOST_BASE + 0x00000068)
#define SATA_FPTCR				(SATA_AHBHOST_BASE + 0x0000006c)
#define SATA_DMACR				(SATA_AHBHOST_BASE + 0x00000070)
#define SATA_DBTSR				(SATA_AHBHOST_BASE + 0x00000074)
#define SATA_INTPR				(SATA_AHBHOST_BASE + 0x00000078)
#define SATA_INTMR				(SATA_AHBHOST_BASE + 0x0000007c)
#define SATA_ERRMR				(SATA_AHBHOST_BASE + 0x00000080)
#define SATA_LLCR				(SATA_AHBHOST_BASE + 0x00000084)
#define SATA_PHYCR				(SATA_AHBHOST_BASE + 0x00000088)
#define SATA_PHYSR				(SATA_AHBHOST_BASE + 0x0000008c)
#define SATA_RXBISTPD				(SATA_AHBHOST_BASE + 0x00000090)
#define SATA_RXBISTD1				(SATA_AHBHOST_BASE + 0x00000094)
#define SATA_RXBISTD2				(SATA_AHBHOST_BASE + 0x00000098)
#define SATA_TXBISTPD				(SATA_AHBHOST_BASE + 0x0000009c)
#define SATA_TXBISTD1				(SATA_AHBHOST_BASE + 0x000000a0)
#define SATA_TXBISTD2				(SATA_AHBHOST_BASE + 0x000000a4)
#define SATA_BISTCR				(SATA_AHBHOST_BASE + 0x000000a8)
#define SATA_BISTFCTR				(SATA_AHBHOST_BASE + 0x000000ac)
#define SATA_BISTSR				(SATA_AHBHOST_BASE + 0x000000b0)
#define SATA_BISTDECR				(SATA_AHBHOST_BASE + 0x000000b4)
#define SATA_TESTR				(SATA_AHBHOST_BASE + 0x000000f4)
#define SATA_VERSIONR				(SATA_AHBHOST_BASE + 0x000000f8)
#define SATA_IDR				(SATA_AHBHOST_BASE + 0x000000fc)


#define SATA_DMACR_TXCHEN	(1<<0)
#define SATA_DMACR_RXCHEN	(1<<1)

/* Bit values for SATA_INTPR and SATA_INTMR */
#define SATA_INT_DMAT		(1<<0)
#define SATA_INT_NEWFP		(1<<1)
#define SATA_INT_PMABORT	(1<<2)
#define SATA_INT_ERR		(1<<3)
#define SATA_INT_NEWBIST	(1<<4)

#define SERROR_ERR_T	(1<<8)
#define SERROR_ERR_C	(1<<9)
#define SERROR_ERR_P	(1<<10)
#define SERROR_ERR_E	(1<<11)
#define SERROR_DIAG_N	(1<<16)
#define SERROR_DIAG_X	(1<<26)

#define SATA_FIS_SIZE	(8*1024)

static int stm_sata_scr_read(struct ata_port *ap, unsigned int sc_reg,
			     u32 *val);
static int stm_sata_scr_write(struct ata_port *ap, unsigned int sc_reg,
			      u32 val);

/* Layout of a DMAC Linked List Item (LLI)
 * DMAH_CH0_STAT_DST and DMAH_CH0_STAT_SRC are both 0 */
struct stm_lli {
	u32	sar;
	u32	dar;
	u32	llp;
	u32	ctl0;
	u32	ctl1;
};

struct stm_host_priv
{
	unsigned long phy_init;		/* Initial value for PHYCR */
	int softsg;			/* If using softsg */
	int shared_dma_host_irq;	/* If we the interrupt from the DMA
					 * and HOSTC are or'ed together */
};

struct stm_port_priv
{
	struct stm_lli *lli;		/* Base of the allocated lli nodes */
	dma_addr_t lli_dma;		/* Physical version of lli */
	struct stm_lli *softsg_node;	/* Current softsg node */
	struct stm_lli *softsg_end;	/* End of the softsg node */
	char smallburst;		/* Small DMA burst size */
};

/* There is an undocumented restriction that DMA blocks must not span
 * a FIS boundary. So to ensure we have enough LLIs to cope we restrict
 * the maximum number of sectors, and assume a worst case of one
 * LLI per sector.
 */
#define STM_MAX_SECTORS ATA_MAX_SECTORS
#define STM_MAX_LLIS	ATA_MAX_SECTORS
#define STM_LLI_BYTES	(STM_MAX_LLIS * sizeof(struct stm_lli))

static void stm_phy_configure(struct ata_port *ap)
{
	void __iomem *mmio = ap->ioaddr.cmd_addr;
	struct stm_host_priv *hpriv = ap->host->private_data;

DPRINTK("ENTER\n");

	/*
	 * "sata1hostc Functional Specification" 1.4 defines the PHYCR as:
	 * phy_ctrl[0]     sendalign
	 * phy_ctrl[1]     at
	 * phy_ctrl[4:2]   divdll[2:0]
	 * phy_ctrl[6:5]   txslew[1:0]
	 * phy_ctrl[8:7]   preemph[1:0]
	 * phy_ctrl[10:9]  sdthres[1:0]
	 * phy_ctrl[13:11] swing[2:0]
	 * phy_ctrl[14]    recen
	 * phy_ctrl[15]    ensigdet
	 * phy_ctrl[16]    enasyncdetneg
	 * phy_ctrl[17]    enasyncdetpos
	 * phy_ctrl[18]    startcomzc
	 * phy_ctrl[19]    startcomsr
	 * phy_ctrl[24:20] iddqsub[4:0]
	 * phy_ctrl[31:25] NOT DEFINED
	 */
	if (hpriv->phy_init) {
		writel(hpriv->phy_init, mmio + SATA_PHYCR);
		mdelay(100);
	}
}

/*
 * We have two problems with the interface between the SATA and DMA
 * controllers:
 *  - it can only handle 32 bit quantities
 *  - when reading from the device, if the data returned by the device
 *    is short (ie less than the length programmed into the DMA engine),
 *    and the end of the data doesn't coincide with a DMA burst boundary,
 *    then the DMA will stall, and as a result the end of transfer
 *    interrupt will never be seen.
 */
static int stm_check_atapi_dma(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct stm_port_priv *pp = ap->private_data;
	u8 *scsicmd = qc->scsicmd->cmnd;

	/* Whitelist commands that may use DMA. */
	switch (scsicmd[0]) {
	case WRITE_12:
	case WRITE_10:
	case WRITE_6:
	case READ_12:
	case READ_10:
	case READ_6:
		/* All data is multiples of 2048 */
		pp->smallburst = 0;
		return 0;
	case 0xbe:	/* READ_CD */
		/* Data should be a multiple of four bytes */
		pp->smallburst = 1;
		return 0;
	}

	return 1;
}

static void stm_bmdma_setup(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct stm_port_priv *pp = ap->private_data;
	struct stm_host_priv *hpriv = ap->host->private_data;
	void __iomem *mmio = ap->ioaddr.cmd_addr;
	u32 cfg0, cfg1;

	cfg0 =	DMA_CFG_CH_PRIOR_0		|
		DMA_CFG_HS_SEL_DST_HW		|
		DMA_CFG_HS_SEL_SRC_HW		|
		DMA_CFG_DST_HS_POL_HI		|
		DMA_CFG_SRC_HS_POL_HI		|
		DMA_CFG_MAX_ABRST_UNLIMITED;

	cfg1 =	DMA_CFG_1_FIFO_MODE		|
		DMA_CFG_1_SRC_PER_0		| /* Used on reads */
		DMA_CFG_1_DEST_PER_1;		  /* Used on writes */

	writel(cfg0, mmio + DMAC_CFG0_0);
	writel(cfg1, mmio + DMAC_CFG0_1);

	/* These reads also have the side effect of flushing any posted
	 * writes to the LLI's */
	writel(pp->lli->ctl0, mmio + DMAC_CTL0_0);
	writel(pp->lli->ctl1, mmio + DMAC_CTL0_1);

	if (hpriv->softsg) {
		/* Write the first node into the DMAC registers */
		writel(pp->lli->sar, mmio + DMAC_SAR0);
		writel(pp->lli->dar, mmio + DMAC_DAR0);

		/* Clear interrupt from the final SG node of the
		 * previous transfer */
		writel(1<<0, mmio + DMAC_CLEARTFR);

		/* If there are multiple nodes in the sg list, prepare
		 * to set up subsequent ones in the interrupt handler.
		 */
		if (pp->softsg_node != pp->softsg_end) {
			pp->softsg_node++;
			writel(1<<8 | 1<<0, mmio + DMAC_MASKTFR);
		}
	} else {
		writel(pp->lli_dma, mmio + DMAC_LLP0);
	}

	/* Set Rx and Tx FIFO threshholds to 16 DWORDS except if using
	 * small burst reads, when we set it to 1 DWORD.
	 * Note: this is reset by a COMRESET.
	 */
	if (pp->smallburst) {
		writel((0x1 << 16) | (0x10 << 0), mmio + SATA_DBTSR);
	} else {
		writel((0x10 << 16) | (0x10 << 0), mmio + SATA_DBTSR);
	}

	/* Enable DMA on the SATA host */
	writel(SATA_DMACR_TXCHEN | SATA_DMACR_RXCHEN,
	       mmio + SATA_DMACR);

DPRINTK("SAR %08lx, DAR %08lx, CTL0 %08lx CTL1 %08lx\n",
       readl(mmio + DMAC_SAR0),
       readl(mmio + DMAC_DAR0),
       readl(mmio + DMAC_CTL0_0),
       readl(mmio + DMAC_CTL0_1));
DPRINTK("CFG0 %08lx CFG1 %08lx\n",
       readl(mmio + DMAC_CFG0_0),
       readl(mmio + DMAC_CFG0_1));
DPRINTK("ChEnReg %08lx DmaCfgReg %08lx\n",
       readl(mmio + DMAC_ChEnReg),
       readl(mmio + DMAC_DmaCfgReg));


	/* Enable channel 0 */
	wmb();
	writel((1<<8) | (1<<0), mmio + DMAC_ChEnReg);

	/* issue r/w command */
	ata_exec_command(ap, &qc->tf);
}

static void stm_bmdma_start(struct ata_queued_cmd *qc)
{

#if 0
	void __iomem *mmio = ap->ioaddr.cmd_addr;
	struct ata_port *ap = qc->ap;
	/* Enable channel 0 */
	writel((1<<8) | (1<<0), mmio + DMAC_ChEnReg);
#endif
}

static void stm_bmdma_stop(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	void __iomem *mmio = ap->ioaddr.cmd_addr;

DPRINTK("ENTER\n");

	/*
	 * Chanel is automatically disabled on completion of DMA, however
	 * this also gets called from the timeout handler.
	 */

	/* Disable channel 0 */
	writel((1<<8) | (0<<0), mmio + DMAC_ChEnReg);

	/* Disable DMA on the SATA host */
	writel(0, mmio + SATA_DMACR);

	/* one-PIO-cycle guaranteed wait, per spec, for HDMA1:0 transition */
	ata_altstatus(ap);        /* dummy read */
}

static u8 stm_bmdma_status(struct ata_port *ap)
{
	/* We should be checking here whether the current interrupt
	 * was raised by this SATA host. Unfortuntaly we have no
	 * visibility of the controller's Interrupt Pending Flag (IPF).
	 */
	return ATA_DMA_INTR;
}

static void stm_fill_sg(struct ata_queued_cmd *qc)
{
	struct scatterlist *sg;
	struct ata_port *ap = qc->ap;
	struct stm_host_priv *hpriv = ap->host->private_data;
        struct stm_port_priv *pp = ap->private_data;
	unsigned int write = (qc->tf.flags & ATA_TFLAG_WRITE);
	unsigned int idx;
	u32 sar, dar, ctl0;
	u32 fis_offset;

	DPRINTK("ENTER\n");

	WARN_ON(qc->__sg == NULL);
	WARN_ON(qc->n_elem == 0 && qc->pad_len == 0);

	ctl0 = 	DMAC_CTL_DST_TR_WIDTH_32	|
		DMAC_CTL_SRC_TR_WIDTH_32	|
		DMAC_CTL_DINC_INC		|
		DMAC_CTL_SINC_INC;

	if (write) {
		/* memory (master1) to SATA host (master2) transfer */
		ctl0 |= DMAC_CTL_DEST_MSIZE_4		|
			DMAC_CTL_SRC_MSIZE_16		|
			DMAC_CTL_TT_FC_M2P_DMAC		|
			DMAC_CTL_DMS_2			|
			DMAC_CTL_SMS_1;
	} else {
		/* SATA host (master2) to memory (master1) transfer */
		ctl0 |= DMAC_CTL_DEST_MSIZE_16		|
			(pp->smallburst ?
				DMAC_CTL_SRC_MSIZE_1 :
				DMAC_CTL_SRC_MSIZE_16)	|
			DMAC_CTL_TT_FC_P2M_DMAC		|
			DMAC_CTL_DMS_1			|
			DMAC_CTL_SMS_2;
	}

	if (! hpriv->softsg) {
		ctl0 |= DMAC_CTL_LLP_DST_EN	|
			DMAC_CTL_LLP_SRC_EN;
	}

	idx = 0;
	sar = dar = 0;
	fis_offset = 0;
	ata_for_each_sg(sg, qc) {
		u32 addr;
		u32 sg_len, len;

		addr = sg_dma_address(sg);
		sg_len = sg_dma_len(sg);

		WARN_ON(sg_len & 3);

		while (sg_len) {
			/* Ensure no DMA block crosses a FIS boundary */
			len = sg_len;
			if (len + fis_offset > SATA_FIS_SIZE)
				len = SATA_FIS_SIZE - fis_offset;

			/* SATA host (master2) has a hardwired address of
			 * DMADR, so leave the address set to 0. */
			if (write) {
				sar = addr;
			} else {
				dar = addr;
			}

			pp->lli[idx].sar = sar;
			pp->lli[idx].dar = dar;
			pp->lli[idx].llp = pp->lli_dma +
				(sizeof(struct stm_lli) * (idx+1));
			pp->lli[idx].ctl0 = ctl0;
			pp->lli[idx].ctl1 = len >> 2;

			DPRINTK("lli: %p: SAR %08x, DAR %08x, CTL0 %08x CTL1 %08x\n",
				&pp->lli[idx],
				pp->lli[idx].sar, pp->lli[idx].dar,
				pp->lli[idx].ctl0, pp->lli[idx].ctl1);

			idx++;
			BUG_ON(idx >= STM_MAX_LLIS);
			sg_len -= len;
			addr += len;
			fis_offset = (fis_offset + len) % SATA_FIS_SIZE;
		}
	}

	WARN_ON(idx == 0);
	pp->lli[idx-1].llp = 0;

	if (hpriv->softsg) {
		pp->softsg_node = pp->lli;
		pp->softsg_end  = &pp->lli[idx-1];
	}

}

static void stm_qc_prep(struct ata_queued_cmd *qc)
{
	if (!(qc->flags & ATA_QCFLAG_DMAMAP))
		return;

	stm_fill_sg(qc);
}

static void stm_data_xfer(struct ata_device *adev, unsigned char *buf,
		           unsigned int buflen, int write_data)
{
	struct ata_port *ap = adev->ap;
	unsigned int i;
	unsigned int words = buflen >> 1;
	u16 *buf16 = (u16 *) buf;
	void __iomem *mmio_base = (void __iomem *) ap->ioaddr.cmd_addr;
	void __iomem *mmio = (void __iomem *)ap->ioaddr.data_addr;

	/* Disable error reporting */
	writel(~SERROR_ERR_E, mmio_base + SATA_ERRMR);

	/* Transfer multiple of 2 bytes */
	if (write_data) {
		for (i = 0; i < words; i++) {
			writew(le16_to_cpu(buf16[i]), mmio);
			ndelay(120);
		}
	} else {
		for (i = 0; i < words; i++) {
			buf16[i] = cpu_to_le16(readw(mmio));
			ndelay(120);
		}
	}

	/* Transfer trailing 1 byte, if any. */
	if (unlikely(buflen & 0x01)) {
		u16 align_buf[1] = { 0 };
		unsigned char *trailing_buf = buf + buflen - 1;

		if (write_data) {
			memcpy(align_buf, trailing_buf, 1);
			writew(le16_to_cpu(align_buf[0]), mmio);
		} else {
			align_buf[0] = cpu_to_le16(readw(mmio));
			memcpy(trailing_buf, align_buf, 1);
		}
	}

	/* Clear any errors and re-enable error reporting */
	writel(-1, mmio_base + SATA_SCR1);
	writel(0xffffffff, mmio_base + SATA_ERRMR);
}

static void stm_freeze(struct ata_port *ap)
{
	void __iomem *mmio = ap->ioaddr.cmd_addr;

	/* Disable interrupts */
	writel(0, mmio + SATA_INTMR);
	readl(mmio + SATA_INTMR);	/* flush */
}

static void stm_thaw(struct ata_port *ap)
{
	void __iomem *mmio = ap->ioaddr.cmd_addr;

	/* Reenable interrupts */
	writel(SATA_INT_ERR, mmio + SATA_INTMR);
}

static int stm_prereset(struct ata_port *ap, unsigned long deadline)
{
	stm_phy_configure(ap);
	return ata_std_prereset(ap, deadline);
}

static void stm_postreset(struct ata_port *ap, unsigned int *classes)
{
	void __iomem *mmio = ap->ioaddr.cmd_addr;

	/* Enable notification of errors. These are reset by COMRESET. */
	writel(0xffffffff, mmio + SATA_ERRMR);
	writel(SATA_INT_ERR, mmio + SATA_INTMR);

	ata_std_postreset(ap, classes);
}

static void stm_error_handler(struct ata_port *ap)
{
        ata_do_eh(ap, stm_prereset, ata_std_softreset,
                  sata_std_hardreset, stm_postreset);
}

static void stm_post_internal_cmd(struct ata_queued_cmd *qc)
{
	stm_bmdma_stop(qc);
}

/* This needs munging to give per controller stats */
static unsigned long error_count;
static unsigned int print_error=1;

static unsigned stm_sata_dma_irq(struct ata_port *ap)
{
	void __iomem *mmio = ap->ioaddr.cmd_addr;
	struct stm_port_priv *pp = ap->private_data;
	int handled = 1;

	if (readl(mmio + DMAC_STATUSTFR) & 1) {
		/* DMA Transfer complete update soft S/G */

		/* Ack the interrupt */
		writel(1<<0, mmio + DMAC_CLEARTFR);

		DPRINTK("softsg_node %p, end %p\n",
			pp->softsg_node, pp->softsg_end);

		writel(pp->softsg_node->sar, mmio + DMAC_SAR0);
		writel(pp->softsg_node->dar, mmio + DMAC_DAR0);

		writel(pp->softsg_node->ctl0, mmio + DMAC_CTL0_0);
		writel(pp->softsg_node->ctl1, mmio + DMAC_CTL0_1);

		if (pp->softsg_node != pp->softsg_end) {
			pp->softsg_node++;
		} else {
			writel(1<<8 | 0<<0, mmio + DMAC_MASKTFR);
		}

		writel((1<<8) | (1<<0), mmio + DMAC_ChEnReg);
	} else if (readl(mmio + DMAC_RAWERR) & 1) {
		ata_port_printk(ap, KERN_ERR, "DMA error asserted\n");
	}

	return handled;

}

static unsigned stm_sata_host_irq(struct ata_port *ap)
{
	unsigned int handled = 0;
	void __iomem *mmio = ap->ioaddr.cmd_addr;
	struct ata_eh_info *ehi = &ap->eh_info;
	u32 sstatus, serror;

	if (readl(mmio + SATA_INTPR) & (SATA_INT_ERR)) {

		stm_sata_scr_read(ap, SCR_STATUS, &sstatus);
		stm_sata_scr_read(ap, SCR_ERROR, &serror);
		stm_sata_scr_write(ap, SCR_ERROR, serror);

		if (print_error)
			ata_port_printk(ap, KERN_ERR,
					"SStatus 0x%08x, SError 0x%08x\n",
					sstatus, serror);
		error_count++;

		ata_ehi_clear_desc(ehi);
		ata_ehi_push_desc(ehi, "SStatus 0x%08x, SError 0x%08x",
				  sstatus, serror);
		ehi->serror |= serror;

		if (serror & (SERROR_DIAG_N | SERROR_DIAG_X)) {
			ata_ehi_hotplugged(&ap->eh_info);
			ata_ehi_push_desc(ehi, "Treating as hot-%splug",
					  serror & SERROR_DIAG_X ? "" : "un");
		}

		ata_port_freeze(ap);
		handled = 1;
	} else
		if (ap && (!(ap->flags & ATA_FLAG_DISABLED))) {
			struct ata_queued_cmd *qc;

			qc = ata_qc_from_tag(ap, ap->active_tag);
			if (qc && (!(qc->tf.ctl & ATA_NIEN)))
				handled += ata_host_intr(ap, qc);
		}

	return handled;
}

static irqreturn_t stm_sata_dma_interrupt(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	unsigned int handled = 0;
	unsigned int i;
	unsigned long flags;
	struct stm_host_priv *hpriv = host->private_data;

DPRINTK("ENTER DMA\n");

	BUG_ON(hpriv->shared_dma_host_irq);

	spin_lock_irqsave(&host->lock, flags);

	for (i = 0; i < host->n_ports; i++)
		handled += stm_sata_dma_irq(host->ports[i]);

	spin_unlock_irqrestore(&host->lock, flags);

	return IRQ_RETVAL(handled);
}

static irqreturn_t stm_sata_interrupt(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	unsigned int handled = 0;
	unsigned int i;
	unsigned long flags;
	struct stm_host_priv *hpriv = host->private_data;

DPRINTK("ENTER\n");

	spin_lock_irqsave(&host->lock, flags);

	for (i = 0; i < host->n_ports; i++) {
		if (hpriv->shared_dma_host_irq)
			handled += stm_sata_dma_irq(host->ports[i]);
		handled += stm_sata_host_irq(host->ports[i]);
	}

	spin_unlock_irqrestore(&host->lock, flags);

	return IRQ_RETVAL(handled);
}

static void stm_irq_clear(struct ata_port *ap)
{
	/* TODO */
}

static int stm_sata_scr_read(struct ata_port *ap, unsigned int sc_reg, u32 *val)
{
	void __iomem *mmio = ap->ioaddr.cmd_addr;

	if (sc_reg > SCR_CONTROL) return -EINVAL;

	*val = readl(mmio + SATA_SCR0 + (sc_reg * 4));
	return 0;
}

static int stm_sata_scr_write(struct ata_port *ap, unsigned int sc_reg, u32 val)
{
	void __iomem *mmio = ap->ioaddr.cmd_addr;

DPRINTK("%d = %08x\n", sc_reg, val);
	if (sc_reg > SCR_CONTROL) return -EINVAL;

	writel(val, mmio + SATA_SCR0 + (sc_reg * 4));
	return 0;
}

static int stm_port_start (struct ata_port *ap)
{
	struct device *dev = ap->host->dev;
	struct stm_host_priv *hpriv = ap->host->private_data;
	struct stm_port_priv *pp;
	int rc;

	pp = devm_kzalloc(dev, sizeof(*pp), GFP_KERNEL);
	if (pp == NULL)
		return -ENOMEM;

	if (hpriv->softsg) {
		pp->lli = devm_kzalloc(dev, STM_LLI_BYTES, GFP_KERNEL);
	} else {
		pp->lli = dmam_alloc_coherent(dev, STM_LLI_BYTES, &pp->lli_dma,
					      GFP_KERNEL);
	}

	if (pp->lli == NULL)
		return -ENOMEM;

	pp->smallburst = 0;

	rc = ata_pad_alloc(ap, dev);
	if (rc)
		return rc;

	ap->private_data = pp;

	return 0;
}

static ssize_t stm_show_serror(struct class_device *class_dev, char *buf)
{
	//struct Scsi_Host *host = class_to_shost(class_dev);
	ssize_t len;

	len = snprintf(buf, PAGE_SIZE, "%ld\n", error_count);
	return len;
}

static ssize_t stm_store_serror(struct class_device * class_dev,
			       const char * buf, size_t count)
{
	// struct Scsi_Host *host = class_to_shost(class_dev);

	error_count = simple_strtoul(buf, NULL, 10);
	return count;
}

static struct class_device_attribute stm_host_stats_attr = {
	.attr = {
		.name =		"serror",
		.mode =		S_IRUGO | S_IWUGO,
	},
	.show = stm_show_serror,
	.store = stm_store_serror,
};

static ssize_t stm_show_printerror(struct class_device *class_dev, char *buf)
{
	//struct Scsi_Host *host = class_to_shost(class_dev);
	ssize_t len;

	len = snprintf(buf, PAGE_SIZE, "%d\n", print_error);
	return len;
}

static ssize_t stm_store_printerror(struct class_device * class_dev,
			       const char * buf, size_t count)
{
	// struct Scsi_Host *host = class_to_shost(class_dev);

	print_error = simple_strtoul(buf, NULL, 10);
	return count;
}

static struct class_device_attribute stm_host_printerror_attr = {
	.attr = {
		.name =		"printerror",
		.mode =		S_IRUGO | S_IWUGO,
	},
	.show = stm_show_printerror,
	.store = stm_store_printerror,
};

/* Host attributes initializer */
static struct class_device_attribute *stm_host_attrs[] = {
	&stm_host_stats_attr,
	&stm_host_printerror_attr,
	NULL,
};

static struct scsi_host_template stm_sht = {
	.module			= THIS_MODULE,
	.name			= DRV_NAME,
	.ioctl			= ata_scsi_ioctl,
	.queuecommand		= ata_scsi_queuecmd,
	.can_queue		= ATA_DEF_QUEUE,
	.this_id		= ATA_SHT_THIS_ID,
	.sg_tablesize		= LIBATA_MAX_PRD,
	.max_sectors		= STM_MAX_SECTORS,
	.cmd_per_lun		= ATA_SHT_CMD_PER_LUN,
	.emulated		= ATA_SHT_EMULATED,
	.use_clustering		= ATA_SHT_USE_CLUSTERING,
	.proc_name		= DRV_NAME,
	.dma_boundary		= ATA_DMA_BOUNDARY,
	.slave_configure	= ata_scsi_slave_config,
	.slave_destroy		= ata_scsi_slave_destroy,
	.bios_param		= ata_std_bios_param,
	.shost_attrs		= stm_host_attrs,
};

static struct ata_port_operations stm_ops = {
	.port_disable		= ata_port_disable,
	.tf_load		= ata_tf_load,
	.tf_read		= ata_tf_read,
	.check_status		= ata_check_status,
	.exec_command		= ata_exec_command,
	.dev_select		= ata_noop_dev_select,
	.check_atapi_dma	= stm_check_atapi_dma,
	.bmdma_setup		= stm_bmdma_setup,
	.bmdma_start		= stm_bmdma_start,
	.bmdma_stop		= stm_bmdma_stop,
	.bmdma_status		= stm_bmdma_status,
	.qc_prep		= stm_qc_prep,
	.qc_issue		= ata_qc_issue_prot,
	.data_xfer		= stm_data_xfer,
	.freeze			= stm_freeze,
	.thaw			= stm_thaw,
	.error_handler		= stm_error_handler,
	.post_internal_cmd	= stm_post_internal_cmd,
	.irq_clear		= stm_irq_clear,
	.irq_on			= ata_dummy_irq_on,
	.scr_read		= stm_sata_scr_read,
	.scr_write		= stm_sata_scr_write,
	.port_start		= stm_port_start,
};

static const struct ata_port_info stm_port_info = {
	.flags		= ATA_FLAG_SATA | ATA_FLAG_NO_LEGACY |
			  ATA_FLAG_MMIO | ATA_FLAG_SATA_RESET,
	.pio_mask	= 0x1f, /* pio0-4 */
	.mwdma_mask	= 0x07, /* mwdma0-2 */
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &stm_ops,
};

static unsigned char stm_readb(const volatile void __iomem *addr)
{
	return readl(addr);
}

static unsigned short stm_readw(const volatile void __iomem *addr)
{
	return readl(addr);
}

static void stm_writeb(unsigned char b, volatile void __iomem *addr)
{
	writel(b, addr);
}

static void stm_writew(unsigned short b, volatile void __iomem *addr)
{
	writel(b, addr);
}

static int __devinit stm_sata_probe(struct platform_device *pdev)
{
	struct plat_sata_data *sata_private_info = pdev->dev.platform_data;
	struct device *dev = &pdev->dev;
	struct resource *mem_res;
	unsigned long phys_base, phys_size;
	void __iomem *mmio_base;
	const struct ata_port_info *ppi[] = { &stm_port_info, NULL };
	struct ata_host *host;
	struct ata_port *ap;
	struct stm_host_priv *hpriv = NULL;
	unsigned long sata_rev, dmac_rev;
	int dma_irq;
	int ret;


	printk(KERN_DEBUG DRV_NAME " version " DRV_VERSION "\n");

	host = ata_host_alloc_pinfo(dev, ppi, 1);
	if (!host)
		return -ENOMEM;

	hpriv = devm_kzalloc(dev, sizeof(*hpriv), GFP_KERNEL);
	if (!hpriv)
		return -ENOMEM;

        host->private_data = hpriv;

	mem_res = platform_get_resource(pdev,IORESOURCE_MEM,0);
	phys_base = mem_res->start;
	phys_size = mem_res->end - mem_res->start + 1;

	if (!devm_request_mem_region(dev, phys_base, phys_size, "STM SATA"))
		return -EBUSY;

	mmio_base = devm_ioremap(dev, phys_base, phys_size);
	if (mmio_base == NULL)
		return ENOMEM;

	/* Set up the ports */
	ap = host->ports[0];
	ap->ioaddr.cmd_addr		= mmio_base;
	ap->ioaddr.data_addr		= mmio_base + SATA_CDR0;
	ap->ioaddr.error_addr		= mmio_base + SATA_CDR1;
	ap->ioaddr.feature_addr		= mmio_base + SATA_CDR1;
	ap->ioaddr.nsect_addr		= mmio_base + SATA_CDR2;
	ap->ioaddr.lbal_addr		= mmio_base + SATA_CDR3;
	ap->ioaddr.lbam_addr		= mmio_base + SATA_CDR4;
	ap->ioaddr.lbah_addr		= mmio_base + SATA_CDR5;
	ap->ioaddr.device_addr		= mmio_base + SATA_CDR6;
	ap->ioaddr.status_addr		= mmio_base + SATA_CDR7;
	ap->ioaddr.command_addr		= mmio_base + SATA_CDR7;

	ap->ioaddr.altstatus_addr	= mmio_base + SATA_CLR0;
	ap->ioaddr.ctl_addr		= mmio_base + SATA_CLR0;

	hpriv->phy_init = sata_private_info->phy_init;
	hpriv->softsg = readl(mmio_base + DMAC_COMP_PARAMS_2) &
		DMAC_COMP_PARAMS_2_CH0_HC_LLP;
	//hpriv->softsg = 1;

	printk(KERN_DEBUG DRV_NAME " using %sware scatter/gather\n",
	       hpriv->softsg ? "soft" : "hard");

	if (sata_private_info->only_32bit) {
		printk(KERN_DEBUG DRV_NAME " forcing all byte/word ops to long\n");
		stm_ops.readb = stm_readb;
		stm_ops.readw = stm_readw;
		stm_ops.writeb = stm_writeb;
		stm_ops.writew = stm_writew;
	}

	sata_rev = readl(mmio_base + SATA_VERSIONR);
	dmac_rev = readl(mmio_base + DMAC_COMP_VERSION);
	printk(KERN_DEBUG DRV_NAME " SATA version %c.%c%c DMA version %c.%c%c\n",
	       (int)(sata_rev >> 24) & 0xff,
	       (int)(sata_rev >> 16) & 0xff,
	       (int)(sata_rev >>  8) & 0xff,
	       (int)(dmac_rev >> 24) & 0xff,
	       (int)(dmac_rev >> 16) & 0xff,
	       (int)(dmac_rev >>  8) & 0xff);

	/* AHB bus wrapper setup */

        // SATA_AHB2STBUS_STBUS_OPC
        // 2:0  -- 100 = Store64/Load64
        // 4    -- 1   = Enable write posting
	// DMA Read, write posting always = 0
	/* opcode = Load4 |Store 4*/
	writel(3, mmio_base + SATA_AHB2STBUS_STBUS_OPC);

        // SATA_AHB2STBUS_MESSAGE_SIZE_CONFIG
        // 3:0  -- 0111 = 128 Packets
        // 3:0  -- 0110 =  64 Packets
	/* WAS: Message size = 64 packet when 6 now 3*/
	writel(3, mmio_base + SATA_AHB2STBUS_MESSAGE_SIZE_CONFIG);

        // SATA_AHB2STBUS_CHUNK_SIZE_CONFIG
        // 3:0  -- 0110 = 64 Packets
        // 3:0  -- 0001 =  2 Packets
	/* WAS Chunk size = 2 packet when 1, now 0 */
	writel(2, mmio_base + SATA_AHB2STBUS_CHUNK_SIZE_CONFIG);

        // PC_GLUE_LOGIC
        // 7:0  -- 0xFF = Set as reset value, 256 STBus Clock Cycles
        // 8    -- 1  = Time out enabled
	// (has bit 8 moved to bit 16 on 7109 cut2?)
	/* time out count = 0xa0(160 dec)
	 * time out enable = 1
	 */
	if (sata_private_info->pc_glue_logic_init)
		writel(sata_private_info->pc_glue_logic_init,
		       mmio_base + SATA_PC_GLUE_LOGIC);

	/* DMA controller set up */

	/* Enable DMA controller */
	writel(DMAC_DmaCfgReg_DMA_EN, mmio_base + DMAC_DmaCfgReg);

	/* Clear initial Serror */
	writel(-1, mmio_base + SATA_SCR1);

	/* Finished hardware set up */

	/* Now, are we on one of the later SATA IP's, we have the DMA and
	 * host controller interrupt lines separated out. So if we have two
	 * irq resources, then it is one of these
	 */

	dma_irq = platform_get_irq(pdev, 1);
	if (dma_irq > 0) {
		/* We have two interrupts */
		if (devm_request_irq(host->dev, dma_irq, stm_sata_dma_interrupt,
				     0, dev_driver_string(host->dev), host) < 0)
			panic("Cannot register SATA dma interrupt %d\n",
			      dma_irq);
		hpriv->shared_dma_host_irq = 0;
	} else {
		hpriv->shared_dma_host_irq = 1;
	}

	ret = ata_host_activate(host, platform_get_irq(pdev, 0),
				stm_sata_interrupt,
				IRQF_SHARED, &stm_sht);

	if (ret && dma_irq > 0)
		devm_free_irq(host->dev, dma_irq, host);

	return ret;

}

static int stm_sata_remove(struct platform_device *pdev)
{
	return 0;
}

#ifdef CONFIG_PM
static int stm_sata_suspend(struct platform_device *pdev, pm_message_t state)
{
	if (state.event == PM_EVENT_SUSPEND) {
		platform_pm_pwdn_req(pdev, HOST_PM, 1);
		platform_pm_pwdn_ack(pdev, HOST_PM, 1);
		}
	return 0;
}

static int stm_sata_resume(struct platform_device *pdev)
{
	platform_pm_pwdn_req(pdev, HOST_PM, 0);
	platform_pm_pwdn_ack(pdev, HOST_PM, 0);
	return 0;
}
#else
#define stm_sata_suspend	NULL
#define stm_sata_resume		NULL
#endif

static struct platform_driver stm_sata_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = stm_sata_probe,
	.remove = stm_sata_remove,
	.suspend = stm_sata_suspend,
	.resume = stm_sata_resume,
};

static int __init stm_sata_init(void)
{
	return platform_driver_register(&stm_sata_driver);
}

static void __exit stm_sata_exit(void)
{
	platform_driver_unregister(&stm_sata_driver);
}

module_init(stm_sata_init);
module_exit(stm_sata_exit);

MODULE_AUTHOR("Stuart Menefy");
MODULE_DESCRIPTION("low-level driver for STMicroelectronics SATA");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
