#
# linux/arch/sh/boot/compressed/Makefile
#
# create a compressed vmlinux image from the original vmlinux
#

targets		:= vmlinux vmlinux.bin vmlinux.bin.gz head.o misc.o piggy.o
EXTRA_AFLAGS	:= -traditional

OBJECTS = $(obj)/head.o $(obj)/misc.o

ifdef CONFIG_SH_STANDARD_BIOS
OBJECTS += $(obj)/../../kernel/sh_bios.o
endif

#
# IMAGE_OFFSET is the load offset of the compression loader
#

ifeq ($(CONFIG_32BIT),y)
IMAGE_OFFSET	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_PAGE_OFFSET)  + \
			$(CONFIG_BOOT_LINK_OFFSET)]')
else
IMAGE_OFFSET	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_PAGE_OFFSET)  + \
			$(CONFIG_MEMORY_START) + \
			$(CONFIG_BOOT_LINK_OFFSET)]')
endif

LIBGCC	:= $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)

LDFLAGS_vmlinux := -Ttext $(IMAGE_OFFSET) -e startup \
		-T $(obj)/../../kernel/vmlinux.lds


$(obj)/vmlinux: $(OBJECTS) $(obj)/piggy.o $(LIBGCC) FORCE
	$(call if_changed,ld)
	@:

$(obj)/vmlinux.bin: vmlinux FORCE
	$(call if_changed,objcopy)

$(obj)/vmlinux.bin.gz: $(obj)/vmlinux.bin FORCE
	$(call if_changed,gzip)

OBJCOPYFLAGS += -R .empty_zero_page

LDFLAGS_piggy.o := -r --format binary --oformat elf32-sh-linux -T


$(obj)/piggy.o: $(obj)/vmlinux.scr $(obj)/vmlinux.bin.gz FORCE
	$(call if_changed,ld)
