TARGET := ampdemo

RTOS := RTThread

NUCLEI_SDK_ROOT ?= ../../..

COMMON_FLAGS = -O3

SOC ?= evalsoc

CORE ?= nx900fd

DOWNLOAD ?= ddr

BOOT_HARTID ?= 3

LINKER_SCRIPT ?= gcc.ld

SRCDIRS = .
INCDIRS = .

CLEAN_OBJS += gcc.ld

include $(NUCLEI_SDK_ROOT)/Build/Makefile.base

gcc.ld: gcc_$(SOC).ld
	$(Q)$(ECHO) "Generate $@ from $<"
	$(Q)$(CC) -E -P -nostdinc -x c -DBOOT_HARTID=$(BOOT_HARTID) $< -o $@
