/*
 * arch/sh/boards/st/hmp7100/setup.c
 *
 * Copyright (C) 2005 STMicroelectronics Limited
 * Author: Stuart Menefy (stuart.menefy@st.com)
 *
 * May be copied or modified under the terms of the GNU General Public
 * License.  See linux/COPYING for more information.
 *
 * STMicroelectronics STb7100 HMP board support.
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/stm/pio.h>
#include <linux/stm/soc.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/physmap.h>
#include <linux/mtd/partitions.h>
#include <linux/phy.h>
#include <linux/lirc.h>
#include <asm/irl.h>

static int ascs[2] __initdata = { 2, 3 };

void __init hmp7100_setup(char** cmdline_p)
{
	printk("STMicroelectronics STb7100 HMP board initialisation\n");

	stx7100_early_device_init();
	stb7100_configure_asc(ascs, 2, 0);
}

static struct plat_stm_pwm_data pwm_private_info = {
	.flags		= PLAT_STM_PWM_OUT1,
};

static struct plat_ssc_data ssc_private_info = {
	.capability  =
		ssc0_has(SSC_I2C_CAPABILITY) |
		ssc1_has(SSC_SPI_CAPABILITY) |
		ssc2_has(SSC_I2C_CAPABILITY),
};

static struct resource smc91x_resources[] = {
	[0] = {
		.start	= 0x02000000,
		.end	= 0x02000000 + 0xff,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRL0_IRQ,
		.end	= IRL0_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
        [2] = {
                .name  = "polarity",
                .start = 0,
                .end   = 0,
                .flags = IORESOURCE_IRQ,
        },
        [3] = {
                .name  = "type",
                .start = 1,
                .end   = 1,
                .flags = IORESOURCE_IRQ,
        },

};

static struct platform_device smc91x_device = {
	.name		= "smc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
};

static struct mtd_partition mtd_parts_table[3] = {
	{
		.name = "Boot firmware",
		.size = 0x00040000,
		.offset = 0x00000000,
	}, {
		.name = "Kernel",
		.size = 0x00100000,
		.offset = 0x00040000,
	}, {
		.name = "Root FS",
		.size = MTDPART_SIZ_FULL,
		.offset = 0x00140000,
	}
};

static struct physmap_flash_data physmap_flash_data = {
	.width		= 2,
	.set_vpp	= NULL,
	.nr_parts	= ARRAY_SIZE(mtd_parts_table),
	.parts		= mtd_parts_table
};

static struct resource physmap_flash_resource = {
	.start		= 0x00000000,
	.end		= 0x00800000 - 1,
	.flags		= IORESOURCE_MEM,
};

static struct platform_device physmap_flash = {
	.name		= "physmap-flash",
	.id		= -1,
	.dev		= {
		.platform_data	= &physmap_flash_data,
	},
	.num_resources	= 1,
	.resource	= &physmap_flash_resource,
};

static struct stpio_pin *phy_reset_pin;

static int hmp7100_phy_reset(void* bus)
{
printk ("hmp7100_phy_reset\n");
	stpio_set_pin(phy_reset_pin, 1);
	udelay(1);
	stpio_set_pin(phy_reset_pin, 0);
	udelay(1);
	stpio_set_pin(phy_reset_pin, 1);

	return 1;
}

static struct plat_stmmacphy_data phy_private_data = {
	.bus_id = 0,
	.phy_addr = 2,
	.phy_mask = 0,
	.interface = PHY_INTERFACE_MODE_MII,
	.phy_reset = &hmp7100_phy_reset,
};

static struct platform_device hmp7100_phy_device = {
	.name		= "stmmacphy",
	.id		= 0,
	.num_resources	= 1,
	.resource	= (struct resource[]) {
                {
			.name	= "phyirq",
			.start	= IRL3_IRQ,
			.end	= IRL3_IRQ,
			.flags	= IORESOURCE_IRQ,
		},
	},
	.dev = {
		.platform_data = &phy_private_data,
	 }
};

static struct platform_device *hmp7100_devices[] __initdata = {
	&smc91x_device,
	&physmap_flash,
	&hmp7100_phy_device,
};

/* Configuration based on Futarque-RC signals train. */
lirc_scd_t lirc_scd = {
	.code = 0x3FFFC028,
	.codelen = 0x1e,
	.alt_codelen = 0,
	.nomtime = 0x1f4,
	.noiserecov = 0,
};

static int __init device_init(void)
{
	struct stpio_pin *ethreset;
        struct stpio_pin *fereset;

	stx7100_configure_sata();
	stx7100_configure_pwm(&pwm_private_info);
	stx7100_configure_ssc(&ssc_private_info);
	stx7100_configure_usb();
	stx7100_configure_lirc(&lirc_scd);
	stx7100_configure_pata(3, 1, IRL1_IRQ);

	stx7100_configure_ethernet(0, 0, 0);
	phy_reset_pin = stpio_request_pin(5, 3, "ste100p_reset",
					      STPIO_OUT);

        /* Reset the FE chip */
        fereset =  stpio_request_set_pin (2, 6, "fe_reset",  STPIO_OUT, 1);
	udelay(1);
	stpio_set_pin(fereset, 0);
	udelay(1);
	stpio_set_pin(fereset, 1);

	/* Reset the SMSC 9118 Ethernet chip */
	ethreset = stpio_request_set_pin(2, 7, "smc91x_reset",
					     STPIO_OUT, 1);
	udelay(1);
	stpio_set_pin(ethreset, 0);
	udelay(1);
	stpio_set_pin(ethreset, 1);

	return platform_add_devices(hmp7100_devices,
				    ARRAY_SIZE(hmp7100_devices));
}

device_initcall(device_init);
