/*
 * arch/sh/boards/st/cb104_mc/setup.c
 *
 * Copyright (C) 2009 STMicroelectronics Limited
 * Author: Carl Shaw <carl.shaw@st.com>
 *
 * May be copied or modified under the terms of the GNU General Public
 * License.  See linux/COPYING for more information.
 *
 * Customer Board 104 support.
 */

#include <linux/init.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/stm/pio.h>
#include <linux/stm/soc_init.h>
#include <linux/stm/soc.h>
#include <linux/stm/emi.h>
#include <linux/mtd/nand.h>
#include <linux/stm/nand.h>
#include <linux/stm/sysconf.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/physmap.h>
#include <linux/mtd/partitions.h>
#include <linux/bpa2.h>
#include <linux/dma-mapping.h>
#include <asm/irq-ilc.h>
#include <sound/stm.h>

static int ascs[2] __initdata = {
	2 | (STASC_FLAG_NORTSCTS << 8), /* TTL-level test points only... */
	3 | (STASC_FLAG_NORTSCTS << 8),	/* J8001 (3.5mm jack) */
};

static void __init cb104_setup(char **cmdline_p)
{
	pr_info("CB104 board initialisation\n");
	stx7200_early_device_init();
	stx7200_configure_asc(ascs, 2, 1);
}

static struct plat_ssc_data cb104_ssc_private_info = {
	.capability = (ssc0_has(SSC_I2C_CAPABILITY) |
		       ssc1_has(SSC_SPI_CAPABILITY) |
		       ssc2_has(SSC_I2C_CAPABILITY) |
		       ssc3_has(SSC_UNCONFIGURED) | ssc4_has(SSC_UNCONFIGURED))
};

static struct plat_ssc_data cb104_ssc_private_info_mfg = {
	.capability = (ssc0_has(SSC_I2C_CAPABILITY) |
		       ssc1_has(SSC_SPI_CAPABILITY) |
		       ssc2_has(SSC_I2C_CAPABILITY) |
		       ssc3_has(SSC_UNCONFIGURED) |
		       ssc4_has(SSC_I2C_CAPABILITY))
};

static struct mtd_partition cb104_mtd_parts_table[] = {
	{
	 .name = "nor",
	 .size = MTDPART_SIZ_FULL,
	 .offset = 0x00000000,
	 }
};

static struct physmap_flash_data cb104_physmap_flash_data = {
	.width = 2,
	.nr_parts = ARRAY_SIZE(cb104_mtd_parts_table),
	.parts = cb104_mtd_parts_table
};

static struct platform_device cb104_physmap_flash = {
	.name = "physmap-flash",
	.id = -1,
	.num_resources = 1,
	.resource = (struct resource[]){
					{
					 .start = 0x00000000,
					 .end = 32 * 1024 * 1024 - 1,
					 .flags = IORESOURCE_MEM,
					 }
					},
	.dev = {
		.platform_data = &cb104_physmap_flash_data,
		},
};

static struct mtd_partition nand1_parts[] = {
	{
	 .name = "NAND UBI Space",
	 .offset = 0x00000000,
	 .size = MTDPART_SIZ_FULL	/* 256MB */
	 },
};

static struct plat_stmnand_data nand_config = {
	/* STM_NAND_EMI data */
	.emi_withinbankoffset = 0,
	.rbn_port = 2,
	.rbn_pin = 7,

	/* STM_NAND_FLEX data */
	.flex_rbn_connected = 1,

	/* STM_NAND_EMI/FLEX timing data */
	.timing_data = &(struct nand_timing_data){
						  .sig_setup = 50, /* ns */
						  .sig_hold = 50,
						  .CE_deassert = 0,
						  .WE_to_RBn = 100,
						  .wr_on = 10,
						  .wr_off = 40,
						  .rd_on = 10,
						  .rd_off = 40,
						  .chip_delay = 30, /* in us */
						  },
};

static struct platform_device nand_devices[] = {
	STM_NAND_DEVICE("stm-nand-emi", 1, &nand_config,
			nand1_parts, ARRAY_SIZE(nand1_parts), 0),
};

static struct platform_device *cb104_devices[] __initdata = {
	&cb104_physmap_flash,
};

static int __init device_init(void)
{
	struct stpio_pin *pio = stpio_request_pin(1, 7, "Mfg", STPIO_IN);

	if (!stpio_get_pin(pio)) {
		/* we are in mfg mode */
		pr_info("**** CB104 manufacturing mode ****\n");
		stx7200_configure_usb(1);
		stx7200_configure_usb(2);
		/* Configure ssc4 as a I2C bus.  This is only needed for
		 * manufacturing. */
		stx7200_configure_ssc(&cb104_ssc_private_info_mfg);
	} else {
		/* we are in normal mode */
		stx7200_configure_ssc(&cb104_ssc_private_info);
#ifdef CONFIG_SH_ST_CB104_MC
		stx7200_configure_usb(1);
		stx7200_configure_usb(2);
#endif
	}

	stx7200_configure_nand(&nand_devices[0]);
	stx7200_configure_lirc(NULL);
	return platform_add_devices(cb104_devices, ARRAY_SIZE(cb104_devices));
}

arch_initcall(device_init);

static void __iomem *cb104_ioport_map(unsigned long port, unsigned int size)
{
	/* Shouldn't be here! */
	BUG();
	return NULL;
}


struct sh_machine_vector mv_cb104 __initmv = {
	.mv_name = "cb104",
	.mv_setup = cb104_setup,
	.mv_nr_irqs = NR_IRQS,
	.mv_ioport_map = cb104_ioport_map,
};
