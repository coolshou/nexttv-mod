/*
 * (C) Copyright 2007,2009 STMicroelectronics.
 *
 * Sean McGoogan <Sean.McGoogan@st.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/soc.h>
#include <asm/socregs.h>
#include <asm/io.h>
#include <spi.h>
#include <asm/clk.h>


/**********************************************************************/


#if defined(CONFIG_SPI)


/**********************************************************************/


#if !defined(CONFIG_SOFT_SPI)			/* Use SSC for SPI */
/* SSC Baud Rate Generator Register */
#define SSC_BRG			0x0000

/* SSC Transmit Buffer Register */
#define SSC_TBUF		0x0004

/* SSC Receive Buffer Register */
#define SSC_RBUF		0x0008

/* SSC Control Register */
#define SSC_CON			0x000C
#define SSC_CON_HB		(1ul<<4)	/* endianness */
#define SSC_CON_PH		(1ul<<5)	/* clock phase */
#define SSC_CON_PO		(1ul<<6)	/* clock polarity */
#define SSC_CON_SR		(1ul<<7)	/* SSC software reset */
#define SSC_CON_MS		(1ul<<8)	/* master/slave select */
#define SSC_CON_EN		(1ul<<9)	/* SSC enable */
#define SSC_CON_LPB		(1ul<<10)	/* SSC loopback mode */
#define SSC_CON_TXFIFO		(1ul<<11)	/* transmit-side FIFO */
#define SSC_CON_RXFIFO		(1ul<<12)	/* receive-side FIFO */
#define SSC_CON_CLSTRX		(1ul<<13)	/* clock stretch mechanism */

/* SSC Interrupt Enable Register */
#define SSC_IEN			0x0010

/* SSC Status Register */
#define SSC_STAT		0x0014
#define SSC_STAT_RIR		(1ul<<0)	/* receive buffer full flag */
#define SSC_STAT_TIR		(1ul<<1)	/* transmit buffer empty flag */
#define SSC_STAT_TE		(1ul<<2)	/* transmit Error flag */
#define SSC_STAT_RE		(1ul<<3)	/* receive Error flag */
#define SSC_STAT_PE		(1ul<<4)	/* phase Error flag */

/* SSC I2C Control Register */
#define SSC_I2C			0x0018

#define SPI_CPHA		0x01		/* clock phase */
#define SPI_CPOL		0x02		/* clock polarity */
#define SPI_LSB_FIRST		0x08		/* endianness */
#define SPI_LOOP		0x20		/* loop-back test mode */

#define SPI_MODE_0		(0|0)
#define SPI_MODE_1		(0|SPI_CPHA)
#define SPI_MODE_2		(SPI_CPOL|0)
#define SPI_MODE_3		(SPI_CPOL|SPI_CPHA)

#endif	/* CONFIG_SOFT_SPI */


/**********************************************************************/


#define MIN(a,b)	( (a) < (b) ? (a) : (b) )


/**********************************************************************/


#if defined(CONFIG_SPI_FLASH_ATMEL)
/* For Atmel AT45DB321D Serial Flash */
#define CFG_STM_SPI_MODE	SPI_MODE_3
#define CFG_STM_SPI_FREQUENCY	(10*1000*1000)	/* 10 MHz */
#define CFG_STM_SPI_DEVICE_MASK	0x3cu		/* Mask Bits [5:2] */
#define CFG_STM_SPI_DEVICE_VAL	0x34u		/* Binary xx1101xx */

#define OP_READ_STATUS		0xd7u		/* Status Register Read */
#define OP_READ_DEVID		0x9fu		/* Manufacturer & Device ID Read */
//#define OP_READ_ARRAY		0xe8u		/* Continuous Array Read */
//#define OP_READ_ARRAY		0x0bu		/* Continuous Array Read */
#define OP_READ_ARRAY		0x03u		/* Continuous Array Read */
#define OP_WRITE_VIA_BUFFER1	0x82u		/* Main Memory Page Program via Buffer 1 */
#define OP_WRITE_VIA_BUFFER2	0x85u		/* Main Memory Page Program via Buffer 2 */
#define OP_PAGE_TO_BUFFER1	0x53u		/* Main Memory Page to Buffer 1 Transfer */
#define OP_PAGE_TO_BUFFER2	0x55u		/* Main Memory Page to Buffer 2 Transfer */

#define SR_READY		(1u<<7)		/* Status Register Read/nBusy bit */

#elif defined(CONFIG_SPI_FLASH_ST)	/******************************/

/* For ST M25Pxx Serial Flash */
#define CFG_STM_SPI_MODE	SPI_MODE_3
#define CFG_STM_SPI_FREQUENCY	(10*1000*1000)	/* 10 MHz */
#define CFG_STM_SPI_DEVICE_MASK	0x60u		/* Mask Bits [6:5] */
#define CFG_STM_SPI_DEVICE_VAL	0x00u		/* Binary x00xxxxx */

#define OP_READ_STATUS		0x05u		/* Read Status Register */
#define OP_WRITE_STATUS		0x01u		/* Write Status Register */
#define OP_READ_DEVID		0x9fu		/* Read ID */
#define OP_READ_ARRAY		0x03u		/* Read Data Bytes */
#define OP_WREN			0x06u		/* Write Enable */
//#define OP_SE			0xD8u		/* Sector Erase */
#define OP_SE			0x20u		/* Sector Erase iptv winbond*/
#define OP_PP			0x02u		/* Page Program */

#define SR_WIP			(1u<<0)		/* Status Register Write In Progress bit */
#define SR_BP_MASK		0x1c		/* Block Protect Bits (BP[2:0]) */

#elif defined(CONFIG_SPI_FLASH_MXIC)	/******************************/

/* For Macronix MX25Lxxx Serial Flash */
#define CFG_STM_SPI_MODE	SPI_MODE_3
#define CFG_STM_SPI_FREQUENCY	(10*1000*1000)	/* 10 MHz */
#define CFG_STM_SPI_DEVICE_MASK	0x00u		/* Mask Bits */
#define CFG_STM_SPI_DEVICE_VAL	0x00u		/* Binary xxxxxxxx */

#define OP_READ_STATUS		0x05u		/* Read Status Register */
#define OP_WRITE_STATUS		0x01u		/* Write Status Register */
#define OP_READ_DEVID		0x9fu		/* Read ID */
#define OP_READ_ARRAY		0x03u		/* Read Data Bytes */
#define OP_WREN			0x06u		/* Write Enable */
#define OP_SE			0x20u		/* Sector Erase */
#define OP_PP			0x02u		/* Page Program */

#define SR_WIP			(1u<<0)		/* Status Register Write In Progress bit */
#define SR_BP_MASK		0x3c		/* Block Protect Bits (BP[3:0]) */

#else					/******************************/

#error Please specify which SPI Serial Flash is being used

#endif	/* defined(CONFIG_STM_SPI_xxxxxx) */


/**********************************************************************/


#define CFG_STM_SPI_SSC_BASE	ST40_SSC0_REGS_BASE	/* SSC #0 */
static const unsigned long ssc = CFG_STM_SPI_SSC_BASE;	/* SSC base */

#define ssc_write(offset, value)	writel((value), (ssc)+(offset))
#define ssc_read(offset)		readl((ssc)+(offset))


/**********************************************************************/


static unsigned pageSize;	/* 256, 512 or 528 bytes per page ? */
static unsigned eraseSize;	/* smallest supported erase size */
static unsigned deviceSize;	/* Size of the device in Bytes */
static const char * deviceName;	/* Name of the device */



/*
 * Transfer (i.e. exchange) one "word" with selected SPI device.
 * Typically one word is 8-bits (an octet), but it does not need to be,
 * this function is word-width agnostic - when using the SSC.
 * However, for PIO bit-banging, then one word is explicitly
 * unconditionally assumed to be exactly 8-bits in length.
 *
 *	input:   "out" is word to be send to slave SPI device
 *	returns: one word read from the slave SPI device
 *
 * It is the caller's responsibility to ensure that the
 * chip select (SPI_NOTCS) is correctly asserted.
 */
static unsigned int spi_xfer_one_word(const unsigned int out)
{
	unsigned int in = 0;

#if defined(CONFIG_SOFT_SPI)		/* Use PIO Bit-Banging for SPI */
	signed int i;
	for(i=7; i>=0; i--)		/* for each bit in turn ... */
	{				/* do 8 bits, msb first */
		SPI_SCL(0);		/* SPI_CLK = low */
		SPI_SDA(out & (1u<<i));	/* output next bit on SPI_DOUT */
		SPI_DELAY;		/* clock low cycle */

		SPI_SCL(1);		/* SPI_CLK = high */
		SPI_DELAY;		/* sample on RISING clock edge */

		in <<= 1;		/* shift */
		in |= SPI_READ;		/* get next bit from SPI_DIN */
	}
#else					/* Use SSC for SPI */
	/* write out data 'out' */
	ssc_write(SSC_TBUF, out);

	/* wait for Receive Buffer Full flag to be asserted */
	while ((ssc_read(SSC_STAT) & SSC_STAT_RIR) == 0)
	{
		;	/* busy poll - do nothing */
	}

	/* read in data */
	in = ssc_read(SSC_RBUF);
#endif	/* CONFIG_SOFT_SPI */

	/* return exchanged data */
	return in;
}


/**********************************************************************/


/*
 * transfer (i.e. exchange) a series of "words" with SPI device.
 * Typically one word is 8-bits (an octet).
 * This function is expects a word to be exactly 8-bits.
 *
 *	input:   chipsel is pointer to the chip-select function (if !NULL)
 *		 bitlen number of *bits* (not bytes) to be exchanged
 *		 dout pointer to array of words to be sent to SPI
 *		 din pointer to array of words that were read from SPI
 *	returns: zero on success, else non-zero.
 *
 *	Note: 'din' may be NULL if caller does not need to see it.
 */
extern int spi_xfer(
	spi_chipsel_type const chipsel,
	const int bitlen,
	uchar * const dout,
	uchar * const din)
{
	size_t i;
	const int bytelen = bitlen / 8;	/* number of 8-bit bytes */

	/*
	 * This code assumes that as we are using the SSC, that we will always
	 * be swapping multiples of *whole* 8-bit bytes between the master
	 * and the slave device.
	 * This assumption is strictly unnecessary, as we could re-program
	 * the SSC to allow any bit-size we want. However, this initial version
	 * of the code sets the pervading transfers to 8-bits in the SSC.
	 * So, right now, we just give up if the number of bits is not a
	 * whole number of (8-bit) bytes - after printing a suitable diagnostic.
	 */
	if (bitlen & 0x7)
	{
		printf("ERROR: %s() called with non-multiple of octets (%u bits)\n",
			__FUNCTION__,
			bitlen);
		return 1;	/* error status */
	}

#if 0	/* QQQ - DELETE */
	hexdump(dout, bytelen);
#endif	/* QQQ - DELETE */

	if(chipsel)
	{	/* assert SPI CS */
		chipsel(1);
	}

	/* transfer: write bytes in 'dout', and read into 'din' */
	for(i=0; i<bytelen; i++)
	{
		uchar data;
		data = spi_xfer_one_word(dout[i]);
		if (din != NULL) din[i] = data;
	}

	if(chipsel)
	{	/* de-assert SPI CS */
		chipsel(0);
	}

	return 0;	/* success */
}


/**********************************************************************/


/*
 * read the SPI slave device's "Status Register".
 *
 * input:   none
 * returns: the value of the status register.
 */
static unsigned int spi_read_status(
	spi_chipsel_type const chipsel)
{
	unsigned char data[2] = { OP_READ_STATUS, 0x00 };

	/* issue the Status Register Read command */
	spi_xfer(chipsel, sizeof(data)*8, data, data);

	/* return the status byte read */
	return data[1];
}


/**********************************************************************/


/*
 * poll the "Status Register" waiting till it is not busy.
 *
 * input:   none
 * returns: none
 */
static void spi_wait_till_ready(
	spi_chipsel_type const chipsel)
{
#if defined(CONFIG_SPI_FLASH_ATMEL)
	while (!(spi_read_status(chipsel) & SR_READY))
		;	/* do nothing */
#elif defined(CONFIG_SPI_FLASH_ST) || defined(CONFIG_SPI_FLASH_MXIC)
	while (spi_read_status(chipsel) & SR_WIP)
		;	/* do nothing */
#else
#error Please specify which SPI Serial Flash is being used
#endif	/* defined(CONFIG_STM_SPI_xxxxxx) */
}


/**********************************************************************/


/*
 * probe the serial flash on the SPI bus, to ensure
 * it is a known type, and initialize its properties.
 */
static int spi_probe_serial_flash(
	spi_chipsel_type const chipsel)
{
	unsigned int status;
	unsigned char devid[8] = {
		OP_READ_DEVID,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

	/* read & detect the SPI device type */
	status = spi_read_status(chipsel);
	if (
		(status == 0xffu)	/* nothing talking to us ? */	||
		( (status & CFG_STM_SPI_DEVICE_MASK) != CFG_STM_SPI_DEVICE_VAL )
	   )
	{
		printf("ERROR: Unknown SPI Device detected, status = 0x%02x\n",
			status);
		return -1;
	}

	/*
	 * if we get here, then we think we may have a SPI
	 * device, so now check it is the correct one!
	 */
	spi_xfer(chipsel, sizeof(devid)*8, devid, devid);

#if defined(CONFIG_SPI_FLASH_ATMEL)

	/* extract the page size */
	if (
		(devid[1] != 0x1fu)	||	/* Manufacturer ID */
		(devid[2] != 0x27u)	||	/* Memory Type */
		(devid[3] != 0x01u)		/* Code + Version */
	   )
	{
		printf("ERROR: Unknown SPI Device detected, devid = 0x%02x, 0x%02x, 0x%02x\n",
			devid[1], devid[2], devid[3]);
		return -1;
	}
	pageSize = (status & 1u) ? 512u : 528u;
	eraseSize = pageSize;
	deviceSize = 8192u * pageSize;		/* 32 Mbit == 4 MiB */
	deviceName = "Atmel AT45DB321D";

#elif defined(CONFIG_SPI_FLASH_ST)
 
       if (!((devid[1] == 0xefu) || (devid[1] == 0x20u))	||	 /* Manufacturer ID */
	     !((devid[2] == 0x40u) || (devid[2] == 0x20u))	||	 /* Memory Type */
		(				/* Memory Capacity */
			(devid[3] != 0x14u) &&	/* M25P80 */
			(devid[3] != 0x15u) &&	/* M25P16 */
			(devid[3] != 0x16u) &&	/* M25P32 */
			(devid[3] != 0x17u) &&	/* M25P64 */
			(devid[3] != 0x18u)	/* M25P128 */
		)
	   )
	{
		printf("ERROR: Unknown SPI Device detected, devid = 0x%02x, 0x%02x, 0x%02x\n",
			devid[1], devid[2], devid[3]);
		return -1;
	}
	pageSize   = 256u;
	eraseSize  = 4u<<10;			/* 4 KiB, 16 pages/sector */
	deviceSize = 1u<<devid[3];		/* Memory Capacity */
	if (devid[3] == 0x14u)
	{
		deviceName = "ST M25P80";	/* 8 Mbit == 1 MiB */
	}
	else if (devid[3] == 0x15u)
	{
		deviceName = "ST M25P16";	/* 16 Mbit == 2 MiB */
	}
	else if (devid[3] == 0x16u)
	{
		deviceName = "ST M25P32";	/* 32 Mbit == 4 MiB */
	}
	else if (devid[3] == 0x17u)
	{
		deviceName = "ST M25P64";	/* 64 Mbit == 8 MiB */
	}
	else if (devid[3] == 0x18u)
	{
		deviceName = "ST M25P128";	/* 128 Mbit == 16 MiB */
		eraseSize = 256u<<10;		/* 256 KiB, 1024 pages/sector */
	}

#elif defined(CONFIG_SPI_FLASH_MXIC)

	if (
		(devid[1] != 0xc2u)	||	/* Manufacturer ID */
		(devid[2] != 0x26u)	||	/* Memory Type */
		(				/* Memory Capacity */
			(devid[3] != 0x15u) &&	/* MX25L1655D */
			(devid[3] != 0x17u) &&	/* MX25L6455E */
			(devid[3] != 0x18u)	/* MX25L12855E */
		)
	   )
	{
		printf("ERROR: Unknown SPI Device detected, devid = 0x%02x, 0x%02x, 0x%02x\n",
			devid[1], devid[2], devid[3]);
		return -1;
	}
	pageSize   = 256u;
	eraseSize  = 4u<<10;			/* 4 KiB, 16 pages/sector */
	deviceSize = 1u<<devid[3];		/* Memory Capacity */
	if (devid[3] == 0x15u)
	{
		deviceName = "MXIC MX25L1655D";	/* 16 Mbit == 2 MiB */
	}
	else if (devid[3] == 0x17u)
	{
		deviceName = "MXIC MX25L6455E";	/* 64 Mbit == 8 MiB */
	}
	else if (devid[3] == 0x18u)
	{
		deviceName = "MXIC MX25L12855E";/* 128 Mbit == 16 MiB */
	}

#else
#error Please specify which SPI Serial Flash is being used
#endif	/* defined(CONFIG_STM_SPI_xxxxxx) */

#if 1
	/* tell them what we found */
	printf("SPI: %s (%uMiB) device (page=%u,erase=%u)\n",
		deviceName,
		deviceSize >> 20,	/* in MiB */
		pageSize,		/* in bytes */
		eraseSize);		/* in bytes */
#endif

#if defined(CONFIG_SPI_FLASH_ST) || defined(CONFIG_SPI_FLASH_MXIC)
	/* is the device in a write protected mode ? */
	if (status & SR_BP_MASK)	/* BPx != 0 ? */
	{
		printf( "warning: "
			"SPI device may be write-protected (status=0x%02x)\n",
			status);
#if 0	/* do we want to un-lock it, if we can ? */
{
	unsigned char enable[1] = { OP_WREN };
	unsigned char unlock[2] = { OP_WRITE_STATUS, 0x00 };

	/* let the user know we are trying to un-lock it */
	printf("info: unlocking SPI ...\n");

	/* issue a WRITE ENABLE (WREN) command */
	spi_xfer(chipsel, sizeof(enable)*8, enable, NULL);

	/* issue a WRITE Status Register (WRSR) command */
	spi_xfer(chipsel, sizeof(unlock)*8, unlock, NULL);

	/* give it some time to clear the non-volatile flags */
	udelay(2 * 1000);	/* 2 ms */

	/* re-read (and display) the updated status register */
	status = spi_read_status(chipsel);
	if (status & SR_BP_MASK)	/* BPx != 0 ? */
	{	/* we MAY have succeeded, but we needed a longer delay! */
		printf("warning:            ... FAILED! (status=0x%02x)\n",
			status);
	}
	else
	{	/* the delay was long enough, and we succeeded. */
		printf("info:               ... succeeded.\n");
	}
}
#endif	/* unlock it */
	}
#endif	/* CONFIG_SPI_FLASH_ST || CONFIG_SPI_FLASH_MXIC */

	return 0;
}


/**********************************************************************/


/*
 * initialise the SSC to talk to the slave SPI device.
 */
extern void spi_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	spi_chipsel_type const chipsel = spi_chipsel[0];	/* SPI Device #0 */

#if !defined(CONFIG_SOFT_SPI)			/* Use SSC for SPI */
	unsigned long reg;
	const unsigned long bits_per_word = 8;	/* one word == 8-bits */
	const unsigned long mode = CFG_STM_SPI_MODE /* | SPI_LOOP */;
	const unsigned long fcomms = get_peripheral_clk_rate();
	const unsigned long hz = CFG_STM_SPI_FREQUENCY;
	      unsigned long sscbrg = fcomms/(2*hz);

#if defined(CONFIG_SH_STX5197)
	/* configure SSC0 to use the SPI pads (not PIO1[7:6]) */
	reg = *STX5197_HD_CONF_MON_CONFIG_CONTROL_M;
	reg |= 1ul<<14;	/* CFG_CTRL_M.SPI_BOOTNOTCOMMS = 1 [14] */
	*STX5197_HD_CONF_MON_CONFIG_CONTROL_M = reg;
#endif	/* CONFIG_SH_STX5197 */

#endif	/* CONFIG_SOFT_SPI */

	/* de-assert SPI CS */
	(*chipsel)(0);

#if !defined(CONFIG_SOFT_SPI)			/* Use SSC for SPI */
	/* program the SSC's Baud-Rate Generator */
	if ((sscbrg < 0x07u) || (sscbrg > (0x1u << 16)))
	{
		printf("ERROR: Unable to set SSC buad-rate generator to 0x%04x\n",
			sscbrg);
		return;
	}
	/* TODO: program pre-scaler for slower baud rates */
	if (sscbrg == (0x1 << 16)) /* 16-bit counter wraps */
	{
		sscbrg = 0x0;	/* slowest possible clock frequency */
	}
	ssc_write(SSC_BRG,sscbrg);
#if 0	/* QQQ */
	printf("info: fcomms=%uMHz, SPI=%uHz, brg=0x%04x\n",
		fcomms/1000/1000, hz, sscbrg);
#endif

	/* Disable I2C sub-system */
	ssc_write( SSC_I2C, 0x0);

	/* Perform a S/W reset the SSC */
	reg = ssc_read( SSC_CON);
	reg |= SSC_CON_SR;		/* enable software reset */
	ssc_write( SSC_CON, reg);
	udelay(1);			    /* let reset propagate */
	reg = ssc_read( SSC_CON);
	reg &= ~SSC_CON_SR;		/* disable software reset */
	ssc_write( SSC_CON, reg);

	/* Configure & enable the SSC's control register */
	reg = ssc_read(SSC_CON);
	reg |= SSC_CON_EN;		/* Enable the SSC */
	reg |= SSC_CON_MS;		/* set SSC as the SPI master */
	if (mode & SPI_CPOL)
		reg |= SSC_CON_PO;	/* Clock idles at logic 1 */
	else
		reg &= ~SSC_CON_PO;	/* Clock idles at logic 0 */
	if (mode & SPI_CPHA)
		reg |= SSC_CON_PH;	/* Pulse in first half-cycle */
	else
		reg &= ~SSC_CON_PH;	/* Pulse in second half-cycle */
	if (mode & SPI_LSB_FIRST)
		reg &= ~SSC_CON_HB;	/* LSB first */
	else
		reg |= SSC_CON_HB;	/* MSB first */
	if (mode & SPI_LOOP)
		reg |= SSC_CON_LPB;	/* put SSC in loop-back mode */
	else
		reg &= ~SSC_CON_LPB;	/* remove SSC from loop-back mode */
	reg &= ~0x0ful;			/* set bit width */
	reg |= (bits_per_word - 1ul);	/* set bit width */
	ssc_write(SSC_CON,reg);

	/* clear the status register */
	(void)ssc_read(SSC_RBUF);
#endif	/* CONFIG_SOFT_SPI */

	/* now probe the serial flash, to ensure it is the correct one */
	spi_probe_serial_flash(chipsel);
}


/**********************************************************************/


extern void spi_init_f (void) { }
extern void spi_init_r (void) { }


/**********************************************************************/


static unsigned long get_binary_offset(const uchar * addr, int alen)
{
	unsigned long offset = 0;

	for(;alen>0;--alen)
	{
		offset <<= 8;
		offset |= *addr++;
	}

	return offset;
}


/**********************************************************************/


static unsigned long get_dataflash_offset(const unsigned long addr)
{
	unsigned long offset;

	/* optionally map a 'binary' address to a 'dataflash' address */
	if (pageSize == 528u)
	{	/* one page is 528 (0x210) bytes */
		const unsigned long page = addr / pageSize;
		const unsigned long byte = addr % pageSize;
		offset = (page << 10) | (byte);
	}
	else
	{	/* no special mapping needed */
		offset = addr;
	}

	return offset;
}


/**********************************************************************/


extern ssize_t spi_read (
	uchar * const addr,
	const int alen,
	uchar * const buffer,
	const int len)
{
	int i;
	const unsigned long start = get_binary_offset(addr,alen);
	const unsigned long offset = get_dataflash_offset(start);
	const unsigned long last   = start + len - 1ul;
	spi_chipsel_type const chipsel = spi_chipsel[0];	/* SPI Device #0 */

	if (len < 1) return len;
	if (last >= deviceSize)	/* Out of range ? */
	{
		printf("ERROR: Offset out of range (max=0x%lx)\n",
			deviceSize-1ul);
		return 0;
	}

	/* assert SPI CS */
	(*chipsel)(1);

	/* issue appropriate READ array command */
	spi_xfer_one_word(OP_READ_ARRAY);

	/* write the 24-bit address to start reading from */
	spi_xfer_one_word( (offset>>16) & 0xffu );
	spi_xfer_one_word( (offset>>8)  & 0xffu );
	spi_xfer_one_word( (offset>>0)  & 0xffu );

#if (OP_READ_ARRAY==0xe8u)	/* Legacy command needs 4 dummy bytes */
	spi_xfer_one_word(0x00);
	spi_xfer_one_word(0x00);
	spi_xfer_one_word(0x00);
	spi_xfer_one_word(0x00);
#elif (OP_READ_ARRAY==0x0bu)	/* High-Speed command needs 1 dummy byte */
	spi_xfer_one_word(0x00);
#endif

	/* now read in each byte in turn, and put it in "buffer" */
	for(i=0; i<len; i++)
	{
		buffer[i] = spi_xfer_one_word(0x00);
	}

	/* de-assert SPI CS */
	(*chipsel)(0);

	return len;
}


/**********************************************************************/


static void my_spi_write(
	spi_chipsel_type const chipsel,
	const unsigned long address,
	const uchar * const buffer,
	unsigned long len)
#if defined(CONFIG_SPI_FLASH_ATMEL)
{
	const unsigned long offset = get_dataflash_offset(address);
	size_t i;

#if 0	/* QQQ - DELETE */
	printf("%s():\t buffer=0x%08x, len=%-3u  0x%06x..0x%06x\n",
		__FUNCTION__, buffer, len, address, address+len-1u);
#endif	/* QQQ - DELETE */

	if (len != pageSize)	/* partial page update ? */
	{
		/*
		 * Need to read, merge, erase & write one page.
		 * That is, we copy the whole page into one
		 * of the serial-flash buffers, and then just over-write
		 * with the new data to be updated (in 'buffer'). Then
		 * we erase & write back the whole (merged) page.
		 */

		unsigned char transfer[4] = {
			OP_PAGE_TO_BUFFER1,
			(offset>>16) & 0xffu,
			(offset>>8)  & 0xffu,
			(offset>>0)  & 0xffu,
		};

		/* copy page (to be updated) in serial flash into buffer #1 */
		spi_xfer(chipsel, sizeof(transfer)*8, transfer, NULL);

		/* now wait until the transfer has completed ... */
		spi_wait_till_ready(chipsel);
	}

	/* assert SPI CS */
	(*chipsel)(1);

	/* issue appropriate WRITE command */
	spi_xfer_one_word(OP_WRITE_VIA_BUFFER1);

	/* write the 24-bit address to start writing to */
	spi_xfer_one_word( (offset>>16) & 0xffu );
	spi_xfer_one_word( (offset>>8)  & 0xffu );
	spi_xfer_one_word( (offset>>0)  & 0xffu );

	/* now write in each byte in turn */
	for(i=0; i<len; i++)
	{
		spi_xfer_one_word(buffer[i]);
	}

	/* de-assert SPI CS */
	(*chipsel)(0);

	/* now wait until the programming has completed ... */
	spi_wait_till_ready(chipsel);
}
#elif defined(CONFIG_SPI_FLASH_ST) || defined(CONFIG_SPI_FLASH_MXIC)
{
	const unsigned pages       = eraseSize / pageSize;
	const unsigned long sector = (address / eraseSize) * eraseSize;
	unsigned long page_base;
	size_t i;
	unsigned page;
	const uchar * ptr;
#if defined(CONFIG_SPI_FLASH_ST)
	static unsigned char buff[256<<10];	/* maximum of 256 KiB erase size */
#elif defined(CONFIG_SPI_FLASH_MXIC)
	static unsigned char buff[4<<10];	/* maximum of 4 KiB erase size */
#endif
	unsigned char enable[1] = { OP_WREN };
	unsigned char erase[4] = {
		OP_SE,
		(sector>>16) & 0xffu,
		(sector>>8)  & 0xffu,
		(sector>>0)  & 0xffu,
	};

#if 0	/* QQQ - DELETE */
	printf("%s():\t buffer=0x%08x, len=%-5u  0x%06x..0x%06x\n",
		__FUNCTION__, buffer, len, address, address+len-1u);
#endif	/* QQQ - DELETE */

	if (len != eraseSize)	/* partial sector update ? */
	{
		/*
		 * Need to read, merge, erase & write one sector.
		 * That is, we copy the whole sector from
		 * the serial-flash into RAM, and then just over-write
		 * with the new data to be updated (in 'buffer'). Then
		 * we erase & write back the whole (merged) sector.
		 */
		unsigned char addr[3] = {
			(sector>>16) & 0xffu,
			(sector>>8)  & 0xffu,
			(sector>>0)  & 0xffu,
		};
		const unsigned long offset = address - sector;

		/* read the entire extant sector's content into RAM */
		spi_read ( addr, sizeof(addr), buff, eraseSize );

		/* now merge the old with the new data */
		for( i=0; i<len; i++)
		{
			buff[offset+i] = buffer[i];
		}
		ptr = buff;	/* use "merged" buffer */
	}
	else
	{
		ptr = buffer;	/* use original buffer */
	}

	/* issue a WRITE ENABLE (WREN) command */
	spi_xfer(chipsel, sizeof(enable)*8, enable, NULL);

	/* issue a Sector Erase command */
	spi_xfer(chipsel, sizeof(erase)*8, erase, NULL);

	/* now wait until the erase has completed ... */
	spi_wait_till_ready(chipsel);

	/* now program each page in turn ... */
	for (page_base=sector,page=0u; page<pages; page++)
	{
		/* issue a WRITE ENABLE (WREN) command */
		spi_xfer(chipsel, sizeof(enable)*8, enable, NULL);

		/* assert SPI CS */
		(*chipsel)(1);

		/* issue a Page Program command */
		spi_xfer_one_word(OP_PP);

		/* write the 24-bit address to start writing to */
		spi_xfer_one_word( (page_base>>16) & 0xffu );
		spi_xfer_one_word( (page_base>>8)  & 0xffu );
		spi_xfer_one_word( (page_base>>0)  & 0xffu );

		/* now write in each byte in turn */
		for(i=0; i<pageSize; i++)
		{
			spi_xfer_one_word(*ptr++);
		}

		/* de-assert SPI CS */
		(*chipsel)(0);

		/* now wait until the programming has completed ... */
		spi_wait_till_ready(chipsel);

		/* advance to next page */
		page_base += pageSize;
	}
}
#else
#error Please specify which SPI Serial Flash is being used
#endif	/* defined(CONFIG_STM_SPI_xxxxxx) */


/**********************************************************************/


extern ssize_t spi_write (
	uchar * const addr,
	const int alen,
	uchar * buffer,
	const int len)
{
	const unsigned long first  = get_binary_offset(addr,alen);
	const unsigned long last   = first + len - 1ul;
	const unsigned long lsector= (first + len) / eraseSize;
	      unsigned long sector = first / eraseSize;
	const unsigned long byte   = first % eraseSize;
	      unsigned long ptr    = first;
	unsigned written = 0;		/* amount written between two dots */
	spi_chipsel_type const chipsel = spi_chipsel[0];	/* SPI Device #0 */


	if (len < 1) return len;
	if (last >= deviceSize)	/* Out of range ? */
	{
		printf("ERROR: Offset out of range (max=0x%lx)\n", deviceSize-1ul);
		return 0;
	}

	/* process up to end of first erase block */
	if (byte != 0)
	{
		/* till end of first erase block, or entirety, which is less */
		const unsigned long size = MIN(len,eraseSize-byte);
		my_spi_write(chipsel, first, buffer, size);

		sector++;
		ptr += size;
		buffer += size;
		written += size;
	}

	/* process each whole erase block in turn */
	while(sector<lsector)
	{
		/* print a series of dots (every 16KiB) */
		if ( (written+=eraseSize,written) >= (16u<<10) )
		{
			printf(".");	/* print a dot */
			written = 0;	/* reset counter */
		}

		/* a whole erase block */
		my_spi_write(chipsel, ptr, buffer, eraseSize);
		sector++;
		ptr += eraseSize;
		buffer += eraseSize;

	}
	printf("\n");	/* terminate any row of printed dots */

	/* finally, process any data at the tail */
	if (ptr <= last)
	{
		my_spi_write(chipsel, ptr, buffer, last-ptr+1u);
	}

	return len;
}


/**********************************************************************/


#endif	/* defined(CONFIG_SPI) */


