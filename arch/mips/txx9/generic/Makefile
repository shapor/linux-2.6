#
# Makefile for common code for TXx9 based systems
#

obj-y	+= setup.o
obj-$(CONFIG_PCI)	+= pci.o
obj-$(CONFIG_SOC_TX4927)	+= mem_tx4927.o irq_tx4927.o
obj-$(CONFIG_SOC_TX4938)	+= mem_tx4938.o irq_tx4938.o
obj-$(CONFIG_TOSHIBA_FPCIB0)	+= smsc_fdc37m81x.o
obj-$(CONFIG_KGDB)	+= dbgio.o

EXTRA_CFLAGS += -Werror
