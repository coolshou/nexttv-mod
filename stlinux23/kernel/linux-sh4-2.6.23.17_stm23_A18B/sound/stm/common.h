/*
 * STMicroelectronics' System-on-Chips audio subsystem commons
 */

#ifndef __SOUND_STM_COMMON_H
#define __SOUND_STM_COMMON_H

#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <linux/stringify.h>
#include <linux/stm/soc.h>
#include <linux/stm/stm-dma.h>
#include <sound/driver.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/info.h>
#include <sound/control.h>
#include <sound/stm.h>



/*
 * Frequency synthesizers control interface
 */

struct snd_stm_fsynth_channel;

struct snd_stm_fsynth_channel *snd_stm_fsynth_get_channel(const char *bus_id,
		int output);

int snd_stm_fsynth_add_adjustement_ctl(
		struct snd_stm_fsynth_channel *fsynth_channel,
		struct snd_card *card, int card_device);

int snd_stm_fsynth_set_frequency(struct snd_stm_fsynth_channel *fsynth_channel,
		int frequency);



/*
 * Converters (DAC, ADC, I2S-SPDIF etc.) control interface
 */

struct snd_stm_conv_source;
struct snd_stm_conv_group;
struct snd_stm_conv_converter;

struct snd_stm_conv_source *snd_stm_conv_register_source(struct bus_type *bus,
		const char *bus_id, int channels_num,
		struct snd_card *card, int card_device);
int snd_stm_conv_unregister_source(struct snd_stm_conv_source *source);

int snd_stm_conv_get_card_device(struct snd_stm_conv_converter *converter);

struct snd_stm_conv_group *snd_stm_conv_request_group(
		struct snd_stm_conv_source *source);
int snd_stm_conv_release_group(struct snd_stm_conv_group *group);

const char *snd_stm_conv_get_name(struct snd_stm_conv_group *group);
unsigned int snd_stm_conv_get_format(struct snd_stm_conv_group *group);
int snd_stm_conv_get_oversampling(struct snd_stm_conv_group *group);

int snd_stm_conv_enable(struct snd_stm_conv_group *group,
		int channel_from, int channel_to);
int snd_stm_conv_disable(struct snd_stm_conv_group *group);
int snd_stm_conv_mute(struct snd_stm_conv_group *group);
int snd_stm_conv_unmute(struct snd_stm_conv_group *group);



/*
 * Audio frequency synthesizer description (platform data)
 */

struct snd_stm_fsynth_info {
	int ver;

	int channels_from, channels_to;
};



/*
 * Internal audio DAC description (platform data)
 */

struct snd_stm_conv_int_dac_info {
	int ver;

	const char *source_bus_id;
	int channel_from, channel_to;
};


/*
 * I2S to SPDIF converter description (platform data)
 */

struct snd_stm_conv_i2sspdif_info {
	int ver;

	const char *source_bus_id;
	int channel_from, channel_to;
};



/*
 * PCM Player description (platform data)
 */

struct snd_stm_pcm_player_info {
	const char *name;
	int ver;

	int card_device;
	const char *fsynth_bus_id;
	int fsynth_output;

	unsigned int channels;

	unsigned char fdma_initiator;
	unsigned int fdma_request_line;
};



/*
 * PCM Reader description (platform data)
 */

struct snd_stm_pcm_reader_info {
	const char *name;
	int ver;

	int card_device;

	int channels;

	unsigned char fdma_initiator;
	unsigned int fdma_request_line;
};



/*
 * SPDIF Player description (platform data)
 */

struct snd_stm_spdif_player_info {
	const char *name;
	int ver;

	int card_device;
	const char *fsynth_bus_id;
	int fsynth_output;

	unsigned char fdma_initiator;
	unsigned int fdma_request_line;
};



/*
 * PCM buffer memory management
 */

struct snd_stm_buffer;

struct snd_stm_buffer *snd_stm_buffer_create(struct snd_pcm *pcm,
		struct device *device, int prealloc_size);
void snd_stm_buffer_dispose(struct snd_stm_buffer *buffer);

int snd_stm_buffer_is_allocated(struct snd_stm_buffer *buffer);

int snd_stm_buffer_alloc(struct snd_stm_buffer *buffer,
		struct snd_pcm_substream *substream, int size);
void snd_stm_buffer_free(struct snd_stm_buffer *buffer);

int snd_stm_buffer_mmap(struct snd_pcm_substream *substream,
		struct vm_area_struct *area);



/*
 * Common ALSA controls routines
 */

int snd_stm_ctl_boolean_info(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_info *uinfo);

int snd_stm_ctl_iec958_info(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_info *uinfo);

int snd_stm_ctl_iec958_mask_get_con(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol);

int snd_stm_ctl_iec958_mask_get_pro(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol);

int snd_stm_iec958_cmp(const struct snd_aes_iec958 *a,
		const struct snd_aes_iec958 *b);



/*
 * Common ALSA parameters constraints
 */

int snd_stm_pcm_transfer_bytes(unsigned int bytes_per_frame,
		unsigned int max_transfer_bytes);
int snd_stm_pcm_hw_constraint_transfer_bytes(struct snd_pcm_runtime *runtime,
		unsigned int max_transfer_bytes);



/*
 * Device management
 */

/* Add/remove a list of platform devices */
int snd_stm_add_platform_devices(struct platform_device **devices,
		int cnt);
void snd_stm_remove_platform_devices(struct platform_device **devices,
		int cnt);



/*
 * ALSA card management
 */

struct snd_card *snd_stm_card_new(int index, const char *id,
		struct module *module);
int snd_stm_card_register(void);
int snd_stm_card_is_registered(void);
void snd_stm_card_free(void);

struct snd_card *snd_stm_card_get(void);



/*
 * ALSA procfs additional entries
 */

int snd_stm_info_create(void);
void snd_stm_info_dispose(void);

int snd_stm_info_register(struct snd_info_entry **entry,
		const char *name,
		void (read)(struct snd_info_entry *, struct snd_info_buffer *),
		void *private_data);
void snd_stm_info_unregister(struct snd_info_entry *entry);



/*
 * Resources management
 */

int snd_stm_memory_request(struct platform_device *pdev,
		struct resource **mem_region, void **base_address);
void snd_stm_memory_release(struct resource *mem_region,
		void *base_address);

int snd_stm_irq_request(struct platform_device *pdev,
		unsigned int *irq, irq_handler_t handler, void *dev_id);
#define snd_stm_irq_release(irq, dev_id) free_irq(irq, dev_id)

int snd_stm_fdma_request(struct platform_device *pdev, int *channel);
#define snd_stm_fdma_release(channel) free_dma(channel)



/*
 * Core drivers initialization/exit
 */

int snd_stm_fsynth_init(void);
void snd_stm_fsynth_exit(void);

int snd_stm_conv_init(void);
void snd_stm_conv_exit(void);

int snd_stm_conv_int_dac_init(void);
void snd_stm_conv_int_dac_exit(void);

int snd_stm_conv_i2sspdif_init(void);
void snd_stm_conv_i2sspdif_exit(void);

int snd_stm_pcm_player_init(void);
void snd_stm_pcm_player_exit(void);

int snd_stm_pcm_reader_init(void);
void snd_stm_pcm_reader_exit(void);

int snd_stm_spdif_player_init(void);
void snd_stm_spdif_player_exit(void);

int snd_stm_synchro_init(void);
void snd_stm_synchro_exit(void);



/*
 * Debug features
 */

/* Data dump functions */

void snd_stm_hex_dump(void *data, int size);
void snd_stm_iec958_dump(const struct snd_aes_iec958 *vuc);

/* Component name */

#if !defined(COMPONENT)
#error Please define COMPONENT name before including "common.h" !
#endif
static const char __maybe_unused *__snd_stm_component = __stringify(COMPONENT);

/* Debug messages */

#if defined(CONFIG_SND_DEBUG) || defined(DEBUG)

#define ___concat(a, b) a##b
#define __concat(a, b) ___concat(a, b)

#if defined(DEBUG)
static int __concat(debug_, COMPONENT) = DEBUG;
#else
static int __concat(debug_, COMPONENT) = -1;
#endif
module_param(__concat(debug_, COMPONENT), int, S_IRUGO | S_IWUSR);

#if defined(CONFIG_SND_STM_DEBUG_LEVEL)
extern int *snd_stm_debug_level;
#define verbosity max(*snd_stm_debug_level, __concat(debug_, COMPONENT))
#else
#define verbosity __concat(debug_, COMPONENT)
#endif

#if defined(CONFIG_SND_VERBOSE_PRINTK)

#define snd_stm_printd(level, format, args...) \
		do { \
			if (level <= verbosity) \
				snd_printk(KERN_INFO format, ## args); \
		} while (0)

#define snd_stm_assert snd_assert

#else

#define snd_stm_printd(level, format, args...) \
		do { \
			if (level <= verbosity) \
				printk(KERN_INFO "snd-stm:%s:%d: " format, \
						__snd_stm_component, \
						__LINE__, ## args); \
		} while (0)

#define snd_stm_assert(expr, args...) \
		do { \
			if (unlikely(!(expr))) { \
				printk(KERN_ERR "snd-stm:%s:%d: BUG? " \
						"(%s)\n", \
						__snd_stm_component, \
						__LINE__, \
						__stringify(expr)); \
				dump_stack(); \
				args; \
			} \
		} while (0)
#endif

#else

#define snd_stm_printd(...) /* nothing */

#define snd_stm_assert snd_assert

#endif

/* Error messages */

#if defined(CONFIG_SND_VERBOSE_PRINTK)
#define snd_stm_printe(format, args...) \
		snd_printk(KERN_ERR format, ## args)
#else
#define snd_stm_printe(format, args...) \
		printk(KERN_ERR "snd-stm:%s:%d: " format, \
				__snd_stm_component, __LINE__, ## args)
#endif

/* Magic value checking in device structures */

#if defined(CONFIG_SND_DEBUG) || defined(DEBUG)

#define snd_stm_magic \
		(((unsigned)(&__snd_stm_component) & 0xffff0000) >> 16 ^ \
		((unsigned)(&__snd_stm_component) & 0xffff))
#define snd_stm_magic_good (0x600d0000 | snd_stm_magic)
#define snd_stm_magic_bad (0xbaad0000 | snd_stm_magic)
#define snd_stm_magic_field unsigned __snd_stm_magic
#define snd_stm_magic_set(object) \
		(object)->__snd_stm_magic = snd_stm_magic_good
#define snd_stm_magic_clear(object) \
		(object)->__snd_stm_magic = snd_stm_magic_bad
#define snd_stm_magic_assert(object, args...) \
		snd_stm_assert((object)->__snd_stm_magic == \
				snd_stm_magic_good, ## args)

#else

#	define snd_stm_magic_field /* nothing */
#	define snd_stm_magic_set(object) /* nothing */
#	define snd_stm_magic_clear(object) /* nothing */
#	define snd_stm_magic_assert(object, args...) /* nothing */

#endif



#endif
