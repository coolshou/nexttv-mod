/*
 * include/asm-sh/hms1/st40_ide.h
 *
 * This file contains all the definitions to support
 * the IDE interface on HMS1.
 * This uses the IDE EMI in bank 3.
 */

/* On the HMS1 is present only 1 hw interface */
#undef MAX_HWIFS
#define MAX_HWIFS       1

/* The ATA base address. */
#define ATA_ADDRESS           0xA2800000

/* The ATA data base address offset. It is used to map
 * all the ide registers on the hwif interface
 * starting from this offset.
 */
#define ATA_DATA_OFFS_ADDRESS	0x00200000

/* The ide registers offset. Registers will be stored into
 * the hwif interface with a costant offset starting from
 * the ATA data register address.
 */
#define REG_OFFSET	0x20000

/* Only the control register has a different offset. */
#define CTRL_REG_OFFSET		-0x40000

/* ATA IRQ number */
#define ATA_IRQ		IRL1_IRQ

/* ide_enable does nothing because there is no external hardware to configure */
#define ide_enable()

/* These do nothing because the STb7100 doesn't have an HDDI i/f */
#define hddi_reset()
#define hddi_set_pio_timings(rate)
#define hddi_setup_dma(interface, address, offset)

/* ide_ack_intr returns 1 when invoked.
 * It is needed by the ide_intr function.
 */
#define ide_ack_intr(hwif)	1
