#ifndef _ASM_IRQ_VECTORS_H
#define _ASM_IRQ_VECTORS_H

#include <linux/threads.h>

#define NMI_VECTOR		0x02

/*
 * IDT vectors usable for external interrupt sources start
 * at 0x20:
 */
#define FIRST_EXTERNAL_VECTOR	0x20

#ifdef CONFIG_X86_32
# define SYSCALL_VECTOR		0x80
#else
# define IA32_SYSCALL_VECTOR	0x80
#endif

/*
 * Reserve the lowest usable priority level 0x20 - 0x2f for triggering
 * cleanup after irq migration on 64 bit.
 */
#define IRQ_MOVE_CLEANUP_VECTOR	FIRST_EXTERNAL_VECTOR

/*
 * Vectors 0x20-0x2f are used for ISA interrupts on 32 bit.
 * Vectors 0x30-0x3f are used for ISA interrupts on 64 bit.
 */
#ifdef CONFIG_X86_32
#define IRQ0_VECTOR		(FIRST_EXTERNAL_VECTOR)
#else
#define IRQ0_VECTOR		(FIRST_EXTERNAL_VECTOR + 0x10)
#endif
#define IRQ1_VECTOR		(IRQ0_VECTOR + 1)
#define IRQ2_VECTOR		(IRQ0_VECTOR + 2)
#define IRQ3_VECTOR		(IRQ0_VECTOR + 3)
#define IRQ4_VECTOR		(IRQ0_VECTOR + 4)
#define IRQ5_VECTOR		(IRQ0_VECTOR + 5)
#define IRQ6_VECTOR		(IRQ0_VECTOR + 6)
#define IRQ7_VECTOR		(IRQ0_VECTOR + 7)
#define IRQ8_VECTOR		(IRQ0_VECTOR + 8)
#define IRQ9_VECTOR		(IRQ0_VECTOR + 9)
#define IRQ10_VECTOR		(IRQ0_VECTOR + 10)
#define IRQ11_VECTOR		(IRQ0_VECTOR + 11)
#define IRQ12_VECTOR		(IRQ0_VECTOR + 12)
#define IRQ13_VECTOR		(IRQ0_VECTOR + 13)
#define IRQ14_VECTOR		(IRQ0_VECTOR + 14)
#define IRQ15_VECTOR		(IRQ0_VECTOR + 15)

/*
 * Special IRQ vectors used by the SMP architecture, 0xf0-0xff
 *
 *  some of the following vectors are 'rare', they are merged
 *  into a single vector (CALL_FUNCTION_VECTOR) to save vector space.
 *  TLB, reschedule and local APIC vectors are performance-critical.
 *
 *  Vectors 0xf0-0xfa are free (reserved for future Linux use).
 */
#ifdef CONFIG_X86_32

# define SPURIOUS_APIC_VECTOR		0xff
# define ERROR_APIC_VECTOR		0xfe
# define INVALIDATE_TLB_VECTOR		0xfd
# define RESCHEDULE_VECTOR		0xfc
# define CALL_FUNCTION_VECTOR		0xfb
# define CALL_FUNCTION_SINGLE_VECTOR	0xfa
# define THERMAL_APIC_VECTOR		0xf0

#else

#define SPURIOUS_APIC_VECTOR		0xff
#define ERROR_APIC_VECTOR		0xfe
#define RESCHEDULE_VECTOR		0xfd
#define CALL_FUNCTION_VECTOR		0xfc
#define CALL_FUNCTION_SINGLE_VECTOR	0xfb
#define THERMAL_APIC_VECTOR		0xfa
#define THRESHOLD_APIC_VECTOR		0xf9
#define INVALIDATE_TLB_VECTOR_END	0xf7
#define INVALIDATE_TLB_VECTOR_START	0xf0	/* f0-f7 used for TLB flush */

#define NUM_INVALIDATE_TLB_VECTORS	8

#endif

/*
 * Local APIC timer IRQ vector is on a different priority level,
 * to work around the 'lost local interrupt if more than 2 IRQ
 * sources per level' errata.
 */
#define LOCAL_TIMER_VECTOR	0xef

/*
 * First APIC vector available to drivers: (vectors 0x30-0xee) we
 * start at 0x31(0x41) to spread out vectors evenly between priority
 * levels. (0x80 is the syscall vector)
 */
#ifdef CONFIG_X86_32
# define FIRST_DEVICE_VECTOR	0x31
#else
# define FIRST_DEVICE_VECTOR	(IRQ15_VECTOR + 2)
#endif

#define NR_VECTORS		256

#define FPU_IRQ			13

#define	FIRST_VM86_IRQ		3
#define LAST_VM86_IRQ		15
#define invalid_vm86_irq(irq)	((irq) < 3 || (irq) > 15)

#if !defined(CONFIG_X86_VOYAGER)

# if defined(CONFIG_X86_IO_APIC) || defined(CONFIG_PARAVIRT) || defined(CONFIG_X86_VISWS)

#  define NR_IRQS		224

#  if (224 >= 32 * NR_CPUS)
#   define NR_IRQ_VECTORS	NR_IRQS
#  else
#   define NR_IRQ_VECTORS	(32 * NR_CPUS)
#  endif

# else /* IO_APIC || PARAVIRT */

#  define NR_IRQS		16
#  define NR_IRQ_VECTORS	NR_IRQS

# endif

#else /* !VISWS && !VOYAGER */

# define NR_IRQS		224
# define NR_IRQ_VECTORS		NR_IRQS

#endif /* VISWS */

/* Voyager specific defines */
/* These define the CPIs we use in linux */
#define VIC_CPI_LEVEL0			0
#define VIC_CPI_LEVEL1			1
/* now the fake CPIs */
#define VIC_TIMER_CPI			2
#define VIC_INVALIDATE_CPI		3
#define VIC_RESCHEDULE_CPI		4
#define VIC_ENABLE_IRQ_CPI		5
#define VIC_CALL_FUNCTION_CPI		6
#define VIC_CALL_FUNCTION_SINGLE_CPI	7

/* Now the QIC CPIs:  Since we don't need the two initial levels,
 * these are 2 less than the VIC CPIs */
#define QIC_CPI_OFFSET			1
#define QIC_TIMER_CPI			(VIC_TIMER_CPI - QIC_CPI_OFFSET)
#define QIC_INVALIDATE_CPI		(VIC_INVALIDATE_CPI - QIC_CPI_OFFSET)
#define QIC_RESCHEDULE_CPI		(VIC_RESCHEDULE_CPI - QIC_CPI_OFFSET)
#define QIC_ENABLE_IRQ_CPI		(VIC_ENABLE_IRQ_CPI - QIC_CPI_OFFSET)
#define QIC_CALL_FUNCTION_CPI		(VIC_CALL_FUNCTION_CPI - QIC_CPI_OFFSET)
#define QIC_CALL_FUNCTION_SINGLE_CPI	(VIC_CALL_FUNCTION_SINGLE_CPI - QIC_CPI_OFFSET)

#define VIC_START_FAKE_CPI		VIC_TIMER_CPI
#define VIC_END_FAKE_CPI		VIC_CALL_FUNCTION_SINGLE_CPI

/* this is the SYS_INT CPI. */
#define VIC_SYS_INT			8
#define VIC_CMN_INT			15

/* This is the boot CPI for alternate processors.  It gets overwritten
 * by the above once the system has activated all available processors */
#define VIC_CPU_BOOT_CPI		VIC_CPI_LEVEL0
#define VIC_CPU_BOOT_ERRATA_CPI		(VIC_CPI_LEVEL0 + 8)


#endif /* _ASM_IRQ_VECTORS_H */
